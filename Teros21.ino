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
  sprintf(output_buffer, "RECV: %s", resp ? resp : "No Response Recieved!");
  Serial.println(output_buffer);
  delay(5000);
}
