#include "menu.h"
int stepsToStripStandardWire = 620; //0.5 wire
int lengthPerRevolution_EXTRUDER = 30;
void driveExtruder(int numberOfSteppsForMotor)
{
  digitalWrite(dirPinExtruder, HIGH);
  for (int i = 0; i < numberOfSteppsForMotor; i++)
  {
    digitalWrite(stepPinExtruder, HIGH);
    delayMicroseconds(750);
    digitalWrite(stepPinExtruder, LOW);
    delayMicroseconds(750);
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
  driveWireCutter(stepsToStripStandardWire,1);
  driveWireCutter(stepsToStripStandardWire,0);
  Serial.println((stepsPerRevolution / lengthPerRevolution_EXTRUDER) * (wireLength * 10 - leftIsolationRemove - rightIsolationRemove));
  driveExtruder((stepsPerRevolution / lengthPerRevolution_EXTRUDER) * (wireLength * 10 - leftIsolationRemove - rightIsolationRemove));
  driveWireCutter(stepsToStripStandardWire,1);
  driveWireCutter(stepsToStripStandardWire,0);
  driveExtruder((stepsPerRevolution / lengthPerRevolution_EXTRUDER) * rightIsolationRemove);
  driveWireCutter(stepsPerRevolution*4,1);
  driveWireCutter(stepsPerRevolution*4,0);
}
