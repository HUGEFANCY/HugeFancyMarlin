// TM1637 // 4 Digit LED Display to visualise Temperatures

// PINOUT
// VCC -> 5V
// GND -> GND Teensy
// CLC -> PIN 2 Teensy
// DIO -> PIN 3 Teensy

#include <TM1637.h> // siehe Beispielcode Arduino

const byte TM1637_CLK = 2;
const byte TM1637_DIO = 3;

TM1637 TM1637_T0(TM1637_CLK, TM1637_DIO);

void TM1637_setup()
{
  TM1637_T0.init();
  delay(100);
}

void TM1637_show(int i)
{
  TM1637_T0.dispNumber(i);
}
