#define PHOTO A8
#define Relay 34
int Photo_Value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Relay, OUTPUT);
}

void loop() {
  Photo_Value = analogRead(PHOTO);
  float pv_value = float(Photo_Value * 5) / 1023;
  float Rp = (10 * pv_value) / (5 - pv_value);
  float y = (log10(200 / Rp)) / 0.7;
  float Ea = pow(10, y);

  Serial.print("Pa=");
  Serial.print(Photo_Value);
  Serial.print(", Lx=");
  Serial.println(Ea);
  delay(1000);

  if (Ea <= 100) {
    digitalWrite(Relay, LOW);
  } else {
    digitalWrite(Relay, HIGH);
  }
}

주의사항 : 역릴레이 사용
