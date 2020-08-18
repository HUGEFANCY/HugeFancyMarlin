 
#include <U8g2lib.h>
#include <Wire.h>
#include <stdlib.h>


U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

Metro Metro_OledRefresh = Metro(500);

void setup_Oled()
{
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.clear();
  u8x8.setFlipMode(1);
}


void loop_Oled()
{
  // for itoa function
  char buf[10];
  int decimal = 10;

  if (Joystick.tSwitch1 == true) // TEMPMODUS
  {
    if (Metro_OledRefresh.check() == true)
    {
      u8x8.drawString(0, 0, "NEW  TARGET REAL");

      u8x8.drawString(7, 3, "   ");
      u8x8.drawString(7, 3, itoa(TargetTemperatureZone_1, buf, decimal));
      u8x8.drawString(13, 3, "   ");
      u8x8.drawString(13, 3, itoa(RealTemperatureZone_1, buf, decimal));

      u8x8.drawString(7, 5, "   ");
      u8x8.drawString(7, 5, itoa(TargetTemperatureZone_2, buf, decimal));
      u8x8.drawString(13, 5, "   ");
      u8x8.drawString(13, 5, itoa(RealTemperatureZone_2, buf, decimal));
    }
    // Check these functions for changes
    PotiNewTargetTemp();
    ApplyNewTargetTemp();
  }
  else if (Joystick.tSwitch1 == false)
  {
    if (Metro_OledRefresh.check() == true)
    {
      u8x8.drawString(0, 0, "PART COOLING");
    }
    PotiNewPWMCoolingValue();
  }
}

void Oled(int zahl, int zeile, int zeilenstart)
{
  // for itoa function
  char buf[10];
  int decimal = 10;
  u8x8.setInverseFont(true);

  //10=Dezimalsystem
  u8x8.drawString(zeilenstart, zeile, "   ");
  u8x8.drawString(zeilenstart, zeile, itoa(zahl, buf, decimal));
  u8x8.setInverseFont(false);
}


void PotiNewTargetTemp()
{
  if ((LastimeData.pot1 != Joystick.pot1) and (Joystick.button1 == 0))
  {
    Oled(Joystick.pot1, 3, 0);
    LastimeData.pot1 = Joystick.pot1;
    NewTargetTemp_Zone1 = Joystick.pot1;
    NewTargetTempAvalible_Zone1 = true;
  }

  if ((LastimeData.pot2 != Joystick.pot2) and (Joystick.button2 == 0))
  {
    Oled(Joystick.pot2, 5, 0);
    LastimeData.pot2 = Joystick.pot2;
    NewTargetTemp_Zone2 = Joystick.pot2;
    NewTargetTempAvalible_Zone2 = true;

  }
}

void ApplyNewTargetTemp()
{

  if ((NewTargetTempAvalible_Zone1 == true) and (Joystick.button4 == 0))
  {
    TargetTemperatureZone_1 = NewTargetTemp_Zone1;
    u8x8.clear();
    Oled(TargetTemperatureZone_1, 3, 7);

    NewTargetTempAvalible_Zone1 = false;
    FunkData_Temp();
  }

  if ((NewTargetTempAvalible_Zone2 == true) and (Joystick.button4 == 0))
  {
    TargetTemperatureZone_2 = NewTargetTemp_Zone2;
    u8x8.clear();
    Oled(TargetTemperatureZone_2, 5, 7);

    NewTargetTempAvalible_Zone2 = false;
    FunkData_Temp();
  }
}


void PotiNewPWMCoolingValue()
{
  if (LastimeData.pot1 != Joystick.pot1)
  {
    Oled(Joystick.pot1, 3, 0);
    LastimeData.pot1 = Joystick.pot1;
    PwmValuePartCoolingFanMarlin = Joystick.pot1;
  }
}
