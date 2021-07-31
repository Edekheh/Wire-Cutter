#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include "setup_variables.h"


Stepper Motor_wire_extruder(stepsPerRevolution,5,6);
Stepper Motor_wire_cutter(stepsPerRevolution,3,4);
Servo MOTOR_switcher;
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display


void printOnLCD(String line1, String line2)  {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(line1);
  lcd.setCursor(1, 1);
  lcd.print(line2);
}
void helloScreen()  {
  printOnLCD("Witaj, dzialam", "Kliknij ...");
}




void setUpRoutine() {
  Serial.begin(9600);
  Motor_wire_extruder.setSpeed(60);
  Motor_wire_cutter.setSpeed(60);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  MOTOR_switcher.attach(9);
  MOTOR_switcher.write(90);  // set servo to mid-point
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  helloScreen();
  while(1)  {
    SW_state = digitalRead(SW);
    if(!SW_state)break;
  }
  menuSwitch=1;
}
