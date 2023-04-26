#define PHOTO A8
#define Relay 34
int Photo_Value = 0;
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  pinMode(Relay, OUTPUT);
  delay(3000);
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
}

void loop() {
  DateTime now = rtc.now();

  Photo_Value = analogRead(PHOTO);
  float pv_value = float(Photo_Value * 5) / 1023;
  float Rp = (10 * pv_value) / (5 - pv_value);
  float y = (log10(200 / Rp)) / 0.7;
  float Ea = pow(10, y);

  Serial.print("Pa=");
  Serial.print(Photo_Value);
  Serial.print(", Lx=");
  Serial.println(Ea);
  delay(1000);

  if ((now.hour() >= 10 ) && (now.minute() < 51)) {
    if (Ea <= 100) {
      digitalWrite(Relay, LOW);
    } else {
      digitalWrite(Relay, HIGH);
    }
  } else {
    digitalWrite(Relay, HIGH);
  }
}
