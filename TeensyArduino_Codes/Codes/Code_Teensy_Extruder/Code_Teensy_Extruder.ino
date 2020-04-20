#include <Arduino.h>

unsigned long currentMillis = 0;

// Zielwerte aus Marlin
int targetTempExtruderMarlin = 0; // max 9 Bit = 511°C
int RealTempExtruderForMarlin = 33; // max 9 Bit = 511°C
byte PwmValuePartCoolingFanMarlin = 0;

byte ExtruderCoolingStatusMarlin = 0; // 0 = off, 1 = on // muss 8 Bit, statt boolean sein
byte pwmValuePartCoolingFan = 0; // max 8 Bit = 255


void setup()
{
  Serial.begin(9600); // serieller Monitor

  RS485_setup();
  TM1637_setup();
  Farbmischer_setup();
}

void loop()
{
  currentMillis = millis(); // Für das periodische Aufrufen von diversen Funktionen ohne ein delay zu verursachen

  RS485_CheckIfUpdateAvalible();
  //RS485_Test();
  TM1637_update();
  
  //watchdog_gameover();
}
