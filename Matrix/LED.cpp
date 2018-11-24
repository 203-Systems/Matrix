#include "LED.h"

LED::LED()
{
  // CRGB leds[NUM_TOTAL_LEDS];
  // FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_TOTAL_LEDS);
  // FastLED.setBrightness(Brightness);
  // delay(50);
  // LED::Fill(0);
  // if(POWERCORD)
  //{
  //   CRGB pc_leds[NUM_POWERCORD_LEDS];
  //   FastLED.addLeds<WS2812B, POWERCORD_PIN>(pc_leds, NUM_POWERCORD_LEDS);
  // }
};

void LED::Fill(uint64_t WRGB)
{
  //fill_solid(leds,NUM_TOTAL_LEDS,CRGB::Black);
  for(int i = 0; i < NUM_TOTAL_LEDS; i++)
  {
    leds[i] = WRGB;
  }
  FastLED.show();
}
void LED::Off(uint8_t index)
{
  leds[index] = 0;
}

void LED::On(uint8_t index)
{
  leds[index] = 0xffffff;
}

void LED::SetW(uint8_t index, uint8_t w)
{
  leds[index] = w;
}

void LED::SetRGB(uint8_t index, uint8_t R, uint8_t G, uint8_t B)
{
  //TODO
}

void LED::SetWRGB(uint8_t index, uint8_t W, uint8_t R, uint8_t G, uint8_t B)
{
  //TODO
}

void LED::SetHEX(uint8_t index, uint64_t WRGB)
{
  leds[index] = WRGB;
}

void LED::SetPallette(uint8_t pallette, uint8_t index, uint8_t colour)
{
  LED::SetHEX(index,ColourPallette[pallette][colour]);
}

void LED::Update()
{
  FastLED.show();
}

void LED::Rainbow()
{
  // int hue = 0;
  //
  // while(true)
  // {
  //   fill_rainbow(leds, NUM_LEDS, hue++);
  //   FastLED.show();
  //   if(hue == 255)
  //   hue = 1;
  //   delay(5);
  // }
}
