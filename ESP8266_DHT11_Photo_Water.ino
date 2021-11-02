#include "WiFiEsp.h"
#include "DHT.h"
#define PHOTO A0
#define Water_Pin A1
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int Photo_Value = 0;

char ssid[] = "********";            // your network SSID (name)
char pass[] = "********";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiEspServer server(80);

void setup()
{
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
