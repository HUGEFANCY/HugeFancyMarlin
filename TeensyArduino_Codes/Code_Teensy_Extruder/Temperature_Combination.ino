/*
*   Function to combine two Temperatures 
*   this is done because we have two heating zones but Marlin Firmware only takes
*   one Hotend temperature  
*   
*   Naming CONVENTIONS:
*   Zone1 is the Heating Zone at the top 
*        its temperature is offset from Zone2 by Zone1_TargetOffset
*   Zone2 is the Heating Zone at the tip of the extruder 
*/
const int waitErr = 10;

void CombineRealTemps()
{
    int err_Z1 = 0, err_Z2  = 0;
    err_Z1 += TargetTemperatureZone_1 - RealTemperatureZone_1;
    err_Z2 += TargetTemperatureZone_2 - RealTemperatureZone_2;

    //TODO combine first if and last else statement:
    //if (abs(err_Z2) > waitErr) 
    //{   //if Z2 is more than waitErr° lower/higher than the target set its RealTemp as CombinedTemp
    //    CombinedRealTempExtruder = RealTemperatureZone_2;
    //}

    if ((abs(err_Z2) < waitErr) & (abs(err_Z1) > waitErr))
    {   //if Z2 is less than waitErr° lower/higher than the target 
        //  and Z1 is farther than waitErr°
        // set the CombinedTemp as TargetTemp - waitErr
        CombinedRealTempExtruder = TargetTemperatureZone_2 - waitErr;
    }
    else
    {   //if Z2 is more than waitErr° lower/higher than the target
        //  or both are within waitErr° from their target 
        // set the CombinedTemp as Z2 RealTemp
        CombinedRealTempExtruder = RealTemperatureZone_2;
    }
    
}

void PrintCombTemps()
{
    //Serial.print(",");
    //Serial.print("TargetTempfromMarlin:  ");
    //Serial.print(TargetTempExtruderMarlin);
    //Serial.print(",");
    //Serial.print("TargetTemp1:");
    Serial.print(TargetTemperatureZone_1);
    Serial.print(",");
    //Serial.print("TargetTemp2:");
    Serial.print(TargetTemperatureZone_2);
    Serial.print(",");
    //Serial.print("CombinedRealTempExtruder:");
    //Serial.print(CombinedRealTempExtruder);
    //Serial.print(",");
    //Serial.print("TZone1="); 
    //Serial.print(RealTemperatureZone_1);
    Serial.print(AveragedRealTempZone_1);
    Serial.print(",");
    //Serial.print("TZone2="); 
    // Serial.print(RealTemperatureZone_2);
    Serial.print(AveragedRealTempZone_2);
    Serial.print(",");

    //Serial.print(LuefterZone_1);
    //Serial.print(",");
    Serial.print(HeaterZone_1);
    Serial.print(",");
    //Serial.print(LuefterZone_2);
    //Serial.print(",");
    Serial.print(HeaterZone_2);
    Serial.print(",");

    Serial.print(HeatPowerZone_1);
    Serial.print(",");
    Serial.print(HeatPowerZone_2);
    Serial.print(",");

    Serial.println();
}