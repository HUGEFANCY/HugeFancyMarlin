#include <Arduino.h>

// Zielwerte aus Marlin
int targetTempExtruderMarlin = 0; // max 9 Bit = 511°C
int ExtruderCoolingStatusMarlin = 0; // 0 = off, 1 = on // muss 8 Bit, statt boolean sein
int pwmValuePartCoolingFanMarlin = 0; // max 8 Bit = 255

void setup() 
{
  Serial.begin(9600); // serieller Monitor

  RS485_setup();
}

void loop() 
{
  //SerialTastatur_CheckKeys();

  // Sende jede Sekunde eine neue Ziffer // Testcode
  targetTempExtruderMarlin++;
  delay(1000);
  RS485_sentSignals();  
}
