#include "menu.h"
#include "cycleControl.h"
void setup()
{
  setUpRoutine();
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
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
    //calculateStepps(); //#important
    printOnLCD("Wykonywanie ...", "zostalo " + String(wiresNumber));
    driveWireCutter(stepsPerRevolution*3,0);

    for (wiresNumber; wiresNumber > 0; wiresNumber--)
    {
      singleCutLoop();
      printOnLCD("Wykonywanie ...", "zostalo " + String(wiresNumber));
    }
    printOnLCD("Zrobione !!!", "Jazda dalej?");
    while (SW_state)
      ;
    menuNumber = 0;
  }
}
