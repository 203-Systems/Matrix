#include "LED.h"
#include <FastLED.h>



LED::LED()
{
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_TOTAL_LEDS);
  //LED::setBrightness(brightness);
  // if(POWERCORD)
  //{
  //   CRGB pc_leds[NUM_POWERCORD_LEDS];
  //   FastLED.addLeds<WS2812B, POWERCORD_PIN>(pc_leds, NUM_POWERCORD_LEDS);
  // }
};

void LED::setBrightness(u8 b)
{
  FastLED.setBrightness(b);
}

void LED::fill(u64 WRGB, bool overlay /*= false*/)
{
  //fill_solid(leds,NUM_TOTAL_LEDS,CRGB::Black);
  for(int i = 0; i < NUM_TOTAL_LEDS; i++)
  {
    if(!overlay_mode || overlay)
    {
      leds[i] = WRGB;
    }
    else
    {
      buffer[i] = WRGB;
    }
  }
  FastLED.show();
}

// void LED::setLED(INDEXMODE indexmode, LEDMODE ledmode, u8 x, u8 y = 0, u64 p1 = 0, u8 p2 = 0, u8 p3 = 0, u8 p4 = 0)
// {
//   u8 index = x;
//   if(ledmode == XY)
//   u8 index = xyToIndex(x,y);
//
//   switch (ledmode)
//   {
//     case off:
//     LED::Off(index);
//     break;
//     case on:
//     LED::On(index);
//     break;
//     case w:
//     LED::setW(index, p1);
//     break;
//     case rgb:
//     LED::setRGB(index, p1, p2, p3);
//     break;
//     case wrgb:
//     LED::setWRGB(index, p1, p2, p3, p4);
//     break;
//     case hex:
//     LED::setHEX(index, p1);
//     break;
//     case palette:
//     LED::setPalette(index, p1, p2);
//     break;
//   }
// }

// Index
void LED::off(u8 index, bool overlay /*= false*/)
{
  LED::setHEX(index, 0, overlay);
}

void LED::on(u8 index, bool overlay /*= false*/)
{
  LED::setHEX(index, 0xFFFFFFFF, overlay);
}

void LED::setW(u8 index, u8 w, bool overlay /*= false*/)
{
  LED::setHEX(index, w * 0x10000 + w * 0x100 + w, overlay);
}

void LED::setRGB(u8 index, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setHEX(index, r * 0x10000 + g * 0x100 + b, overlay);
}

void LED::setWRGB(u8 index, u8 w, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setHEX(index, w * 0x1000000 + r * 0x10000 + g * 0x100 + b, overlay);
}

void LED::setHEX(u8 index, u64 hex, bool overlay /*= false*/, bool ignore_gamma /*= false*/)
{
  if(!overlay_mode || overlay)
  {
    if(gamma_enable && !ignore_gamma)
    {
      leds[indexRotation(index)] = hex;
    }
    else
    {
      leds[indexRotation(index)] = applyGamma(hex);
    }
  }
  else
  {
    if(gamma_enable && !ignore_gamma)
    {
      buffer[indexRotation(index)] = hex;
    }
    else
    {
      buffer[indexRotation(index)] = applyGamma(hex);
    }
  }
}

void LED::setPalette(u8 index, u8 pick_palette, u8 colour, bool overlay /*= false*/)
{
  LED::setHEX(index, palette[pick_palette][colour], overlay, true);
}


// XY
void LED::offXY(u8 x,u8 y, bool overlay /*= false*/)
{
  LED::setXYHEX(x, y, 0, overlay);
}

void LED::onXY(u8 x,u8 y, bool overlay /*= false*/)
{
  LED::setXYHEX(x, y, 0xFFFFFFFF, overlay);
}

void LED::setXYW(u8 x, u8 y, u8 w, bool overlay /*= false*/)
{
  LED::setXYHEX(x, y, w * 0x10000 + w * 0x100 + w, overlay);
}

void LED::setXYRGB(u8 x, u8 y, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setXYHEX(x, y, r * 0x10000 + g * 0x100 + b, overlay);
}

void LED::setXYWRGB(u8 x, u8 y, u8 w, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setXYHEX(x, y, w * 0x1000000 + r * 0x10000 + g * 0x100 + b, overlay);
}


void LED::setXYHEX(u8 x, u8 y, u64 WRGB, bool overlay /*= false*/, bool ignore_gamma /*= false*/)
{
  if(!overlay_mode || overlay)
  {
    if(gamma_enable && !ignore_gamma)
    {
      leds[xyToIndex(x,y)] = applyGamma(WRGB);
    }
    else
    {
      leds[xyToIndex(x,y)] = WRGB;
    }
  }
  else
  {
    if(gamma_enable && !ignore_gamma)
    {
      buffer[xyToIndex(x,y)] = applyGamma(WRGB);
    }
    else
    {
      buffer[xyToIndex(x,y)] = WRGB;
    }
  }
}

void LED::setXYPalette(u8 x, u8 y, u8 pick_palette, u8 colour, bool overlay /*= false*/)
{
  LED::setXYHEX(x, y, palette[pick_palette][colour], overlay, true);
}

//Processing

void LED::update()
{
  FastLED.show();
}

void LED::rainbow()
{
  int hue = 0;
  while(hue != 255)
  {
    fill_rainbow(leds, NUM_LEDS, hue++);
    FastLED.show();
  }
}

void LED::fillRegionOff(u8 x1, u8 y1, u8 x2, u8 y2, bool overlay /*= false*/)
{
  LED::fillRegionHEX(x1, y1, y1, y2, 0, overlay);
}

void LED::fillRegionOn(u8 x1, u8 y1, u8 x2, u8 y2, bool overlay /*= false*/)
{
  LED::fillRegionHEX(x1, y1, y1, y2, 0xFFFFFFFF, overlay);
}

void LED::fillRegionW(u8 x1, u8 y1, u8 x2, u8 y2, u8 w, bool overlay /*= false*/)
{
  LED::fillRegionHEX(x1, y1, y1, y2, w * 0x10000 + w * 0x100 + w, overlay);
}

void LED::fillRegionRGB(u8 x1, u8 y1, u8 x2, u8 y2, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::fillRegionHEX(x1, y1, y1, y2, r * 0x10000 + g * 0x100 + b, overlay);
}

void LED::fillRegionWRGB(u8 x1, u8 y1, u8 x2, u8 y2, u8 w, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::fillRegionHEX(x1, y1, y1, y2, w *  0x1000000 + r * 0x10000 + g * 0x100 + b, overlay);
}

void LED::fillRegionHEX(u8 x1, u8 y1, u8 x2, u8 y2, u64 hex, bool overlay /*= false*/, bool ignore_gamma /*= false*/)
{
  //Reorder
  if(x1 > x2)
  {
    u8 c = x1;
    x1 = x2;
    x2 = c;
  }
  if(y1 > y2)
  {
    u8 c = y1;
    y1 = y2;
    y2 = c;
  }

  for(x1; x1 <= x2; x1++)
  {
    for(y1; y1 <= y2; y1++)
    {
      LED::setXYHEX(x1, y1, hex, overlay, ignore_gamma);
    }
  }
}

void LED::fillRegionPalette(u8 x1, u8 y1, u8 x2, u8 y2, u8 p, u8 c, bool overlay /*= false*/)
{
  LED::fillRegionHEX(x1, y1, y1, y2, palette[p][c], overlay, true);
}

u64 LED::applyGamma(u64 hex)
{
  return
  ledGamma[(hex & 0xff000000) >> 24] * 0x1000000 +
  ledGamma[(hex & 0x00ff0000) >> 16] *0x10000 +
  ledGamma[(hex & 0x0000ff00) >> 8] *0x100 +
  ledGamma[(hex & 0x000000ff)];
}

void LED::enableOverlayMode()
{
  if (!overlay_mode)
  {
    overlay_mode = true;
    for(int i = 0; i < NUM_TOTAL_LEDS; i++)
    {
      buffer[i] == leds[i];
    }
    LED::fill(0, true);
  }
}

void LED::disableOverlayMode()
{
  overlay_mode = false;
  for(int i = 0; i < NUM_TOTAL_LEDS; i++)
  {
    leds[i] == buffer[i];
  }
  LED::update();
}
