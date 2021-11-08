#include "WiFiEsp.h"
#include <Servo.h>
#define Fan 32
#define Light 4
#define servoPin 9

char ssid[] = "**********";            // your network SSID (name)
char pass[] = "**********";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

WiFiEspServer server(80);
Servo myservo;

int Light_value = 0;
int Fan_value = 0;
int Window_value = 0;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(Fan, OUTPUT);
  digitalWrite(Fan, 0);
  pinMode(Light, OUTPUT);
  digitalWrite(Light, 0);
  myservo.attach(servoPin);
  myservo.write(0);

  WiFi.init(&Serial2);

  WiFi.begin(ssid, pass);  // 네트웍에 설정된 id와 패스워드로 접속을 합니다.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // 서버 시작
  server.begin();
  Serial.println("Server started");

  // 서버의(esp8266) IP 주소를 출력합니다
  Serial.println(WiFi.localIP());
}


void loop()
{
  // 클라이언트가 접속하는지 체크 합니다
  WiFiEspClient client = server.available();
  if (!client) {
    return;
  }

  // 클라이언트가 데이터를 보낼 때까지 기다립니다.
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // 요청 첫 출을 읽어 옵니다.
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // 요청 사항과 비교해봅니다.
  if (req.indexOf("/Light/0") != -1) {
    Light_value = 0;
  } else if (req.indexOf("/Light/1") != -1) {
    Light_value = 1;
  } else if (req.indexOf("/Fan/0") != -1) {
    Fan_value = 0;
  } else  if (req.indexOf("/Fan/1") != -1) {
    Fan_value = 1;
  } else if (req.indexOf("/Window/0") != -1) {
    Window_value = 0;
  } else  if (req.indexOf("/Window/1") != -1) {
    Window_value = 90;
  } else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // 요청에 따라 셋팅합니다(ON 또는 OFF)
  digitalWrite(Light, Light_value);
  digitalWrite(Fan, Fan_value);
  myservo.write(Window_value);
  client.flush();

  // 응답을 준비합니다.
  String s1 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n \r\n\r\nLight is now ";
  String s2 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n \r\n\r\nFan is now ";
  String s3 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n \r\n\r\nWindow is now ";
  s1 += (Light_value) ? "HIGH" : "LOW"; //Light_value 값에 따라 HIGH 또는 LOW 응답합니다.
  s1 += "\n";
  s2 += (Fan_value) ? "HIGH" : "LOW"; //Fan_value 값에 따라 HIGH 또는 LOW 응답합니다.
  s2 += "\n";

  // 클라이언트로 응답을 보냅니다
  client.print(s1);
  delay(1);
  client.print(s2);
  delay(1);
  Serial.println("Client disonnected");
}
