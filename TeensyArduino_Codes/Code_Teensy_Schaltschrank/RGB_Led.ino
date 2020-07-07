#include <FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 23
CRGB leds[NUM_LEDS];

void RGB_setup()
{
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  delay(20);
  RGB_Aus();
  RGB_Rot();
  delay(1000);
  RGB_Gruen();
  delay(1000);
  RGB_Blau();
  delay(1000);
  RGB_Aus();
  delay(10);
}


void RGB_Rot()
{
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();
}

void RGB_Gruen()
{
  leds[0] = CRGB(0, 255, 0);
  FastLED.show();
}

void RGB_Blau()
{
  leds[0] = CRGB(0, 0, 255);
  FastLED.show();
}

void RGB_Aus()
{
  leds[0] = CRGB(0, 0, 0);
  FastLED.show();
}
