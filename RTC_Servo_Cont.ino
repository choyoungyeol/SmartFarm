#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#include <Servo.h>

Servo myservo1;
Servo myservo4;
Servo myservo2;
Servo myservo3;  // create servo object to control a servo
// twelve servo objects can be created on most boards


void setup () {
  myservo2.attach(24);  // attaches the servo on pin 9 to the servo object
  myservo3.attach(26);
  myservo2.write(180);
  myservo3.write(180);
  myservo1.attach(22);  // attaches the servo on pin 9 to the servo object
  myservo4.attach(28);
  myservo1.write(0);
  myservo4.write(0);
  Serial.begin(9600);
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
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(", ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(3000);

  if (now.hour() == 10 && now.minute() ==49) {
    myservo1.write(70);
    delay(1000);
    myservo4.write(90);
    delay(1000);
    myservo2.write(90);
    delay(1000);
    myservo3.write(110);
    delay(1000);
  } else {
    myservo1.write(0);
    delay(1000);
    myservo4.write(0);
    delay(1000);
    myservo2.write(180);
    delay(1000);
    myservo3.write(180);
    delay(1000);
  }
}
