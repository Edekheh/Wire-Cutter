#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "setup_variables.h"

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void printOnLCD(String line1, String line2)
{
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(line1);
  lcd.setCursor(1, 1);
  lcd.print(line2);
}
void helloScreen()
{
  printOnLCD("Witaj, dzialam", "Kliknij ...");
}

void setUpRoutine()
{
  Serial.begin(9600);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(stepPinExtruder, OUTPUT);
  pinMode(dirPinExtruder, OUTPUT);
  pinMode(stepPinCutter, OUTPUT);
  pinMode(dirPinCutter, OUTPUT);
  lcd.init(); // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  helloScreen();
  while (1)
  {
    SW_state = digitalRead(SW);
    if (!SW_state)
      break;
  }
  menuSwitch = 1;
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
}
