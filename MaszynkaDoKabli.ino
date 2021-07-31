#include "menu.h"

void setup()
{
  setUpRoutine();
}

void loop() {
  joystickRoutine();
  printMenu();
  Serial.println(xPosition);
  Serial.println(yPosition);
}
void startProgramCycle(){
  printOnLCD("Wykonywanie ...", "zostalo " + String(wiresNumber));
}
void servoMove()  {
  MOTOR_switcher.write(90);
  delay(500);
  MOTOR_switcher.write(120);
  delay(500);
}

void openWireCutter() {
  Motor_wire_cutter.step(numberOfSteppsToCut_CUTTER);
  delay(1*numberOfSteppsToCut_CUTTER/stepsPerRevolution);//wait on end
}
void closeWireCutter()  {
  Motor_wire_cutter.step(-numberOfSteppsToCut_CUTTER);
  delay(1*numberOfSteppsToCut_CUTTER/stepsPerRevolution);//wait on end
}
void cutTheWire() {
  MOTOR_switcher.write(60);
  delay(250);
  closeWireCutter();
  MOTOR_switcher.write(90);
  delay(250);
  openWireCutter();
}
void singleCutLoop() {
  //extrude length of right isolation removal
  
  extrudeWire(stepsForRemoveRightIsolation);
  removeIsolationFromWire();
  extrudeWire(stepsForRemoveLeftIsolation);
  removeIsolationFromWire();
  extrudeWire(stepsForCutTheWire_EXTRUDER);
  cutTheWire();
}
void removeIsolationFromWire()  {
  closeWireCutter();
  delay(1*numberOfSteppsToCut_CUTTER/stepsPerRevolution);//wait on end
  openWireCutter();
  delay(1*numberOfSteppsToCut_CUTTER/stepsPerRevolution);//wait on end
}
void extrudeWire(double lengthOfWire)  {
  Motor_wire_extruder.step(lengthOfWire);
  delay(1*lengthOfWire/stepsPerRevolution);//wait on end
}
