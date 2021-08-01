//global variables

double lengthPerStep_EXTRUDER=32.5;//325mm per one motor revolution
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
    stepsForRemoveLeftIsolation=leftIsolationRemove*stepsPerRevolution/lengthPerStep_EXTRUDER;
    Serial.print("LEWA : ");
    Serial.println(stepsForRemoveLeftIsolation);
    Serial.print("dlugosc : ");
    Serial.println(wireLength);
    Serial.print("stepy :");
    Serial.println(stepsPerRevolution);
    Serial.print("lengthPerCostam");
    Serial.println(lengthPerStep_EXTRUDER);
    
    Serial.print("SRODEK : ");
    stepsForRemoveRightIsolation=wireLength*10*stepsPerRevolution/lengthPerStep_EXTRUDER;

    Serial.println(stepsForRemoveRightIsolation);
    stepsForCutTheWire_EXTRUDER=rightIsolationRemove*stepsPerRevolution/lengthPerStep_EXTRUDER;
    Serial.print("PRAWA : ");

    Serial.println(stepsForCutTheWire_EXTRUDER);
}