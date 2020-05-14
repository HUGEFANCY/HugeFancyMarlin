
#include <U8g2lib.h>
#include <Wire.h>


U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // Slow mode, requires less memory
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // Fast mode, requires much memory

void setup_Oled()
{
  u8g2.begin();
  u8g2.clearBuffer(); // clear the internal memory
  u8g2.setFont(u8g2_font_fub35_tn); // 791 bytes
}

void Oled()
{
  u8g2.clearBuffer(); // clear the internal memory
  u8g2.drawStr(0, 10, "Hello World!"); // write something to the internal memory
  u8g2.sendBuffer(); // transfer internal memory to the display
}
