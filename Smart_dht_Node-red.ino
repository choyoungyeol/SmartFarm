//Arduino Program

#include <dht.h>
#define DHT11_PIN 12

dht DHT;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float chk = DHT.read11(DHT11_PIN);
  Serial.print(DHT.temperature);
  Serial.print(",");
  Serial.println(DHT.humidity);
  delay(5000);
}

//Node-red Program
//https://github.com/choyoungyeol/SmartFarm/issues/1#issue-973231282
