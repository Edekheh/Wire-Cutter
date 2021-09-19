#include "menu.h"
#include "cycleControl.h"
void setup()
{
  setUpRoutine();
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  calibration();
}

void loop()
{
  joystickRoutine();
  printMenu();
  startProgramCycle();
  /* Joystick testing
  Serial.print("X : ");
  Serial.print(xPosition);
  Serial.print("  Y : ");
  Serial.println(yPosition);
  */
}
void startProgramCycle()
{
  if (!SW_state && menuNumber == 5)
  {
    void calculateStepps();//lets calculate some numbers
    printOnLCD("Wykonywanie ...", "zostalo " + String(wiresNumber));
    if(firstRun)  {
    driveWireCutter(stepsPerRevolution * 2.5, 0);
      firstRun=0;
    }

    for (wiresNumber; wiresNumber > 0; wiresNumber--)
    {
      singleCutLoop();
      printOnLCD("Wykonywanie ...", "zostalo " + String(wiresNumber));
    }
    printOnLCD("Zrobione !!!", "Jazda dalej?");
    while (SW_state)  {
          joystickRoutine();

    }
    menuNumber = 0;
  }
}
void calibration()  {
  printOnLCD("Trwa bazowanie","...............");
  digitalWrite(dirPinCutter, HIGH);
  while(digitalRead(endStopPin))  {
    digitalWrite(stepPinCutter, HIGH);
    delayMicroseconds(600);
    digitalWrite(stepPinCutter, LOW);
    delayMicroseconds(600);
    Serial.println(digitalRead(endStopPin));
  }
}
