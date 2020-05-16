#include <Arduino.h>
#include <math.h>
#include <Metro.h> // Include the Metro library // https://www.pjrc.com/teensy/td_libs_Metro.html

unsigned long currentMillis = 0;
int analog_resolution = 10; // sets resolution of analog writing as exponent of 2 (2^12=4096)


// Extruder
int TargetTempExtruderMarlin = 0; // max 9 Bit = 511° // Target Values from Marlin and Real Values from Hotend
// ->
int TargetTemperatureZone_1 = 0; // max 9 Bit = 511°C
int TargetTemperatureZone_2 = 0; // max 9 Bit = 511°C
// ->
int RealTemperatureZone_1 = 0; // max 9 Bit = 511°C
int RealTemperatureZone_2 = 0; // max 9 Bit = 511°C
// ->
int CombinedRealTempertureExtruderForMarlin = 44; // max 9 Bit = 511°C

byte PwmValuePartCoolingFanMarlin = 0;
// ->
bool LuefterZone_1 = false;
bool LuefterZone_2 = false;

// Wasserkühlung
int TempWatercooling_In = 0; // max 9 Bit = 511°C
int TempWatercooling_Out = 0; // max 9 Bit = 511°C

byte ExtruderCoolingStatusMarlin = 0; // 0 = off, 1 = on // muss 8 Bit, statt boolean sein

float prozentTankladung = 0;
void setup()
{
  Serial.begin(9600); // serieller Monitor
  delay(100);

  analogReadResolution(analog_resolution);

  RS485_setup();
  TM1637_setup();
  Motoren_setup();
  PT100_MAX31865_setup();
  Relays_setup();
  RGB_setup();


  Serial.println("Setup fertig");
}

void loop()
{
  currentMillis = millis(); // Für das periodische Aufrufen von diversen Funktionen ohne ein delay zu verursachen

  RS485_Extruder_CheckIfUpdateAvalible();
  PT100_MAX31865_loop();
  TM1637_update();
  TempWasser_loop();

  //watchdog_gameover();



  SerialTastatur_CheckKeys();

}
