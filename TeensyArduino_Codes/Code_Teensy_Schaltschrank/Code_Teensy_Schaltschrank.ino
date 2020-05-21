#include <Arduino.h>

unsigned long currentMillis = 0;

unsigned long RS485_gesendet_LastUpdatePreviousMillis = 0;

// Global variables, TargetTemp from Marlin and RealTemp from Hotend
int TargetTempExtruderMarlin = 0; // max 9 Bit - 1 = 510°C
int RealTempExtruderForMarlin = 0; // max 9 Bit - 1 = 510°C
byte PwmValuePartCoolingFanMarlin = 0;  //not yet implemented 

void setup()
{
  Serial.begin(9600); 
  delay(100);

  RS485_setup();
  setup_Funk();
  RGB_setup();
  Relays_setup();
  I2C_Marlin_setup();

  Serial.println("Setup End");
}

void loop()
{
  currentMillis = millis();

  SerialTastatur_CheckKeys();

  // Sende jede Sekunde eine neue Ziffer // Testcode

  // Aufruf ohne Blockieren alle RS485_SendIntervall ms
  const int RS485_SendIntervall = 1000;
  if (currentMillis - RS485_gesendet_LastUpdatePreviousMillis >= RS485_SendIntervall) 
  {
    //Serial.println("RS485_SendIntervall");
    RS485_gesendet_LastUpdatePreviousMillis = currentMillis;
    TargetTempExtruderMarlin++;
    if (TargetTempExtruderMarlin >= 510)
    {
      TargetTempExtruderMarlin = 0;
    }
    RS485_Schaltschrank_Send_Statusupdate();
  }
  
  RS485_Schaltschrank_CheckIfUpdateAvalible();
  loop_FunkCheck();

  //watchdog_gameover();
}
