#include "LED.h"
#include <FastLED.h>

CRGB leds[NUM_TOTAL_LEDS];

extern MatrixSystem Matrix;

LED::LED()
{
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_TOTAL_LEDS);
  //LED::SetBrightness(brightness);
  // if(POWERCORD)
  //{
  //   CRGB pc_leds[NUM_POWERCORD_LEDS];
  //   FastLED.addLeds<WS2812B, POWERCORD_PIN>(pc_leds, NUM_POWERCORD_LEDS);
  // }
};

void LED::SetBrightness(uint8_t b)
{
  FastLED.setBrightness(b);
}

void LED::Fill(uint64_t WRGB)
{
  //fill_solid(leds,NUM_TOTAL_LEDS,CRGB::Black);
  for(int i = 0; i < NUM_TOTAL_LEDS; i++)
  {
    leds[i] = WRGB;
  }
  FastLED.show();
}

void LED::SetLED(INDEXMODE indexmode, LEDMODE ledmode, uint8_t x, uint8_t y = 0, uint64_t p1 = 0, uint8_t p2 = 0, uint8_t p3 = 0, uint8_t p4 = 0)
{
  uint8_t index = x;
  if(ledmode == XY)
  uint8_t index = Matrix.XYtoIndex(x,y);

  switch (ledmode)
  {
    case off:
    LED::Off(index);
    break;
    case on:
    LED::On(index);
    break;
    case w:
    LED::SetW(index, p1);
    break;
    case rgb:
    LED::SetRGB(index, p1, p2, p3);
    break;
    case wrgb:
    LED::SetWRGB(index, p1, p2, p3, p4);
    break;
    case hex:
    LED::SetHEX(index, p1);
    break;
    case pallette:
    LED::SetPallette(index, p1, p2);
    break;
  }

}


// XY
void LED::Off(uint8_t x,uint8_t y)
{
  LED::SetHEX(x, y, 0);
}

void LED::On(uint8_t x,uint8_t y)
{
  LED::SetHEX(x, y, 0xFFFFFFFF);
}

void LED::SetW(uint8_t x, uint8_t y, uint8_t w)
{
  LED::SetHEX(x, y, w * 0x10000 + w * 0x100 + w);
  //TODO WRGB
}

void LED::SetRGB(uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B)
{
  LED::SetHEX(x, y, R * 0x10000 + G * 0x100 + B);
}

void LED::SetWRGB(uint8_t x, uint8_t y, uint8_t W, uint8_t R, uint8_t G, uint8_t B)
{
  //TODO
}

void LED::SetHEX(uint8_t x, uint8_t y, uint64_t WRGB)
{

  leds[Matrix.XYtoIndex(x,y)] = WRGB;
}

void LED::SetPallette(uint8_t x, uint8_t y, uint8_t pallette, uint8_t colour)
{
  LED::SetHEX(x, y, colour_pallette[pallette][colour]);
}


// Index
void LED::Off(uint8_t index)
{
  LED::SetHEX(index, 0);
}

void LED::On(uint8_t index)
{
  LED::SetHEX(index, 0xFFFFFFFF);
}

void LED::SetW(uint8_t index, uint8_t w)
{
  LED::SetHEX(index, w * 0x10000 + w * 0x100 + w);
  //TODO WRGB
}

void LED::SetRGB(uint8_t index, uint8_t R, uint8_t G, uint8_t B)
{
  LED::SetHEX(index, R * 0x10000 + G * 0x100 + B);
}

void LED::SetWRGB(uint8_t index, uint8_t W, uint8_t R, uint8_t G, uint8_t B)
{
  //TODO
}

void LED::SetHEX(uint8_t index, uint64_t WRGB)
{

  if(index < NUM_BOTTOM_LEDS)
  {
    leds[Matrix.BottomLEDrotation(index)] = WRGB;
  }
  else
  {
    leds[index] = WRGB;
  }
}

void LED::SetPallette(uint8_t index, uint8_t pallette, uint8_t colour)
{
  LED::SetHEX(index, colour_pallette[pallette][colour]);
}


//Processing

void LED::Update()
{
  FastLED.show();
}

void LED::Rainbow()
{
  int hue = 0;
  while(hue != 255)
  {
    fill_rainbow(leds, NUM_LEDS, hue++);
    FastLED.show();
  }
}

void LED::FillRegion(LEDMODE ledmode, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint64_t p1 = 0, uint8_t p2 = 0, uint8_t p3 = 0, uint8_t p4 = 0)
{
  //Reorder
  if(x1 > x2)
  {
    uint8_t c = x1;
    x1 = x2;
    x2 = c;
  }
  if(y1 > y2)
  {
    uint8_t c = y1;
    y1 = y2;
    y2 = c;
  }

  for(x1; x1 <= x2; x1++)
  {
    for(y1; y1 <= y2; y1++)
    {
      LED::SetLED(XY, ledmode, x1, y1, p1, p2, p3, p4);
    }
  }
}

uint64_t LED::ApplyGamma(uint64_t WRGB)
{
  uint8_t LEDGamma[256] =
  { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
    115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
    144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
    177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
    215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
  };

  return
  LEDGamma[(WRGB & 0xff000000)] *0x1000000 +
  LEDGamma[(WRGB & 0x00ff0000)>> 16] *0x10000 +
  LEDGamma[(WRGB & 0x0000ff00)>> 8] *0x100 +
  LEDGamma[(WRGB & 0x000000ff)];
}
