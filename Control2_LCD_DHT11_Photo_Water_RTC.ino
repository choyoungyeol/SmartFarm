#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include <Servo.h>

#define PHOTO A0
#define Water_Pin A1
#define DHTPIN 12
#define DHTTYPE DHT11
#define servoPin 9
#define Fan 32
#define Light 4

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;
Servo myservo;

int Photo_Value = 0;
int pos = 0;
int Auto = 1;

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("JNU SmartFarm");
  lcd.setCursor(0, 1);
  lcd.print("Jeju Nat'l Univ.");
  delay(5000);
  myservo.attach(servoPin);
  pinMode(Fan, OUTPUT);
  pinMode(Light, OUTPUT);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  } else {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  }

  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop()
{
  DateTime now = rtc.now();
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();
  Photo_Value = analogRead(PHOTO);
  float pv_value = float(Photo_Value * 5) / 1023;
  float Rp = (10 * pv_value) / (5 - pv_value);
  float y = (log10(200 / Rp)) / 0.7;
  float Ea = pow(10, y);

  int Water = analogRead(Water_Pin);
  int Water_Content = map(Water, 518, 272, 0, 100);

  if (Water_Content >= 100) {
    Water_Content = 100;
  }
  if (Water_Content <= 0) {
    Water_Content = 0;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(now.year());
  lcd.print("/");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.day());
  lcd.setCursor(0, 1);
  lcd.print(now.hour());
  lcd.print(" hour: ");
  lcd.print(now.minute());
  lcd.print(" min");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lux= ");
  lcd.print(Ea);
  lcd.setCursor(0, 1);
  lcd.print("Water= ");
  lcd.print(Water_Content);
  lcd.print(" %");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp= ");
  lcd.print(temperature);
  lcd.print(" oC");
  lcd.setCursor(0, 1);
  lcd.print("R  H= ");
  lcd.print(humidity);
  lcd.print(" %");
  delay(5000);

  if (Auto == 1) {
    if (now.hour() >= 6 && now.hour() <= 18) {
      if (Ea <= 10000) {
        digitalWrite(Light, HIGH);
      } else {
        digitalWrite(Light, LOW);
      }
      if (temperature >= 25) {
        digitalWrite(Fan, HIGH);
        myservo.write(90);

      } else {
        digitalWrite(Fan, LOW);
        myservo.write(0);
      }
    } else {
      digitalWrite(Light, LOW);
      if (temperature >= 25) {
        digitalWrite(Fan, HIGH);
        myservo.write(90);
      } else {
        digitalWrite(Fan, LOW);
        myservo.write(0);
      }
    }
  } else {                             //Auto == 0
    if (readString.length() > 0) {
      if (readString = "x") {
        Auto = 1;
      }
      if (readString = "y") {
        Auto = 0;
      }

      if (readString = "a") {
        digitalWrite(Light, HIGH);
      }
      if (readString = "b") {
        digitalWrite(Light, LOW);
      }

      if (readString = "c") {
        digitalWrite(Fan, HIGH);
      }
      if (readString = "d") {
        digitalWrite(Fan, LOW);
      }

      if (readString = "e") {
        servo.write(90);
      }
      if (readString = "f") {
        servo.write(0);
      }

      if (readString = "0") {
        analogWrite(Light_Pin, 0);
      }

      if (readString = "1") {
        analogWrite(Light, 25);
      }
      if (readString = "2") {
        analogWrite(Light, 75);
      }
      if (readString = "3") {
        analogWrite(Light, 100);
      }
      if (readString = "4") {
        analogWrite(Light, 125);
      }
      if (readString = "5") {
        analogWrite(Light, 150);
      }
      if (readString = "6") {
        analogWrite(Light, 175);
      }
      if (readString = "7") {
        analogWrite(Light, 200);
      }
      if (readString = "8") {
        analogWrite(Light, 225);
      }
      if (readString = "9") {
        analogWrite(Light, 250);
      }
    }
  }

  while (Serial2.available()) {
    delay(3);
    char c = Serial2.read();
    readString += c;
  }
  if (readString.length() > 0) {
    if (readString = "x") {
      Auto = 1;
    }
    if (readString = "y") {
      Auto = 0;
    }
  }
  Auto = Auto;
}
