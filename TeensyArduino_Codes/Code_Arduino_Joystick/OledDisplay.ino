
#include <U8g2lib.h>
#include <Wire.h>
#include <stdlib.h>


U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

Metro Metro_OledRefresh = Metro(250);

void setup_Oled()
{
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.clear();
  u8x8.setFlipMode(1);
}

String OledModus = "none";


void loop_Oled()
{
  // for itoa function
  char buf[10];
  int decimal = 10;

  if ((Joystick.tSwitch1 == true) and (Joystick.tSwitch2 == false)) // Modus Temperatur
  {
    if (Metro_OledRefresh.check() == true)
    {
      if (OledModus != "temp")
      {
        u8x8.clear();
        u8x8.setFlipMode(1);
        OledModus = "temp";
      }
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
  else if ((Joystick.tSwitch1 == false) and (Joystick.tSwitch2 == false)) // Modus Lüfter
  {
    if (Metro_OledRefresh.check() == true)
    {
      if (OledModus != "fan")
      {
        u8x8.clear();
        u8x8.setFlipMode(1);
        OledModus = "fan";
      }
      u8x8.drawString(0, 0, "PART COOLING");
    }
    PotiNewPWMCoolingValue();
  }


  // INDIVIDUALLY COLOR MODE
  if ((Joystick.tSwitch2 == true) and (Joystick.tSwitch2 == true))
  {
    if (Metro_OledRefresh.check() == true)
    {
      if (OledModus != "color_i")
      {
        u8x8.clear();
        u8x8.setFlipMode(1);
        OledModus = "color_i";
      }
      u8x8.drawString(0, 0, "INDIVIDUALLY COLOR");
      u8x8.drawString(0, 4, "Farbrad A: ");
      u8x8.drawString(0, 6, "Farbrad B: ");
    }
  }

  // PERIODICALLY COLOR MODE
  if ((Joystick.tSwitch2 == true) and (Joystick.tSwitch2 == false))
  {
    if (Metro_OledRefresh.check() == true)
    {
      if (OledModus != "color_p")
      {
        u8x8.clear();
        u8x8.setFlipMode(1);
        OledModus = "color_p";
      }
      u8x8.drawString(0, 0, "PERIODICALLY COLOR");
      u8x8.drawString(0, 4, "Farbrad A: ");
      u8x8.drawString(0, 6, "Farbrad B: ");
    }
    PotiNewColorTimeValue_A();
    PotiNewColorTimeValue_B();
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


void loop_ColorWheelButtons()
{

  // INDIVIDUALLY COLOR MODE
  if ((Joystick.tSwitch2 == true) and (Joystick.tSwitch2 == true))// color mode 1
  {
    if ((LastimeData.button1 != Joystick.button1) and (Joystick.button1 == true))
    {
      LastimeData.button1 = Joystick.button1;

      if (FunkData_Color_A() == true)
      {
        wheelcount_A++;
        Oled(wheelcount_A, 4, 12);
      }
      Serial.println("Farbrad A");
    }
    if ((LastimeData.button2 != Joystick.button2) and (Joystick.button2 == true))
    {
      LastimeData.button2 = Joystick.button2;
      if (FunkData_Color_B() == true)
      {
        wheelcount_B++;
        Oled(wheelcount_B, 6, 12);
      }
      Serial.println("Farbrad B");
    }
  }

  // PERIODICALLY COLOR MODE
  if ((Joystick.tSwitch2 == true) and (Joystick.tSwitch2 == false))
  {
    if ((LastimeData.button4 != Joystick.button4) and (Joystick.button1 == true))
    {
      LastimeData.button4 = Joystick.button4;
      if (FunkData_Color_Periodically() == true)
      {
        u8x8.drawString(0, 0, "GESENDET !");
        (OledModus != "gesendet");
      }
    }
  }
}


void PotiNewColorTimeValue_A()
{
  if (LastimeData.pot1 != Joystick.pot1)
  {
    Oled(Joystick.pot1, 4, 12);
    LastimeData.pot1 = Joystick.pot1;
    ColorTime255_A = Joystick.pot1;
  }
}
void PotiNewColorTimeValue_B()
{
  if (LastimeData.pot2 != Joystick.pot2)
  {
    Oled(Joystick.pot2, 4, 12);
    LastimeData.pot2 = Joystick.pot2;
    ColorTime255_B = Joystick.pot2;
  }
}

void loop_PWM()
{
  if ((Joystick.tSwitch2 == false) and (Joystick.tSwitch1 == false))
  {
    if ((LastimeData.button4 != Joystick.button4) and (Joystick.button4 == true))
    {
      LastimeData.button4 = Joystick.button4;
      FunkData_Temp();
    }
  }
}
