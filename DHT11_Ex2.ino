#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600); //시리얼모니터 출력
  delay(300);
}

void loop(){
  int temperature = dht.readTemperature();
  int humidity = dht.readHumidity();
  
  for (int i = 0; i < 100; i++) { //평균온도
    temperature += dht.readTemperature();
    delay(10);
  }
  temperature /= 100;

  for (int i = 0; i < 100; i++) { //평균상대습도
    humidity += dht.readHumidity();
    delay(10);
  }
  humidity /= 100;
  Serial.print(temperature); //평균온도값 출력
  Serial.println(" C");
  Serial.print(humidity); //평균상대습도값 출력
  Serial.println(" %");
  delay(2000);
}
