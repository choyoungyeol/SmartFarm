#include <SDISerial.h>
#include <string.h>
#define pin 7

SDISerial connection(pin);

char output_buffer[125];
char tmp_buffer[4];

void setup() {
  connection.begin();
  Serial.begin(9600);
  delay(3000);
}

void loop() {
  char* resp = connection.sdi_query("0R0!", 1000);
  sprintf(output_buffer, "RECV: %s", resp ? resp : "No Response Received!");
  Serial.println(output_buffer);
  delay(5000);

  if (resp != nullptr) {
    String resp1 = resp;
    int first = resp1.indexOf("-");
    int second = resp1.indexOf("+", first + 1);
    int length = resp1.length();

    String ch = resp1.substring(0, first);  // 채널 값
    String kPa = resp1.substring(first + 1, second);  // kPa 값
    String Temp = resp1.substring(second + 1, length);  // 온도 값

    // kPa를 float로 변환
    float fkPa = kPa.toFloat();

    // kPa 값이 음수일 때 양수로 변환하여 pF 계산
    if (fkPa < 0) {
      fkPa = -fkPa;  // 음수를 양수로 변경
    }

    // pF 계산: log10(kPa * 10.197)
    float pF = log10(fkPa * 10.197);

    // pF가 유효한 값(0 이상)인지 확인하고 출력
    if (pF > 0) {
      Serial.println(ch);
      Serial.println(kPa);
      Serial.println(pF);
      Serial.println(Temp);
    } else {
      Serial.println("pF value is too low for log calculation.");
    }
  } else {
    Serial.println("No valid response received.");
  }
}
