#include <Arduino.h>

void setup()
{
  Serial.begin(9600); // serieller Monitor

  RS485_setup();
  TM1637_setup();
}

void loop()
{
  RS485_signalAvailable();
}
