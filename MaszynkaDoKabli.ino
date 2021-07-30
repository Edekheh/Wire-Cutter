#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

const int stepsPerRevolution = 3200;
Stepper Motor_wire_extruder(stepsPerRevolution,5,6);
Stepper Motor_wire_cutter(stepsPerRevolution,3,4);

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

//global variables
int VRx = A0;
int VRy = A1;
int SW = 2;
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int wireLength = 30;//cm
int menuNumber = 0;
int leftIsolationRemove = 8; //mm
int rightIsolationRemove = 8; //mm
int wiresNumber = 1; //how much wires to cut and strip
bool menuSwitch=0;
bool cycleStart=0;
double lengthPerStep=10.25;//10mm per one motor revolution
double numberOfSteppsToCut_CUTTER=3;//3 motor revolutions to cut wire
double stepsForRemoveRightIsolation=0;
double stepsForRemoveleftIsolation=0;
double stepsForCutTheWire_EXTRUDER=0;

Servo MOTOR_switcher;

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
void setUpRoutine() {
  Serial.begin(9600);
  Motor_wire_extruder.setSpeed(60);
  Motor_wire_cutter.setSpeed(60);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  MOTOR_switcher.attach(9);
  MOTOR_switcher.write(90);  // set servo to mid-point
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  helloScreen();
  while(1)  {
    SW_state = digitalRead(SW);
    if(!SW_state)break;
  }
  menuSwitch=1;
}
void printOnLCD(String line1, String line2)  {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(line1);
  lcd.setCursor(1, 1);
  lcd.print(line2);
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
void helloScreen()  {
  printOnLCD("Witaj, dzialam", "Kliknij ...");
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
