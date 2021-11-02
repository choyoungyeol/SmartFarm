#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("JNU Arduino!");
  delay(5000);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, JNU!");
  lcd.setCursor(0, 1);
  lcd.print("Start Arduino!");
  delay(5000);
}
