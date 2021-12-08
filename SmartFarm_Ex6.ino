#include <SoftwareSerial.h>
#include <dht.h>

#define LED 5
#define Pin 8

SoftwareSerial Bluetooth(2, 3);

dht DHT;

String readString;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Bluetooth.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  readString = "";

  float chk = DHT.read22(Pin);
  float temperature = DHT.temperature;
  float humidity = DHT.humidity;

  if (Serial.available()) {
    delay(3);
    char c = Serial.read();
    if (c == 'a') {
      digitalWrite(LED, HIGH);
    }
    if (c == 'b') {
      digitalWrite(LED, LOW);
    }
  }
  delay(1000);

  if (Bluetooth.available()) {
    delay(3);
    char c = Bluetooth.read();
    readString += c;
  }

  if (readString.length() > 0) {
    if (readString == "a") {
      digitalWrite(LED, HIGH);
    }
    if (readString == "b") {
      digitalWrite(LED, LOW);
    }
  }

  String data = String(temperature) + " ," + String(humidity);
  Serial.println(data);
  delay(2000);
}
