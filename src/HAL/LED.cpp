#include "LED.h"
// #include <FastLED.h>

#ifdef DEBUG
#include <USBComposite.h>
#endif

LED::LED()
{
  //setBrightnesss(brightness);
  //LED::setBrightness(brightness);
  // if(POWERCORD)
  //{
  //   CRGB pc_leds[NUM_POWERCORD_LEDS];
  //   FastLED.addLeds<WS2812B, POWERCORD_PIN>(pc_leds, NUM_POWERCORD_LEDS);
  // }
};

void LED::init()
{
  switch(LED_PIN)
  {
    case PB7:
    FastLED.addLeds<NEOPIXEL, PB7>(leds, NUM_TOTAL_LEDS);
    break;

    case PC7:
    FastLED.addLeds<NEOPIXEL, PC7>(leds, NUM_TOTAL_LEDS);
    break;

    FastLED.setMaxRefreshRate(fps);
    LED::dynamicBrightness(max_mAh);

  }
}

void LED::setBrightness(u8 b)
{
  FastLED.setBrightness(b);
  setBrightnesss(b);
}

void LED::dynamicBrightness(u16 mah)
{
  FastLED.setMaxPowerInVoltsAndMilliamps(5,mah);
}

void LED::nextBrightnessState()
{
  // if(brightness >= 192) //Bright AF
  // {
  //   LED::setBrightness(32);
  // }
  // else if(brightness >= 160) //VeryBright
  // {
  //   LED::setBrightness(192);
  // }
  // else if(brightness >= 128) //Bright
  // {
  //   LED::setBrightness(160);
  // }
  // else if(brightness >= 96) //Normal
  // {
  //   LED::setBrightness(128);
  // }
  // else if(brightness >= 64) //Dim
  // {
  //   LED::setBrightness(96);
  // }
  // else if(brightness >= 32) //VeryDim
  // {
  //   LED::setBrightness(64);
  // }
  // else
  // {
  //   LED::setBrightness(32);
  // }
  for(u8 i = 0; i < 6; i++)  //
  {
    if(brightness_level[i] > brightness)
    {
      setBrightness(brightness_level[i]);
      return;
    }
  }
  setBrightness(brightness_level[0]);
}

void LED::fill(u32 WRGB, bool overlay /*= false*/)
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
  //FastLED.show();
}

// void LED::setLED(INDEXMODE indexmode, LEDMODE ledmode, u8 xy = 0, u32 p1 = 0, u8 p2 = 0, u8 p3 = 0, u8 p4 = 0)
// {
//   u8 index = x;
//   if(ledmode == XY)
//   u8 index = xyToIndex(xy);
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
void LED::off(s16 index, bool overlay /*= false*/)
{
  LED::setHEX(index, 0, overlay);
}

void LED::on(s16 index, bool overlay /*= false*/)
{
  LED::setHEX(index, 0xFFFFFFFF, overlay);
}

void LED::setW(s16 index, u8 w, bool overlay /*= false*/)
{
  LED::setHEX(index, w * 0x10000 + w * 0x100 + w, overlay);
}

void LED::setRGB(s16 index, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setHEX(index, r * 0x10000 + g * 0x100 + b, overlay);
}

void LED::setWRGB(s16 index, u8 w, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setHEX(index, w * 0x1000000 + r * 0x10000 + g * 0x100 + b, overlay);
}

void LED::setHEX(s16 index, u32 hex, bool overlay /*= false*/, bool ignore_gamma /*= false*/)
{
  // #ifdef DEBUG
  // CompositeSerial.print("LED Index \t");
  // CompositeSerial.print(index);
  // CompositeSerial.print("\t");
  // CompositeSerial.println(hex, HEX);
  // #endif

  if(index < 0)
  return;

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

void LED::setPalette(s16 index, u8 pick_palette, u8 colour, bool overlay /*= false*/)
{
  LED::setHEX(index, palette[pick_palette][colour], overlay, true);
}


// XY
void LED::offXY(u8 xy, bool overlay /*= false*/)
{
  LED::setXYHEX(xy, 0, overlay);
}

void LED::onXY(u8 xy, bool overlay /*= false*/)
{
  LED::setXYHEX(xy, 0xFFFFFFFF, overlay);
}

void LED::setXYW(u8 xy, u8 w, bool overlay /*= false*/)
{
  LED::setXYHEX(xy, w * 0x10000 + w * 0x100 + w, overlay);
}

void LED::setXYRGB(u8 xy, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setXYHEX(xy, r * 0x10000 + g * 0x100 + b, overlay);
}

void LED::setXYWRGB(u8 xy, u8 w, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setXYHEX(xy, w * 0x1000000 + r * 0x10000 + g * 0x100 + b, overlay);
}


void LED::setXYHEX(u8 xy, u32 hex, bool overlay /*= false*/, bool ignore_gamma /*= false*/)
{
  // #ifdef DEBUG
  // CompositeSerial.print("LED XY \t");
  // CompositeSerial.print(xy, HEX);
  // CompositeSerial.print("\t");
  // CompositeSerial.println(hex, HEX);
  // #endif

  if(!overlay_mode || overlay)
  {
    if(gamma_enable && !ignore_gamma)
    {
      leds[xyToIndex(xy)] = applyGamma(hex);
    }
    else
    {
      leds[xyToIndex(xy)] = hex;
    }
  }
  else
  {
    if(gamma_enable && !ignore_gamma)
    {
      buffer[xyToIndex(xy)] = applyGamma(hex);
    }
    else
    {
      buffer[xyToIndex(xy)] = hex;
    }
  }
}

void LED::setXYPalette(u8 xy, u8 pick_palette, u8 colour, bool overlay /*= false*/)
{
  LED::setXYHEX(xy, palette[pick_palette][colour], overlay, true);
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

// void LED::fillRegionOff(u8 xy1, u8 xy2, bool overlay /*= false*/)
// {
//   LED::fillRegionHEX(xy1, xy2, 0, overlay);
// }
//
// void LED::fillRegionOn(u8 xy1, u8 xy2, bool overlay /*= false*/)
// {
//   LED::fillRegionHEX(xy1, xy2, 0xFFFFFFFF, overlay);
// }
//
// void LED::fillRegionW(u8 xy1, u8 xy2, u8 w, bool overlay /*= false*/)
// {
//   LED::fillRegionHEX(xy1, xy2, w * 0x10000 + w * 0x100 + w, overlay);
// }
//
// void LED::fillRegionRGB(u8 xy1, u8 xy2, u8 r, u8 g, u8 b, bool overlay /*= false*/)
// {
//   LED::fillRegionHEX(xy1, xy2, r * 0x10000 + g * 0x100 + b, overlay);
// }
//
// void LED::fillRegionWRGB(u8 xy1, u8 xy2, u8 w, u8 r, u8 g, u8 b, bool overlay /*= false*/)
// {
//   LED::fillRegionHEX(xy1, xy2, w *  0x1000000 + r * 0x10000 + g * 0x100 + b, overlay);
// }
//
// void LED::fillRegionHEX(u8 xy1, u8 xy2, u32 hex, bool overlay /*= false*/, bool ignore_gamma /*= false*/)
// {
//   u8 x1 = (xy1 & 0xF0) >> 4;
//   u8 y1 = xy1 & 0x0F;
//   u8 x2 = (xy2 & 0xF0) >> 4;
//   u8 y2 = xy2 & 0x0F;
//   //Reorder
//   if(x1 > x2)
//   {
//     u8 c = x1;
//     x1 = x2;
//     x2 = c;
//   }
//   if(y1 > y2)
//   {
//     u8 c = y1;
//     y1 = y2;
//     y2 = c;
//   }
//
//   for(x1; x1 <= x2; x1++)
//   {
//     for(y1; y1 <= y2; y1++)
//     {
//       LED::setXYHEX(x1 * 0x10 + y1, hex, overlay, ignore_gamma);
//     }
//   }
// }
//
// void LED::fillRegionPalette(u8 xy1, u8 xy2, u8 p, u8 c, bool overlay /*= false*/)
// {
//   LED::fillRegionHEX(xy1, xy2, palette[p][c], overlay, true);
// }

u32 LED::applyGamma(u32 hex)
{
  return
  led_gamma[(hex & 0xff000000) >> 24] * 0x1000000 +
  led_gamma[(hex & 0x00ff0000) >> 16] *0x10000 +
  led_gamma[(hex & 0x0000ff00) >> 8] *0x100 +
  led_gamma[(hex & 0x000000ff)];
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
  }
  LED::fill(0, true);
}

void LED::disableOverlayMode()
{
  if(overlay_mode)
  {
    overlay_mode = false;
    LED::fill(0);
    for(int i = 0; i < NUM_TOTAL_LEDS; i++)
    {
      leds[i] == buffer[i];
    }
  }
  LED::update();
}

u32 LED::readXYLED(u8 xy)
{
  return leds[xyToIndex(xy)];
}

u32 LED::readLED(u8 index)
{
  return leds[indexRotation(index)];
}

u32 LED::toBrightness(u32 hex, float f)
{
  u8 w = (((hex & 0xFF000000) >> 24) * f);
  u8 r = (((hex & 0x00FF0000) >> 16) * f);
  u8 g = (((hex & 0x0000FF00) >> 8) * f);
  u8 b = ((hex & 0x000000FF) * f);

  return w * 0x1000000 + r * 0x10000 + g * 0x100 + b;
}
