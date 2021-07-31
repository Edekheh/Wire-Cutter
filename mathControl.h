//global variables

double lengthPerStep_EXTRUDER=6;//6mm per one motor revolution
double numberOfSteppsToCut_CUTTER=2400;
double stepsForRemoveRightIsolation=0;
double stepsForRemoveLeftIsolation=0;
double stepsForCutTheWire_EXTRUDER=0;
double numberOfSteppsToStrip_CUTTER= 2000;//2000stepps for stripping 0.5 ; 1 rev = 4mm

void calculateStepps()  {
    if(0.5>wireDiameter)    {
        numberOfSteppsToStrip_CUTTER+=(0.5-wireDiameter)*stepsPerRevolution/pitchScrew;
    }
    else if(0.5<wireDiameter)   {
        numberOfSteppsToStrip_CUTTER-=(wireDiameter-0.5)*stepsPerRevolution/pitchScrew;
    }
    stepsForRemoveLeftIsolation=leftIsolationRemove*lengthPerStep_EXTRUDER*stepsPerRevolution;
    stepsForRemoveRightIsolation=wireLength*10*lengthPerStep_EXTRUDER*stepsPerRevolution;
    stepsForCutTheWire_EXTRUDER=rightIsolationRemove*lengthPerStep_EXTRUDER*stepsPerRevolution;
}