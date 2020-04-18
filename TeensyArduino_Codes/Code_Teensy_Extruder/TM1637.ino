// TM1637 // 4 Digit LED Display to visualise Temperatures, etc.

#include <TM1637.h> // siehe Beispielcode Arduino

// PINOUT
// VCC -> 5V
// GND -> GND Teensy

// TempExtruderObenrum // Rot
const byte TM1637_TempExtruderObenrum_CLK = 2;
const byte TM1637_TempExtruderObenrum_DIO = 3;
TM1637 TM1637_TempExtruderObenrum(TM1637_TempExtruderObenrum_CLK, TM1637_TempExtruderObenrum_DIO);

/*
// TempExtruderUntenrum // Rot
const byte TM1637_TempExtruderUntenrum_CLK = 4;
const byte TM1637_TempExtruderUntenrum_DIO = 5;
TM1637 TM1637_TempExtruderUntenrum(TM1637_TempExtruderUntenrum_CLK, TM1637_TempExtruderUntenrum_DIO);

// TempWatercoolingWarm // Blau
const byte TM1637_TempWatercoolingWarm_CLK = 6;
const byte TM1637_TempWatercoolingWarm_DIO = 7;
TM1637 TM1637_TempWatercoolingWarm(TM1637_TempWatercoolingWarm_CLK, TM1637_TempWatercoolingWarm_DIO);

// TempWatercoolingCold // Blau
const byte TM1637_TempWatercoolingCold_CLK = 17;
const byte TM1637_TempWatercoolingCold_DIO = 9;
TM1637 TM1637_TempWatercoolingCold(TM1637_TempWatercoolingCold_CLK, TM1637_TempWatercoolingCold_DIO);

// pwmValuePartCoolingFan // Weiß
const byte TM1637_pwmValuePartCoolingFan_CLK = 10;
const byte TM1637_pwmValuePartCoolingFan_DIO = 11;
TM1637 TM1637_pwmValuePartCoolingFan(TM1637_pwmValuePartCoolingFan_CLK, TM1637_pwmValuePartCoolingFan_DIO);
*/

// Update Intervall
const int TM1637updateInterval = 333;
unsigned long TM1637updatePreviousMillis = 0; 


void TM1637_setup()
{
  TM1637_TempExtruderObenrum.init();
  delay(100);
}

void TM1637_test(int test)
{
  TM1637_TempExtruderObenrum.dispNumber(test);
}

void TM1637_update()
{
  if (currentMillis - TM1637updatePreviousMillis >= TM1637updateInterval) 
  {
    TM1637updatePreviousMillis = currentMillis; // save the last timeof the event

    TM1637_TempExtruderObenrum.dispNumber(targetTempExtruderMarlin); 
    // ### ToDo: hier später die momentane TempExtruderObenrum
    /*
    TM1637_TempExtruderUntenrum.dispNumber(TempExtruderUntenrum); 
    TM1637_TempWatercoolingWarm.dispNumber(TempWatercoolingWarm);
    TM1637_TempWatercoolingCold.dispNumber(TempWatercoolingCold);
    TM1637_pwmValuePartCoolingFan.dispNumber(pwmValuePartCoolingFan);
    */
  }
}
