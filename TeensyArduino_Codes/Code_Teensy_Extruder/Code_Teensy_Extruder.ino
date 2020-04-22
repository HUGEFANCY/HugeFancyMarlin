#include <Arduino.h>

unsigned long currentMillis = 0;
bool once = true;

// Zielwerte aus Marlin
int targetTempExtruderMarlin = 0; // max 9 Bit = 511°C
int RealTempExtruderForMarlin = 33; // max 9 Bit = 511°C
byte PwmValuePartCoolingFanMarlin = 0;



// Extruder
int TempExtruderObenrum = 0; // max 9 Bit = 511°C
int TempExtruderUntenrum = 0; // max 9 Bit = 511°C
bool LuefterObenrum = false;
bool LuefterObenUntenrum = false;

// Wasserkühlung
int TempWatercoolingCold = 0; // max 9 Bit = 511°C
int TempWatercoolingWarm = 0; // max 9 Bit = 511°C

byte ExtruderCoolingStatusMarlin = 0; // 0 = off, 1 = on // muss 8 Bit, statt boolean sein
byte pwmValuePartCoolingFan = 0; // max 8 Bit = 255

float prozentTankladung = 0;
void setup()
{
  Serial.begin(9600); // serieller Monitor
  delay(100);

  RS485_setup();
  TM1637_setup();
  Motoren_setup();

  
  Serial.println("Setup fertig");
}

void loop()
{
  currentMillis = millis(); // Für das periodische Aufrufen von diversen Funktionen ohne ein delay zu verursachen

  RS485_Extruder_CheckIfUpdateAvalible();
  //RS485_Test();
  TM1637_update();
  
  //watchdog_gameover();

  // Hier Platz für Einwegcode
  if (once == true)
  {
    once = false; 
  }

  
  SerialTastatur_CheckKeys();
  
}
