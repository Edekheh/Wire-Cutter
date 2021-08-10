//global variables

double lengthPerStep_EXTRUDER = 32.2; //19mm per one motor revolution
double numberOfSteppsToCut_CUTTER = 2400*3;
double stepsForRemoveRightIsolation = 0;
double stepsForRemoveLeftIsolation = 0;
double stepsForCutTheWire_EXTRUDER = 0;
double numberOfSteppsToStripMinInterval = stepsPerRevolution / 80; //for stripping 0.05 ; 1 rev = 4mm
double numberOfSteppsToStrip_CUTTER = 0;
void calculateStepps()
{
    if (0.5 > wireDiameter)
    {
        numberOfSteppsToStrip_CUTTER = numberOfSteppsToStripMinInterval * 200 - numberOfSteppsToStripMinInterval * (0.5 - wireDiameter) * 200;
    }
    else if (0.5 < wireDiameter)
    {
        numberOfSteppsToStrip_CUTTER = numberOfSteppsToStripMinInterval * 200 + numberOfSteppsToStripMinInterval * (wireDiameter - 0.5) * 200;
    }
    else
    {
        numberOfSteppsToStrip_CUTTER = 5000;
    }
    stepsForRemoveLeftIsolation = leftIsolationRemove * stepsPerRevolution / lengthPerStep_EXTRUDER;
    Serial.print("LEWA : ");
    Serial.println(stepsForRemoveLeftIsolation);
    Serial.print("dlugosc : ");
    Serial.println(wireLength);
    Serial.print("stepy :");
    Serial.println(stepsPerRevolution);
    Serial.print("lengthPerCostam");
    Serial.println(lengthPerStep_EXTRUDER);

    Serial.print("SRODEK : ");
    stepsForRemoveRightIsolation = wireLength * 10 * stepsPerRevolution / lengthPerStep_EXTRUDER;

    Serial.println(stepsForRemoveRightIsolation);
    stepsForCutTheWire_EXTRUDER = rightIsolationRemove * stepsPerRevolution / lengthPerStep_EXTRUDER;
    Serial.print("PRAWA : ");

    Serial.println(stepsForCutTheWire_EXTRUDER);
}