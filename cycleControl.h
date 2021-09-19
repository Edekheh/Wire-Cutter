#include "menu.h"
int stepsToStripStandardWire = 330; //0.75 wire
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
void checkWireDiameter()  {
  if(wireDiameter == 0.75)  {
    stepsToStripStandardWire=330;
  }
  else if(wireDiameter == 0.5)  {
    stepsToStripStandardWire=370;
  }
  else if(wireDiameter == 1)  {
   stepsToStripStandardWire=260;
  }
}
void singleCutLoop()
{
  checkWireDiameter();
  driveExtruder((stepsPerRevolution / lengthPerRevolution_EXTRUDER) * leftIsolationRemove);
  driveWireCutter(stepsToStripStandardWire,1);
  driveWireCutter(stepsToStripStandardWire,0);
  driveExtruder((stepsPerRevolution / lengthPerRevolution_EXTRUDER) * (wireLength * 10 - leftIsolationRemove - rightIsolationRemove));
  driveWireCutter(stepsToStripStandardWire,1);
  driveWireCutter(stepsToStripStandardWire,0);
  driveExtruder((stepsPerRevolution / lengthPerRevolution_EXTRUDER) * rightIsolationRemove);
  driveWireCutter(stepsPerRevolution*2.5,1);
  driveWireCutter(stepsPerRevolution*2.5,0);
}
