#include "SoftwareSerial.h"
SoftwareSerial K_30_Serial(12, 13);

byte readCO2[] = {0xFE, 0X44, 0X00, 0X08, 0X02, 0X9F, 0X25};
byte response[] = {0, 0, 0, 0, 0, 0, 0};
int valMultiplier = 1;

void sendRequest(byte packet[])
{
  while (!K_30_Serial.available())
  {
    K_30_Serial.write(readCO2, 7);
    delay(50);
  }
  int timeout = 0;
  while (K_30_Serial.available() < 7 )
  {
    timeout++;
    if (timeout > 10)
    {
      while (K_30_Serial.available())
        K_30_Serial.read();
      break;
    }
    delay(50);
  }

  for (int i = 0; i < 7; i++)
  {
    response[i] = K_30_Serial.read();
  }
}
unsigned long getValue(byte packet[])
{
  int high = packet[3];
  int low = packet[4];
  unsigned long val = high * 256 + low;
  return val * valMultiplier;
}

void setup()
{
  Serial.begin(9600);
  K_30_Serial.begin(9600);
}

void loop()
{
  sendRequest(readCO2);
  unsigned long valCO2 = getValue(response);
  Serial.print("Co2 ppm = ");
  Serial.println(valCO2);
  delay(1000);
}
