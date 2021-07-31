//global variables
#define VRx A0
#define VRy A1
#define SW 2
const int stepsPerRevolution = 3200;
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
double stepsForRemoveLeftIsolation=0;
double stepsForCutTheWire_EXTRUDER=0;