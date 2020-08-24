
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


// Oled Zahl setzen
void OledZahl(int zeile, int spalte, int zahl, boolean invertiert)
{
  // for itoa function
  char buf[10];
  int decimal = 10;
  u8x8.setInverseFont(invertiert);

  //10=Dezimalsystem
  u8x8.drawString(spalte, zeile, "   ");
  u8x8.drawString(spalte, zeile, itoa(zahl, buf, decimal));
  u8x8.setInverseFont(false);
}

// Oled Zahl setzen
void OledString(int zeile, int spalte, int Wort, boolean invertiert)
{
  u8x8.setInverseFont(invertiert);
  u8x8.drawString(spalte, zeile, Wort);
  u8x8.setInverseFont(false);
}

void OledClear()
{
  u8x8.clear();
}


/// OLED TEXT MODUS SCHREIBEN ////////////////////////////
void loop_Oled()
{
  //////////////////////////// Modus Temperatur ////////////////////////////
  if ((Joystick.tSwitch2 == false) and (Joystick.tSwitch1 == true))
  {
    if (Metro_OledRefresh.check() == true)
    {
      if (OledModus != "temp")
      {
        OledClear();
        OledModus = "temp";
      }
      OledString(0, 0, "NEW  TARGET REAL", false);

      OledString(3, 7, "   ", false);
      OledZahl(3, 7, TargetTemperatureZone_1, false);
      OledString(3, 13, "   ", false);
      OledZahl(3, 13, RealTemperatureZone_1, false);


      OledString(5, 7, "   ", false);
      OledZahl(5, 7, TargetTemperatureZone_2, false);
      OledString(5, 13, "   ", false);
      OledZahl(5, 13, RealTemperatureZone_2, false);
    }
    // Check these functions for changes
    PotiNewTargetTemp();
    ApplyNewTargetTemp();
  }

  //////////////////////////// Part Cooling ////////////////////////////
  else if ((Joystick.tSwitch2 == false) and (Joystick.tSwitch1 == false))
  {
    if (Metro_OledRefresh.check() == true)
    {
      if (OledModus != "fan")
      {
        if (OledModus != "fan_sent")
        {
          // reset
          OledClear();
          PwmValuePartCoolingFanMarlin = -1;
        }
        OledModus = "fan";
        OledString(0, 0, "Part Cooling", false);
      }
    }
    // Check these functions for changes
    if (Joystick.button1 == false)
    {
      OledString(3, 0, "Velocity = ", false);
      PwmValuePartCoolingFanMarlin = Joystick.pot1;
      int PwmValuePartCoolingFanMarlin_prozent = map(PwmValuePartCoolingFanMarlin, 0, 255, 0, 100);
      OledZahl(3, 11, PwmValuePartCoolingFanMarlin_prozent, true);
      OledString(3, 15, "%", false);
    }
    // senden
    if ((LastimeData.button4 != Joystick.button4) and (Joystick.button4 == false) and (PwmValuePartCoolingFanMarlin >= 0))
    {
      if (FunkData_Temp_PWM() == true)
      {
        OledString(0, 0, "Part Cooling", true);
        OledModus = "fan_sent";
        delay(1000);
      }
    }
  }

  //////////////////////////// Click Color MODE ////////////////////////////
  else if ((Joystick.tSwitch2 == true) and (Joystick.tSwitch1 == true))
  {
    if (Metro_OledRefresh.check() == true)
    {
      if (OledModus != "color_click")
      {
        OledClear();
        OledModus = "color_click";
      }
      OledString(0, 0, "Color Click", false);
      OledString(4, 0, "Color L: ", false);
      OledString(6, 0, "Color R: ", false);
    }
    // Check these functions for changes
    if ((LastimeData.button1 != Joystick.button1) and (Joystick.button1 == true))
    {
      LastimeData.button1 = Joystick.button1;
      if (FunkData_clickColor(1,0) == true)
      {
        wheelcount_A++;
        OledZahl(4, 12, wheelcount_A, true);
      }
    }
    if ((LastimeData.button2 != Joystick.button2) and (Joystick.button2 == true))
    {
      LastimeData.button2 = Joystick.button2;
      if (FunkData_clickColor(0,1) == true)
      {
        wheelcount_B++;
        OledZahl(6, 12, wheelcount_B, true);
      }
    }
  }

  //////////////////////////// Color Metronome MODE ////////////////////////////
  if ((Joystick.tSwitch2 == true) and (Joystick.tSwitch1 == false))
  {
    if (Metro_OledRefresh.check() == true)
    {
      if (OledModus != "color_metronome")
      {
        if (OledModus != "color_metronome_sent")
        {
          // reset
          OledClear();
          ColorTime255_R = -1;
          ColorTime255_L = -1;
          ColorTime255_shift = -1;
        }
        OledModus = "color_metronome";
        OledString(0, 0, "Color Metronome", false);
        OledString(3, 0, "Delay L: ", false);
        OledString(5, 0, "Delay R: ", false);
        OledString(7, 0, "Shift L/R: ", false);
      }
    }
    // Check these functions for changes
    if (Joystick.button1 == false)
    {
      ColorTime255_L = Joystick.pot1;
      int ColorTimeSeconds_L = map(ColorTime255_L, 0, 255, 0, 600);
      OledZahl(3, 11, ColorTimeSeconds_L, true);
      OledString(3, 15, "s", false);
    }
    if (Joystick.button2 == false)
    {
      ColorTime255_R = Joystick.pot1;
      int ColorTimeSeconds_R = map(ColorTime255_R, 0, 255, 0, 600);
      OledZahl(5, 11, ColorTimeSeconds_R, true);
      OledString(5, 15, "s", false);
    }
    if (Joystick.button3 == false)
    {
      ColorTime255_shift = Joystick.pot1;
      int ColorTimeSeconds_shift = map(ColorTime255_shift, 0, 255, 0, 600);
      OledZahl(7, 11, ColorTimeSeconds_shift, true);
      OledString(7, 15, "s", false);
    }
    // senden
    if ((LastimeData.button4 != Joystick.button4) and (Joystick.button4 == false) and (ColorTime255_R >= 0) and (ColorTime255_L >= 0) and (ColorTime255_shift >= 0))
    {
      if (FunkData_colorMetronome() == true)
      {
        OledString(0, 0, "Color Metronome", true);
        OledModus = "color_metronome_sent";
        delay(1000);
      }

    }
  }
}





// veraltet aber noch integriert
void PotiNewTargetTemp()
{
  if ((LastimeData.pot1 != Joystick.pot1) and (Joystick.button1 == 0))
  {
    OledZahl(3, 0, Joystick.pot1, true);
    LastimeData.pot1 = Joystick.pot1;
    NewTargetTemp_Zone1 = Joystick.pot1;
    NewTargetTempAvalible_Zone1 = true;
  }
  if ((LastimeData.pot2 != Joystick.pot2) and (Joystick.button2 == 0))
  {
    OledZahl(5, 0, Joystick.pot2, true);
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
    OledZahl(3, 7, TargetTemperatureZone_1, true);

    NewTargetTempAvalible_Zone1 = false;
    FunkData_Temp_PWM();
  }

  if ((NewTargetTempAvalible_Zone2 == true) and (Joystick.button4 == 0))
  {
    TargetTemperatureZone_2 = NewTargetTemp_Zone2;
    u8x8.clear();
    OledZahl(5, 7, TargetTemperatureZone_2, true);

    NewTargetTempAvalible_Zone2 = false;
    FunkData_Temp_PWM();
  }
}
