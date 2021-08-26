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
}
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
  driveExtruder((stepsPerRevolution / lengthPerRevolution_EXTRUDER) * leftIsolationRemove);
  driveWireCutter(stepsPerRevolution*3.4,1);
  driveWireCutter(stepsPerRevolution*3.4,0);
  driveExtruder((stepsPerRevolution / lengthPerRevolution_EXTRUDER) * wireLength);
  driveWireCutter(stepsPerRevolution*3.4,1);
  driveWireCutter(stepsPerRevolution*3.4,0);
  driveExtruder((stepsPerRevolution / lengthPerRevolution_EXTRUDER) * rightIsolationRemove);
  driveWireCutter(stepsPerRevolution*4,1);
  driveWireCutter(stepsPerRevolution*4,0);
}
