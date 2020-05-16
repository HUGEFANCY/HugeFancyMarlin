
#include <U8g2lib.h>
#include <Wire.h>
#include <stdlib.h>


U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

Metro Metro_OledRefresh = Metro(1000);



void setup_Oled()
{
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.clear();
  u8x8.setFlipMode(1);
}

void Oled_1()
{
  u8x8.drawString(1, 1, "1");
}

void Oled_2()
{
  u8x8.drawString(1, 1, "2");
}

void loop_Oled()
{
  // for itoa function
  char buf[10];
  int decimal = 10;

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
}

void Oled(int zahl, int zeile)
{
  // for itoa function
  char buf[10];
  int decimal = 10;
  u8x8.setInverseFont(true);

  //10=Dezimalsystem
  u8x8.drawString(0, zeile, "   ");
  u8x8.drawString(0, zeile, itoa(zahl, buf, decimal));
  u8x8.setInverseFont(false);
}
