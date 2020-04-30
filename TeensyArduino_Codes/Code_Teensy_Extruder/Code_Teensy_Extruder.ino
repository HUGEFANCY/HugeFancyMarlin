#include <Arduino.h>

#include <Metro.h> // Include the Metro library // https://www.pjrc.com/teensy/td_libs_Metro.html

unsigned long currentMillis = 0;
bool once = true;

// Zielwerte aus Marlin
int targetTempExtruderMarlin = 0; // max 9 Bit = 511°C
int CombinedTempertureExtruderForMarlin = 33; // max 9 Bit = 511°C
byte PwmValuePartCoolingFanMarlin = 0;



// Extruder
int RealTemperatureZone_1 = 0; // max 9 Bit = 511°C
int RealTemperatureZone_2 = 0; // max 9 Bit = 511°C
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
  PT100_MAX31865_setup();
  Relays_setup();
  //RGB_setup();

  
  Serial.println("Setup fertig");
}

void loop()
{
  currentMillis = millis(); // Für das periodische Aufrufen von diversen Funktionen ohne ein delay zu verursachen

  RS485_Extruder_CheckIfUpdateAvalible();
  PT100_MAX31865_loop();
  TM1637_update();
  
  watchdog_gameover();

  // Hier Platz für Einwegcode
  if (once == true)
  {
    once = false; 
  }

  
  SerialTastatur_CheckKeys();
  
}
