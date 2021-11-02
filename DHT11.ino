#include <SimpleDHT.h>
#define pinDHT11 12

SimpleDHT11 dht11(pinDHT11);

void setup()
{
  Serial.begin(9600);
}


void loop()
{
  byte temperature = 0;
  byte humidity = 0;
  dht11.read(&temperature, &humidity, NULL);
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  delay(2000);
}
