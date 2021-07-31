#include "menu.h"
#include "mathControl.h"
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
void closeWireStripper()    {
    Motor_wire_cutter.step(-numberOfSteppsToStrip_CUTTER);
  delay(1*numberOfSteppsToStrip_CUTTER/stepsPerRevolution);//wait on end
}
void openWireStripper() {
    Motor_wire_cutter.step(numberOfSteppsToStrip_CUTTER);
  delay(1*numberOfSteppsToStrip_CUTTER/stepsPerRevolution);//wait on end
}
void removeIsolationFromWire()  {
  closeWireStripper();
  delay(1*numberOfSteppsToStrip_CUTTER/stepsPerRevolution);//wait on end
  openWireStripper();
  delay(1*numberOfSteppsToStrip_CUTTER/stepsPerRevolution);//wait on end
}
void extrudeWire(double lengthOfWire)  {
  Motor_wire_extruder.step(lengthOfWire);
  delay(1*lengthOfWire/stepsPerRevolution);//wait on end
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

