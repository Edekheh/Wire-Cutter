//global variables
#define VRx A0
#define VRy A1
#define SW 2
double stepsPerRevolution = 200;
const int numberOfDifferentMenus=5;
const int pitchScrew = 4;
int updateDelayForSettingValues=200;
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
double wireLength = 30;//cm
int menuNumber = 0;
double leftIsolationRemove = 8; //mm
double rightIsolationRemove = 8; //mm
int wiresNumber = 1; //how much wires to cut and strip
bool menuSwitch=0;
bool cycleStart=0;
double wireDiameter = 0.5;