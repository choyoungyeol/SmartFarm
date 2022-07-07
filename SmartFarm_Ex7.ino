#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>

#define DHTPIN 8
#define DHTTYPE DHT22
#define Red A1
#define Yellow A2
#define Green A3
#define Relay1 3
#define Relay2 4
#define Relay3 5
#define Relay4 6
#define Relay5 7

int Red_value = 0;
int Yellow_value = 0;
int Green_value = 0;
int Relay1_value = 0;
int Relay2_value = 0;
int Relay3_value = 0;
int Relay4_value = 0;
int Relay5_value = 0;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);
SoftwareSerial BT(0, 1);

void setup() {
  Serial.begin(9600);
  dht.begin();
  BT.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  pinMode(Red, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  pinMode(Relay5, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Jeju Nat'l Univ.");
  lcd.setCursor(0, 1);
  lcd.print("Dept. Horticulture");
  lcd.setCursor(0, 2);
  lcd.print("Vegetables Lab.");
  lcd.setCursor(0, 3);
  lcd.print("Cho Young-Yeol");
  delay(5000);
}

void loop() {
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  float DP = dewPoint(temp, humi);
  float AH =  ((6.112 * exp((17.67 * temp) / (temp + 245.5)) * humi * 18.02) / ((273.15 + temp) * 100 * 0.08314));
  float Psat =  (6.112 * exp((17.67 * temp) / (temp + 243.5))) / 10;
  float P =  (6.112 * exp((17.67 * temp) / (temp + 243.5)) * (humi / 100)) / 10;
  float VPD = (Psat - P);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  lcd.print(temp);
  lcd.print(" oC");
  lcd.setCursor(0, 1);
  lcd.print("Humi = ");
  lcd.print(humi);
  lcd.print(" %");
  lcd.setCursor(0, 2);
  lcd.print("DewT = ");
  lcd.print(DP);
  lcd.print(" oC");
  lcd.setCursor(0, 3);
  lcd.print("VPD  = ");
  lcd.print(VPD);
  lcd.print(" kPa");

  if (temp >= 30) {
    analogWrite(Red, 255);
    analogWrite(Yellow, 0);
    analogWrite(Green, 0);
    Red_value = 1 ;
    Yellow_value = 0;
    Green_value = 0;
  }

  if (temp < 30 && temp > 20) {
    analogWrite(Red, 0);
    analogWrite(Yellow, 255);
    analogWrite(Green, 0);
    Red_value = 0 ;
    Yellow_value = 1;
    Green_value = 0;
  }
  if (temp <= 20) {
    analogWrite(Red, 0);
    analogWrite(Yellow, 0);
    analogWrite(Green, 255);
    Red_value = 0 ;
    Yellow_value = 0;
    Green_value = 1;
  }

  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'a') {
      digitalWrite(Relay1, HIGH);
      Relay1_value = 1;
    }
    if (c == 'b') {
      digitalWrite(Relay1, LOW);
      Relay1_value = 0;
    }
    if (c == 'c') {
      digitalWrite(Relay2, HIGH);
      Relay2_value = 1;
    }
    if (c == 'd') {
      digitalWrite(Relay2, LOW);
      Relay2_value = 0;
    }
    if (c == 'e') {
      digitalWrite(Relay3, HIGH);
      Relay3_value = 1;
    }
    if (c == 'f') {
      digitalWrite(Relay3, LOW);
      Relay3_value = 0;
    }
    if (c == 'g') {
      digitalWrite(Relay4, HIGH);
      Relay4_value = 1;
    }
    if (c == 'h') {
      digitalWrite(Relay4, LOW);
      Relay4_value = 0;
    }
    if (c == 'i') {
      digitalWrite(Relay5, HIGH);
      Relay5_value = 1;
    }
    if (c == 'j') {
      digitalWrite(Relay5, LOW);
      Relay5_value = 0;
    }
  }
  if (BT.available()) {
    char c = BT.read();
    if (c == 'a') {
      digitalWrite(Relay1, HIGH);
      Relay1_value = 1;
    }
    if (c == 'b') {
      digitalWrite(Relay1, LOW);
      Relay1_value = 0;
    }
    if (c == 'c') {
      digitalWrite(Relay2, HIGH);
      Relay2_value = 1;
    }
    if (c == 'd') {
      digitalWrite(Relay2, LOW);
      Relay2_value = 0;
    }
    if (c == 'e') {
      digitalWrite(Relay3, HIGH);
      Relay3_value = 1;
    }
    if (c == 'f') {
      digitalWrite(Relay3, LOW);
      Relay3_value = 0;
    }
    if (c == 'g') {
      digitalWrite(Relay4, HIGH);
      Relay4_value = 1;
    }
    if (c == 'h') {
      digitalWrite(Relay4, LOW);
      Relay4_value = 0;
    }
    if (c == 'i') {
      digitalWrite(Relay5, HIGH);
      Relay5_value = 1;
    }
    if (c == 'j') {
      digitalWrite(Relay5, LOW);
      Relay5_value = 0;
    }
  }
  String data = String(temp) + "," + String(humi) + "," + String(DP) + "," + String(AH) + "," + String(VPD) + "," + String(Red_value) + "," + String(Yellow_value) + "," + String(Green_value) + "," + String(Relay1_value) + "," + String(Relay2_value) + "," + String(Relay3_value) + "," + String(Relay4_value) + "," + String(Relay5_value);
  Serial.println(data);
  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();
  delay(1000);
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
