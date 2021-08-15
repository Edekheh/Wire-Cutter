#include "menu.h"
#include "mathControl.h"

void driveExtruder(int numberOfSteppsForMotor)
{
  digitalWrite(dirPinExtruder, HIGH);
  for (int i = 0; i < numberOfSteppsForMotor; i++)
  {
    digitalWrite(stepPinExtruder, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinExtruder, LOW);
    delayMicroseconds(500);
  }
} //2 aby obrac 3 aby uciac
void driveWireCutter(int numberOfSteppsForMotor, bool directionToMove)
{
  if (directionToMove)
    digitalWrite(dirPinCutter, HIGH);
  else
    digitalWrite(dirPinCutter, LOW);

  for (int i = 0; i < numberOfSteppsForMotor; i++)
  {
    digitalWrite(stepPinCutter, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinCutter, LOW);
    delayMicroseconds(500);
  }
}
void singleCutLoop()
{
  driveExtruder((stepsPerRevolution / lengthPerStep_EXTRUDER) * leftIsolationRemove);
  driveWireCutter(stepsPerRevolution*2.25,1);
  driveWireCutter(stepsPerRevolution*2.25,0);
  driveExtruder((stepsPerRevolution / lengthPerStep_EXTRUDER) * wireLength * 10);
  driveWireCutter(stepsPerRevolution*2.25,1);
  driveWireCutter(stepsPerRevolution*2.25,0);
  driveExtruder((stepsPerRevolution / lengthPerStep_EXTRUDER) * rightIsolationRemove);
  driveWireCutter(stepsPerRevolution*3,1);
  driveWireCutter(stepsPerRevolution*3,0);
}
