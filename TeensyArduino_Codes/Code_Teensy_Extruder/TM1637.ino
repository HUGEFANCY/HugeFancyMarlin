// TM1637 // 4 Digit LED Display to visualise Temperatures, etc.

#include <TM1637Display.h>
// https://github.com/avishorp/TM1637

Metro DisplayIntervall = Metro(1000);

// PINOUT
// VCC -> 5V
// GND -> GND Teensy

// TempExtruderObenrum // Rot
const byte TM1637_TempExtruderZone_1_CLK = 2;
const byte TM1637_TempExtruderZone_1_DIO = 3;
TM1637Display TM1637_TempExtruderZone_1(TM1637_TempExtruderZone_1_CLK, TM1637_TempExtruderZone_1_DIO);


// TempExtruderUntenrum // Rot
const byte TM1637_TempExtruderZone_2_CLK = 4;
const byte TM1637_TempExtruderZon2_2_DIO = 5;
TM1637Display TM1637_TempExtruderZone_2(TM1637_TempExtruderZone_2_CLK, TM1637_TempExtruderZon2_2_DIO);

// TempWatercoolingWarm // Blau
const byte TM1637_TempWatercoolingWarm_CLK = 6;
const byte TM1637_TempWatercoolingWarm_DIO = 7;
TM1637Display TM1637_TempWatercoolingWarm(TM1637_TempWatercoolingWarm_CLK, TM1637_TempWatercoolingWarm_DIO);

// TempWatercoolingCold // Blau
const byte TM1637_TempWatercoolingCold_CLK = 8;
const byte TM1637_TempWatercoolingCold_DIO = 9;
TM1637Display TM1637_TempWatercoolingCold(TM1637_TempWatercoolingCold_CLK, TM1637_TempWatercoolingCold_DIO);

// pwmValuePartCoolingFan // Weiß
const byte TM1637_pwmValuePartCoolingFan_CLK = 10;
const byte TM1637_pwmValuePartCoolingFan_DIO = 11;
TM1637Display TM1637_pwmValuePartCoolingFan(TM1637_pwmValuePartCoolingFan_CLK, TM1637_pwmValuePartCoolingFan_DIO);

// pwmValuePartCoolingFan // Weiß
const byte TM1637_prozentTankladung_CLK = 12;
const byte TM1637_prozentTankladung_DIO = 24;
TM1637Display TM1637_prozentTankladung(TM1637_prozentTankladung_CLK, TM1637_prozentTankladung_DIO);

void TM1637_setup()
{
  TM1637_TempExtruderZone_1.clear();
  TM1637_TempExtruderZone_1.setBrightness(0x0f); // 7 max
  TM1637_TempExtruderZone_2.clear();
  TM1637_TempExtruderZone_2.setBrightness(0x0f); // 7 max
  TM1637_TempWatercoolingWarm.clear();
  TM1637_TempWatercoolingWarm.setBrightness(0x0f); // 7 max
  TM1637_TempWatercoolingCold.clear();
  TM1637_TempWatercoolingCold.setBrightness(0x0f); // 7 max
  TM1637_pwmValuePartCoolingFan.clear();
  TM1637_pwmValuePartCoolingFan.setBrightness(0x0f); // 7 max
  TM1637_prozentTankladung.clear();
  TM1637_prozentTankladung.setBrightness(0x0f); // 7 max
  delay(100);
}

void TM1637_update()
{
  if (DisplayIntervall.check() == 1)  // check if the metro has passed its interval
  {
    TM1637_TempExtruderZone_1.showNumberDec(RealTemperatureZone_1, false);
    TM1637_TempExtruderZone_2.showNumberDec(RealTemperatureZone_2, false);
    TM1637_TempWatercoolingWarm.showNumberDec(TempWatercoolingWarm, false);
    TM1637_TempWatercoolingCold.showNumberDec(targetTempExtruderMarlin, false); // ### ToDo: hier später die momentane TempExtruderObenrum
    TM1637_pwmValuePartCoolingFan.showNumberDec(pwmValuePartCoolingFan, false);
    TM1637_prozentTankladung.showNumberDec(PwmValuePartCoolingFanMarlin, false);
  }
}
