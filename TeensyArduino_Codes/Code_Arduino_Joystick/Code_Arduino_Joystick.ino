/*
        DIY Arduino based RC Transmitter
  by Dejan Nedelkovski, www.HowToMechatronics.com
  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/


  Joystick by www.HowToMechatronics.com
*/

int TargetTemperatureZone_1 = 111; // max 8 Bit = 255°C
int TargetTemperatureZone_2 = 222; // max 8 Bit = 255°C

int RealTemperatureZone_1 = 205; // max 8 Bit = 255°C // TEST ### ToDo
int RealTemperatureZone_2 = 210; // max 8 Bit = 255°C

#include <Arduino.h>
#include <Metro.h> //Include Metro library


void setup() 
{
  Serial.begin(9600);
  delay(100);

  setup_Inputs();
  setup_SerialDataOutput();
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
