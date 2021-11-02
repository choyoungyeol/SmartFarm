#define Water_Pin A1

void setup() {
  Serial.begin(9600);
}

void loop() {
  int Water = analogRead(Water_Pin);
  int Water_Content = map(Water, 518, 272, 0, 100);

  if (Water_Content >= 100) {
    Water_Content = 100;
  }
  if (Water_Content <= 0) {
    Water_Content = 0;
  }
  
  Serial.print("Water = ");
  Serial.println(Water);
  Serial.print("Water content = ");
  Serial.print(Water_Content);
  Serial.println(" %");
  delay(5000);
}
