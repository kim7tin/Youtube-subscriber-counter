#include "LiquidCrystal_I2C.h"
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte aSac[8] = {
  0b00010,
  0b00100,
  0b00000,
  0b01111,
  0b00001,
  0b01111,
  0b10001,
  0b01111
};

byte dongHo[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b10101,
  0b10111,
  0b10001,
  0b01110,
  0b00000
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(D2, D1);
  lcd.begin();
  lcd.createChar(0, heart);
  lcd.createChar(1, aSac);
  lcd.createChar(2, dongHo);
  lcd.home();
  lcd.print("T");
  lcd.write((byte) 1);
  lcd.print("y M");
  lcd.write((byte) 1);
  lcd.print("y Channel");
  lcd.setCursor(0,1);

  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
  lcd.write((byte) 0);
}

void loop() {
}
