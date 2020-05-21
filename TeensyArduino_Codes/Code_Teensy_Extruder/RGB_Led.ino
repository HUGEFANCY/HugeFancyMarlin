#include <FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 23
CRGB leds[NUM_LEDS];

void RGB_setup()
{
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  delay(200);
  leds[0] = CRGB(0, 0, 0); 
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  delay(200);
  leds[0] = CRGB(0, 0, 0);
  FastLED.show();
  delay(10);
  leds[0] = CRGB(0, 255, 0);
  FastLED.show();
  delay(200);
  leds[0] = CRGB(0, 0, 0);
  FastLED.show();
  delay(10);
  leds[0] = CRGB(0, 0, 255);
  FastLED.show();
  delay(200);
  leds[0] = CRGB(0, 0, 0);
  FastLED.show();
  delay(10);
}
