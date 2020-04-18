#include <Arduino.h>

// Zielwerte aus Marlin
int targetTempExtruderMarlin = 0; // max 9 Bit = 511°C
byte PwmValuePartCoolingFanMarlin = 0; // 0 = off, 1 = on // muss 8 Bit, statt boolean sein

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

  //RS485_Test_Sent(targetTempExtruderMarlin);

  RS485_updateVaribles(); 
  // ### ToDo aufrufen im Intervall von 1 Sekunde oder immer wenn I2C neues verkündet
  // ### ToDo bzw. wenn lange nichts mehr von Marlin kommt ABBRUCH!!!!
}
