#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600); //시리얼모니터 출력
  delay(300);
}

void loop()
{

  for (int i = 0; i < 100; i++) { //평균온도
    int temperature = dht.readTemperature();
    delay(10);
  }
  temperature /= 10;
  
  for (int i = 0; i < 100; i++) { //평균상대습도
    int humidity = dht.readHumidity();
    delay(10);
  }
  humidity /= 10;
  Serial.print(temperature, 1); //평균온도값 출력
  Serial.println(" C");
  Serial.print(humidity, 1); //평균상대습도값 출력
  Serial.println(" %");
}
