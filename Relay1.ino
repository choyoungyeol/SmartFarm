#define Relay1 32

void setup() {
  // put your setup code here, to run once:
  pinMode(Relay1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Relay1, HIGH);
  delay(8000);
  digitalWrite(Relay1, LOW);
  delay(2000);
}
