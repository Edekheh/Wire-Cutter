//global variables

int lengthPerRevolution_EXTRUDER = 28; //19mm per one motor revolution
int stepsForRemoveRightIsolation = 0;
int stepsForRemoveLeftIsolation = 0;
int stepsForCutTheWire_EXTRUDER = 0;
int numberOfSteppsToStrip_CUTTER = 0;
int numberOfSteppsToCut_CUTTER = 0;
void calculateStepps()
{
    numberOfSteppsToStrip_CUTTER = stepsPerRevolution * 2.25; //for 0.5 mm wire
    numberOfSteppsToCut_CUTTER = stepsPerRevolution * 3;      //for 0.5mm wire
    if(wireDiameter>0.5)    {
        numberOfSteppsToStrip_CUTTER-=(wireDiameter/0.05-10)*2.5;//some weird math
    }
    else if(wireDiameter<0.5)    {
        numberOfSteppsToStrip_CUTTER+=(10-wireDiameter/0.05)*2.5;//some weird math
    }
}