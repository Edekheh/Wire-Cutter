#include "menu.h"
#include "mathControl.h"
void driveMotor(double steps, int pinDirection, int pinStepps, bool dir)
{
  int czekanie = 1000;
  Serial.print("ILE KROKOW : ");
  Serial.println(steps);
  if (dir)
    digitalWrite(pinDirection, HIGH);
  else
    digitalWrite(pinDirection, LOW);
  if (pinStepps == 3)
  {
    czekanie = 250;
  }
  for (double i = 0; i < steps; i++)
  {
    digitalWrite(pinStepps, HIGH);
    delayMicroseconds(czekanie);
    digitalWrite(pinStepps, LOW);
    delayMicroseconds(czekanie);
  }
}
void openWireCutter()
{
  driveMotor(numberOfSteppsToCut_CUTTER, 3, 4, 1);
}
void closeWireCutter()
{
  driveMotor(numberOfSteppsToCut_CUTTER, 3, 4, 0);
}
void cutTheWire()
{
  closeWireCutter();
  openWireCutter();
}
void closeWireStripper()
{
  driveMotor(numberOfSteppsToStrip_CUTTER, 3, 4, 0);
}
void openWireStripper()
{
  driveMotor(numberOfSteppsToStrip_CUTTER, 3, 4, 1);
}
void removeIsolationFromWire()
{
  closeWireStripper();
  openWireStripper();
}
void extrudeWire(double lengthOfWire)
{
  driveMotor(lengthOfWire, 5, 6, 0);
}
void singleCutLoop()
{
  extrudeWire(stepsForRemoveLeftIsolation);
  removeIsolationFromWire();
  extrudeWire(stepsForRemoveRightIsolation);

  removeIsolationFromWire();
  extrudeWire(stepsForCutTheWire_EXTRUDER);
  cutTheWire();
}
