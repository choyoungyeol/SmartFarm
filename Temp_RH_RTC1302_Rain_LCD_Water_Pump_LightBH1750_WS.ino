#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <BH1750.h>
#include <RtcDS1302.h>

#define DHTPIN 22
#define DHTTYPE DHT22
#define WaterPin A8
#define RainPin 25

#define Light 26
#define Fan_in 28
#define Fan_out 30
#define Pump 32

#define RSWPin 31
#define LSWPin 33
#define RUWPin 35
#define LUWPin 37

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo RSW;    //Right Side Window
Servo LSW;    //Left Side Window
Servo RUW;    //Right Up Window
Servo LUW;    //Left Up Window
BH1750 lightMeter;
ThreeWire myWire(4, 5, 2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

const int Target_Water_low = 20;
const int Target_Water_high = 23;

const int Target_Temp_low = 20;
const int Target_Temp_high = 30;

const int Target_Light_low = 200;
const int Target_Light_high = 500;

int RSW_value = 0;
int LSW_value = 0;
int RUW_value = 0;
int LUW_value = 0;
int Windows_value = 0;

int Fan_in_value = 0;
int Fan_out_value = 0;
int Light_value = 0;
int Pump_value = 0;
int Rain_value = 0;

char                 databuffer[35];
double               temp;

void getBuffer()                                                                    //Get weather status data
{
  int index;
  for (index = 0; index < 35; index++) {
    if (Serial.available()) {
      databuffer[index] = Serial.read();
      if (databuffer[0] != 'c') {
        index = -1;
      }
    } else {
      index--;
    }
  }
}

int transCharToInt(char* _buffer, int _start, int _stop)                             //char to int）
{
  int _index;
  int result = 0;
  int num = _stop - _start + 1;
  int _temp[num];
  for (_index = _start; _index <= _stop; _index++) {
    _temp[_index - _start] = _buffer[_index] - '0';
    result = 10 * result + _temp[_index - _start];
  }
  return result;
}

int transCharToInt_T(char* _buffer)
{
  int result = 0;
  if (_buffer[13] == '-') {
    result = 0 - (((_buffer[14] - '0') * 10) + (_buffer[15] - '0'));
  } else {
    result = ((_buffer[13] - '0') * 100) + ((_buffer[14] - '0') * 10) + (_buffer[15] - '0');
  }
  return result;
}

int WindDirection()                                                                  //Wind Direction
{
  return transCharToInt(databuffer, 1, 3);
}

float WindSpeedAverage()                                                             //air Speed (1 minute)
{
  temp = 0.44704 * transCharToInt(databuffer, 5, 7);
  return temp;
}

float WindSpeedMax()                                                                 //Max air speed (5 minutes)
{
  temp = 0.44704 * transCharToInt(databuffer, 9, 11);
  return temp;
}

float Temperature()                                                                  //Temperature ("C")
{
  temp = (transCharToInt_T(databuffer) - 32.00) * 5.00 / 9.00;
  return temp;
}

float RainfallOneHour()                                                              //Rainfall (1 hour)
{
  temp = transCharToInt(databuffer, 17, 19) * 25.40 * 0.01;
  return temp;
}

float RainfallOneDay()                                                               //Rainfall (24 hours)
{
  temp = transCharToInt(databuffer, 21, 23) * 25.40 * 0.01;
  return temp;
}

int Humidity()                                                                       //Humidity
{
  return transCharToInt(databuffer, 25, 26);
}

float BarPressure()                                                                  //Barometric Pressure
{
  temp = transCharToInt(databuffer, 28, 32);
  return temp / 10.00;
}


void setup() {
  RSW.attach(RSWPin);
  LSW.attach(LSWPin);
  RUW.attach(RUWPin);
  LUW.attach(LUWPin);

  RSW.write(0);
  delay(1000);
  LSW.write(180);
  delay(1000);
  RUW.write(0);
  delay(1000);
  LUW.write(180);
  delay(1000);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Jeju Nat'l Univ.");
  lcd.setCursor(0, 1);
  lcd.print("Hortic. Sci. Major");
  lcd.setCursor(0, 2);
  lcd.print("Vegetables Lab.");
  lcd.setCursor(0, 3);
  lcd.print("By Young Yeol CHO");
  Serial.begin(9600);
  dht.begin();
  lightMeter.begin();
  Rtc.Begin();
  pinMode(Pump, OUTPUT);
  pinMode(Fan_in, OUTPUT);
  pinMode(Fan_out, OUTPUT);
  pinMode(Light, OUTPUT);
  pinMode(RainPin, INPUT);

  delay(5000);
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  RtcDateTime now = Rtc.GetDateTime();
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();
  getBuffer();
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  float DP = dewPoint(temp, humi);
  float AH =  ((6.112 * exp((17.67 * temp) / (temp + 245.5)) * humi * 18.02) / ((273.15 + temp) * 100 * 0.08314));
  float Psat =  (6.112 * exp((17.67 * temp) / (temp + 243.5))) / 10;
  float P =  (6.112 * exp((17.67 * temp) / (temp + 243.5)) * (humi / 100)) / 10;
  float VPD = (Psat - P);
  int WaterValue = analogRead(WaterPin);
  float lux = lightMeter.readLightLevel();
  Rain_value = digitalRead(RainPin);

  int Water = map(WaterValue, 535, 289, 0, 100);
  Water = constrain(Water, 0, 100);

  if (Water < Target_Water_low) {
    digitalWrite(Pump, HIGH);
    Pump_value = 1;
    delay(5000);
  }

  if (Water > Target_Water_high) {
    digitalWrite(Pump, LOW);
    Pump_value = 0;
  }

  if (temp < Target_Temp_low) {
    RSW.write(0);
    delay(1000);
    LSW.write(180);
    delay(1000);
    RUW.write(0);
    delay(1000);
    LUW.write(180);
    delay(1000);

    Windows_value = 0;
    digitalWrite(Fan_in, LOW);
    Fan_in_value = 0;
    digitalWrite(Fan_out, LOW);
    Fan_out_value = 0;
  }

  if (temp > Target_Temp_high) {
    RSW.write(80);
    delay(1000);
    LSW.write(120);
    delay(1000);
    RUW.write(60);
    delay(1000);
    LUW.write(120);
    delay(1000);
    Windows_value = 1;
    digitalWrite(Fan_in, HIGH);
    Fan_in_value = 1;
    digitalWrite(Fan_out, HIGH);
    Fan_out_value = 1;
  }

  if (lux < Target_Light_low) {
    digitalWrite(Light, HIGH);
    Light_value = 1;
    delay(5000);
  }

  if (lux > Target_Light_high) {
    digitalWrite(Light, LOW);
    Light_value = 0;
  }

  if (Rain_value == 1) {
    Rain_value = 0;
  } else {
    Rain_value = 1;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(now.Year());
  lcd.print(" / ");
  lcd.print(now.Month());
  lcd.print(" / ");
  lcd.print(now.Day());
  lcd.setCursor(0, 1);
  lcd.print(now.Hour());
  lcd.print(" : ");
  lcd.print(now.Minute());
  lcd.print(" : ");
  lcd.print(now.Second());
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(temp);
  lcd.print("  oC");
  lcd.setCursor(0, 1);
  lcd.print("R H  : ");
  lcd.print(humi);
  lcd.print("  %");
  lcd.setCursor(0, 2);
  lcd.print("A H  : ");
  lcd.print(AH);
  lcd.print("  g/m3");
  lcd.setCursor(0, 3);
  lcd.print("VPD  : ");
  lcd.print(VPD);
  lcd.print("  kPa");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water : ");
  lcd.print(Water);
  lcd.print("  %");

  if (Pump_value == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("Pump ON");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Pump OFF");
  }

  if (Windows_value == 1) {
    lcd.setCursor(0, 2);
    lcd.print("Windows OPEN");
  } else {
    lcd.setCursor(0, 2);
    lcd.print("Windows CLOSED");
  }

  if (VPD >= 0.5 && VPD <= 1.2) {
    lcd.setCursor(0, 3);
    lcd.print("Environment  GOOD");
  } else {
    lcd.setCursor(0, 3);
    lcd.print("Environment  BAD");
  }
  delay(5000);

  if (Fan_in_value == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fan IN ON");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fan IN OFF");
  }
  if (Fan_out_value == 1) {
    lcd.setCursor(0, 1);
    lcd.print("Fan OUT ON");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Fan OUT OFF");
  }
  lcd.setCursor(0, 2);
  lcd.print("Light : ");
  lcd.print(lux);

  if (Light_value == 1) {
    lcd.setCursor(0, 3);
    lcd.print("Light ON");
  } else {
    lcd.setCursor(0, 3);
    lcd.print("Light OFF");
  }
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WD : ");
  lcd.print(WindDirection());
  lcd.print("  ");
  lcd.setCursor(0, 1);
  lcd.print("Avg WS: ");
  lcd.print(WindSpeedAverage());
  lcd.print("  m/s");
  lcd.setCursor(0, 2);
  lcd.print("Max WS: ");
  lcd.print(WindSpeedMax());
  lcd.print("  m/s");
  lcd.setCursor(0, 3);
  lcd.print("Bar PS: ");
  lcd.print(BarPressure());
  lcd.print("  hPa");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rain 01: ");
  lcd.print(RainfallOneHour());
  lcd.print(" mm");
  lcd.setCursor(0, 1);
  lcd.print("Rain 24: ");
  lcd.print(RainfallOneDay());
  lcd.print("  mm");
  lcd.setCursor(0, 2);
  lcd.print("Temp Out: ");
  lcd.print(Temperature());
  lcd.print("  oC");
  lcd.setCursor(0, 3);
  lcd.print("Humi Out: ");
  lcd.print(Humidity());
  lcd.print("  %");
  delay(5000);

  Serial.print(lux);
  Serial.print(", ");
  Serial.print(temp);
  Serial.print(", ");
  Serial.print(humi);
  Serial.print(", ");
  Serial.print(VPD);
  Serial.print(", ");
  Serial.print(Water);
  Serial.print(", ");
  Serial.print(Pump_value);
  Serial.print(", ");
  Serial.print(Rain_value);
  Serial.print(", ");
  Serial.print(Fan_in_value);
  Serial.print(", ");
  Serial.print(Fan_out_value);
  Serial.print(", ");
  Serial.print(Light_value);
  Serial.print(", ");
  Serial.print(WindDirection());
  Serial.print(", ");
  Serial.print(WindSpeedAverage());
  Serial.print(", ");
  Serial.print(WindSpeedMax());
  Serial.print(", ");
  Serial.print(RainfallOneHour());
  Serial.print(", ");
  Serial.print(RainfallOneDay());
  Serial.print(", ");
  Serial.print(Temperature());
  Serial.print(", ");
  Serial.print(Humidity());
  Serial.print(", ");
  Serial.println(BarPressure());

  //  Serial.print("{\"temp\":");
  //  Serial.print(temp);
  //  Serial.print(",\"humidity\":");
  //  Serial.print(humi);
  //  Serial.print(",\"AH\":");
  //  Serial.print(AH);
  //  Serial.print(",\"VPD\":");
  //  Serial.print(VPD);
  //  Serial.print(",\"Water\":");
  //  Serial.print(Water);
  //  Serial.print(",\"Light\":");
  //  Serial.print(Photo);
  //  Serial.print(",\"Pump_value\":");
  //  Serial.print(Pump_value);
  //  Serial.print(",\"Windows_value\":");
  //  Serial.print(Windows_value);
  //  Serial.print(",\"Fan_in_value\":");
  //  Serial.print(Fan_in_value);
  //  Serial.print(",\"Fan_out_value\":");
  //  Serial.print(Fan_out_value);
  //  Serial.print(",\"Light_value\":");
  //  Serial.print(Light_value);
  //  Serial.println("}");
}

float dewPoint(float temp, float humi) {
  float RATIO = 373.15 / (273.15 + temp);
  float RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);
  float VP = pow(10, RHS - 3) * humi;
  float T = log(VP / 0.61078); // temp var
  return (241.88 * T) / (17.558 - T);
}
