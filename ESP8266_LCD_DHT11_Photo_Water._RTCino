#include "WiFiEsp.h"
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"

#define PHOTO A0
#define Water_Pin A1
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

int Photo_Value = 0;

char ssid[] = "*******";            // your network SSID (name)
char pass[] = "*******";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
int reqCount = 1;
WiFiEspServer server(80);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("JNU SmartFarm");
  lcd.setCursor(0, 1);
  lcd.print("Jeju Nat'l Univ.");
  delay(5000);
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
  WiFi.init(&Serial2);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");
  printWifiStatus();

  server.begin();
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
  // listen for incoming clients
  WiFiEspClient client = server.available();
  if (client) {
    Serial.println("New client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          Serial.println("Sending response");
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "Refresh: 20\r\n"
            "\r\n");
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<html>\r\n");
          client.print("<h1>Greenhouse Environment</h1>\r\n");
          client.print("Photo : ");
          client.print(Ea);
          client.print(" Lux");
          client.print("<br>\r\n");
          client.print("Temperature : ");
          client.print(temperature);
          client.print(" oC");
          client.print("<br>\r\n");
          client.print("Humidity : ");
          client.print(humidity);
          client.print(" %");
          client.print("<br>\r\n");
          client.print("Water Content : ");
          client.print(Water_Content);
          client.print(" %");
          client.print("<br>\r\n");
          client.print("</html>\r\n");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(10);
    client.stop();
    Serial.println("Client disconnected");
  }

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
  delay(2000);
}

void printWifiStatus()
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println();
}
