/*
        DIY Arduino based RC Transmitter
  by Dejan Nedelkovski, www.HowToMechatronics.com
  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

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
}
