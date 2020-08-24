/*
        DIY Arduino based RC Transmitter
  by Dejan Nedelkovski, www.HowToMechatronics.com
  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/


  Joystick by www.HowToMechatronics.com
*/

int TargetTemperatureZone_1 = 0; // max 8 Bit = 255°C
int TargetTemperatureZone_2 = 0; // max 8 Bit = 255°C
int NewTargetTemp_Zone1 = 0;
int NewTargetTemp_Zone2 = 0;
bool NewTargetTempAvalible_Zone1 = false;
bool NewTargetTempAvalible_Zone2 = false;

int PwmValuePartCoolingFanMarlin = 0;

int RealTemperatureZone_1 = 0; // max 8 Bit = 255°C // TEST ### ToDo
int RealTemperatureZone_2 = 0; // max 8 Bit = 255°C

int wheelcount_A = 0;
int wheelcount_B = 0;
int ColorTime255_L = 0;
int ColorTime255_R = 0;
int ColorTime255_shift = 0;



#include <Arduino.h>
#include <Metro.h> //Include Metro library


void setup()
{
  Serial.begin(9600);
  delay(500);

  setup_JoystickInputs();
  setup_Funk();
  setup_Oled();
  Serial.println("Setup end");
}


void loop()
{
  loop_Inputs();
  loop_FunkCheck();
  loop_SerialDataOutput();
  loop_Oled();
}
