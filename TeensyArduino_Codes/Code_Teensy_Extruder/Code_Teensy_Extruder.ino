#include <Arduino.h>
#include <math.h>  
#include <Chrono.h>  // Include the Chrono library // https://github.com/SofaPirate/Chrono

unsigned long currentMillis, startMillis = 0;
int analog_resolution = 10; // sets resolution of analog writing as exponent of 2 (2^12=4096)


// Extruder temperatures
int TargetTempExtruderMarlin = 0; // max 9 Bit = 511° // Target Values from Marlin and Real Values from Hotend
// ->
const int Zone1_TargetOffset = 5 ;  // Heating Zone 1 will be different from Zone 2
int TargetTemperatureZone_1 = 0; // max 9 Bit = 511°C
int TargetTemperatureZone_2 = 0; // max 9 Bit = 511°C

// ->
int RealTemperatureZone_1 = 0; // max 9 Bit = 511°C
int RealTemperatureZone_2 = 0; // max 9 Bit = 511°C
double AveragedRealTempZone_1 = 0; //average temperature over the last 5 measurements
double AveragedRealTempZone_2 = 0;
double HeatPowerZone_1 = 0;
double HeatPowerZone_2 = 0;
// ->
int CombinedRealTempExtruder = 0; // max 9 Bit = 511°C

byte PwmValuePartCoolingFanMarlin = 0;
// Hotend Bools
//these are status bools  that do not affect the actual prcess but simply indicate a status.
//Changing them here will not activate the relays
int LuefterZone_1 = 0;
int LuefterZone_2 = 0;
int HeaterZone_1 = 0;
int HeaterZone_2 = 0;

// Water cooling temperatures
int TempWatercooling_In = 0; // max 9 Bit = 511°C
int TempWatercooling_Out = 0; // max 9 Bit = 511°C

byte ExtruderCoolingStatusMarlin = 0; // 0 = off, 1 = on // muss 8 Bit, statt boolean sein

float prozentTankladung = 0;
void setup()
{
  delay(200);
  Serial.begin(9600);
  delay(100);

  KuehlungPWM_setup();
  KuehlungPWM();

  analogReadResolution(analog_resolution);

  RS485_setup();
  TM1637_setup();
  Motoren_setup();
  PT100_MAX31865_setup();
  Relays_setup();
  RGB_setup();
  PID_setup();

  startMillis = millis(); //start timer for periodic executions
  Serial.println("Setup fertig");
}

void loop()
{
  currentMillis = millis(); // Für das periodische Aufrufen von diversen Funktionen ohne ein delay zu verursachen

  RS485_Extruder_CheckIfUpdateAvalible();
  PT100_MAX31865_loop();
  TM1637_update();
  TempWasser_loop();
  PID_loop();
  CombineRealTemps();
  Stepper_loopWatchdogDisableSteppers();
  Stepper_loopMetronomeColor();



  //watchdog_gameover();

  SerialTastatur_CheckKeys();

  if (currentMillis - startMillis > 1000)
    {
    //Serial.print("RealTemperatureZone_1 = ");Serial.println(TargetTemperatureZone_1);
    //Serial.print("RealTemperatureZone_2 = ");Serial.println(TargetTemperatureZone_2);
    //PrintCombTemps();
    Serial.println("1000ms has passed");
    startMillis = currentMillis;
    }
}
