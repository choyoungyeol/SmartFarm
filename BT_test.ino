#define Light 4
#define Fan 32

void setup()
{
  pinMode(Light, OUTPUT);
  pinMode(Fan, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
  if (Serial1.available()) {
    delay(3);
    char c = Serial1.read();

    if (c == 'a') {
      digitalWrite(Light, HIGH);
    }
    if (c == 'b') {
      digitalWrite(Light, LOW);
    }
    if (c == 'c') {
      digitalWrite(Fan, HIGH);
    }
    if (c == 'd') {
      digitalWrite(Fan, LOW);
    }
  }
  delay(2000);
    if (Serial.available()) {
    delay(3);
    char c = Serial.read();

    if (c == 'a') {
      digitalWrite(Light, HIGH);
    }
    if (c == 'b') {
      digitalWrite(Light, LOW);
    }
    if (c == 'c') {
      digitalWrite(Fan, HIGH);
    }
    if (c == 'd') {
      digitalWrite(Fan, LOW);
    }
  }
}
