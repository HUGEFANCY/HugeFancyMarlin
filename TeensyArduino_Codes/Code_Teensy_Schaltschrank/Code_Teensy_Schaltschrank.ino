#include <Arduino.h>

unsigned long currentMillis = 0;

unsigned long RS485_gesendet_LastUpdatePreviousMillis = 0;

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
  unsigned long currentMillis = millis();

  //SerialTastatur_CheckKeys();

  // Sende jede Sekunde eine neue Ziffer // Testcode


  // Aufruf ohne Blockieren alle RS485_Sendezeit ms
  const int RS485_Sendezeit = 1000;
  if (currentMillis - RS485_gesendet_LastUpdatePreviousMillis >= RS485_Sendezeit)
  {
    Serial.println("RS485_Sendezeit");
    RS485_gesendet_LastUpdatePreviousMillis = currentMillis;
    targetTempExtruderMarlin++;
    if (targetTempExtruderMarlin >= 510)
    {
      targetTempExtruderMarlin = 0;
    }
    RS485_Schaltschrank_Sent_Statusupdate();
  }
  
  
  RS485_Schaltschrank_CheckIfUpdateAvalible();

  //watchdog_gameover();
}