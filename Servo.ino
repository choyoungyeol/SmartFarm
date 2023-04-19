#include <Servo.h>

Servo myservo1;
Servo myservo4;
Servo myservo2;
Servo myservo3;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup() {
  myservo2.attach(24);  // attaches the servo on pin 9 to the servo object
  myservo3.attach(26);
  myservo2.write(180);
  myservo3.write(180);
  myservo1.attach(22);  // attaches the servo on pin 9 to the servo object
  myservo4.attach(28);
  myservo1.write(0);
  myservo4.write(0);

}

void loop() {
  myservo1.write(70);
  delay(1000);
  myservo1.write(0);
  delay(1000);
  myservo4.write(90);
  delay(1000);
  myservo4.write(0);
  delay(1000);

  myservo2.write(90);
  delay(1000);
  myservo2.write(180);
  delay(1000);
  myservo3.write(110);
  delay(1000);
  myservo3.write(180);
  delay(1000);
}
