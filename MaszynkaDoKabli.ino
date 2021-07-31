

#include "setup_routine.h"




void setup()
{
  setUpRoutine();
}


void loop() {
  joystickRoutine();
  if (menuNumber == 0 && menuSwitch)  {
    printOnLCD("Podaj dlugosc", "kabla(cm) " + String(wireLength));
    menuSwitch=0;
  }
  else if (menuNumber == 1 && menuSwitch)  {
    printOnLCD("Odizolowanie", "lewa(mm) " + String(leftIsolationRemove));
    menuSwitch=0;
  }
  else if (menuNumber == 2 && menuSwitch)  {
    printOnLCD("Odizolowanie", "prawa(mm) " + String(rightIsolationRemove));
    menuSwitch=0;
  }
  else if (menuNumber == 3 && menuSwitch)  {
    printOnLCD("Ilosc sztuk", "kabla " + String(wiresNumber));
    menuSwitch=0;
  }
   else if (menuNumber == 4 && menuSwitch)  {
    printOnLCD("Kliknij, aby", "wykonac ..." + String(wiresNumber));
    menuSwitch=0;
  }
  else if (cycleStart)  {
    startProgramCycle();
  }

}
void startProgramCycle(){
  printOnLCD("Wykonywanie ...", "zostalo " + String(wiresNumber));
  
}
void servoMove()  {
  MOTOR_switcher.write(90);
  delay(1000);
  MOTOR_switcher.write(120);
  delay(1000);
}


void joystickCommander() {

}
void joystickRoutine()  {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  if (xPosition >= 800) {
    menuNumber++;
    delay(500);
    if (menuNumber >= 5)menuNumber = 4;
    else menuSwitch=1;
  }
  else if (xPosition <= 100)  {
    menuNumber--;
    delay(500);
    if (menuNumber <= 0)menuNumber = 0;
    else menuSwitch=1;
  }
  else if (!SW_state && menuNumber==4)  {
    cycleStart=1;
  }
  else if(yPosition>=800) {
    if(menuNumber==0) {
      wireLength++;
      delay(50);
    }
    else if(menuNumber==1) {
      leftIsolationRemove++;
      delay(50);
    }
    else if(menuNumber==2) {
      rightIsolationRemove++;
      delay(50);
    }
    else if(menuNumber==3) {
      wiresNumber++;
      delay(50);
    }
  }
    else if(yPosition<=100) {
    if(menuNumber==0) {
      wireLength--;
      if(wireLength<0)wireLength=0;
      delay(50);
    }
    else if(menuNumber==1) {
      leftIsolationRemove--;
      if(leftIsolationRemove<0)leftIsolationRemove=0;
      delay(50);
    }
    else if(menuNumber==2) {
      rightIsolationRemove--;
      if(rightIsolationRemove<0)rightIsolationRemove=0;
      delay(50);
    }
    else if(menuNumber==3) {
      wiresNumber--;
      if(wiresNumber<0)wiresNumber=0;
      delay(50);
    }
  }
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
