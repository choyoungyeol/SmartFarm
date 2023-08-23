#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>
#define pinDHT22 30
#define DHTTYPE DHT22
#define PHOTO A8


DHT dht(pinDHT22, DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const int fanRelayPin1 = 32;
const int lightRelayPin2 = 34;
const int relayPin3 = 36;
const int relayPin4 = 38;
const int servoPin1 = 22;
const int servoPin2 = 28;
const int servoPin3 = 26;
const int servoPin4 = 24;
const int lightSensorPin = A8;
const int dhtPin = 30;
float temperature, humidity;
int cdc = 0;
int Photo_Value = 0;


void setup() {
  pinMode(fanRelayPin1, OUTPUT);
  pinMode(lightRelayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin3, OUTPUT);

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);

  dht.begin();

  Serial.begin(9600);
  Serial1.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //lcd.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("JNU SmartFarm");
  lcd.setCursor(0, 1);
  lcd.print("Vegetables Lab.");
  delay(5000);
}


void loop() {
  DateTime now = rtc.now();

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  double gamma = log(humidity / 100) + ((17.62 * temperature) / (243.5 + temperature));
  double dp = 243.5 * gamma / (17.62 - gamma);

  Photo_Value = analogRead(PHOTO);
  float pv_value = float(Photo_Value * 5) / 1023;
  float Rp = (10 * pv_value) / (5 - pv_value);
  float y = (log10(200 / Rp)) / 0.7;
  float Ea = pow(10, y);

  // int lightIntensity = analogRead(lightSensorPin);

  Serial.print("Time: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());
  Serial.print("temp:");
  Serial.print(temperature);
  Serial.print(",humidity:");
  Serial.println(humidity);
  Serial.print("Pa=");
  Serial.print(Photo_Value);
  Serial.print(", Lx=");
  Serial.println(Ea);
  //  Serial.print(" - Light Intensity: ");
  //  Serial.print(lightIntensity);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" 'C");
  lcd.setCursor(0, 1);
  lcd.print("RH: ");
  lcd.print(humidity);
  lcd.print(" %");

  if (Ea <= 100) {
    digitalWrite(lightRelayPin2, LOW);
  } else {
    digitalWrite(lightRelayPin2, HIGH);
  }


  if ((now.hour() >= 6) && (now.hour() <= 22)) {
    if (temperature >= 20) {
      digitalWrite(fanRelayPin1, LOW);
      servo1.write(70);
      delay(100);
      servo2.write(90);
      delay(100);
      servo3.write(110);
      delay(100);
      servo4.write(15);
      delay(100);
    } else {
      digitalWrite(fanRelayPin1, HIGH);
      servo1.write(0);
      servo2.write(10);
      servo3.write(180);
      servo4.write(90);
    }
  }
  delay(100);
}
