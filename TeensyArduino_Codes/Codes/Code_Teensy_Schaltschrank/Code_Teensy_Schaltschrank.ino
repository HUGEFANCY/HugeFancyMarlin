#include <Arduino.h>

unsigned long currentMillis = 0;

// Zielwerte aus Marlin
int targetTempExtruderMarlin = 0; // max 9 Bit - 1 = 510°C
int RealTempExtruderForMarlin = 0; // max 9 Bit - 1 = 510°C
byte PwmValuePartCoolingFanMarlin = 0;

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
  if (targetTempExtruderMarlin >= 510)
  {
    targetTempExtruderMarlin = 0;
  }
  
  delay(1000);

  RS485_SentUpdateVaribles(); 
  
  //watchdog_gameover();
}
