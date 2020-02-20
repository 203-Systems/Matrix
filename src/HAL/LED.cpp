#include "LED.h"
// #include <FastLED.h>

#ifdef DEBUG
#include <USBComposite.h>
#endif

LED::LED()
{
  //LED::setBrightness(brightness);
  // if(POWERCORD)
  //{
  //   CRGB pc_leds[NUM_POWERCORD_LEDS];
  //   FastLED.addLeds<WS2812B, powercord_pin>(pc_leds, NUM_POWERCORD_LEDS);
  // }
}

void LED::init()
{
  switch(led_pin)
  {
    case PB7:
    FastLED.addLeds<NEOPIXEL, PB7>(leds, NUM_TOTAL_LEDS);
    break;

    case PC7:
    FastLED.addLeds<NEOPIXEL, PC7>(leds, NUM_TOTAL_LEDS);
    break;
  }
  //FastLED.setDither(0);
  FastLED.setBrightness(brightness);
  //FastLED.setCorrection(led_color_correction);

  //FastLED.setTemperature(0xFFFFFFFF);
  //FastLED.setMaxRefreshRate(fps);
  //LED::dynamicBrightness(max_mAh);
}

void LED::setBrightness(u8 b)
{
  FastLED.setBrightness(b);
  //setBrightness(b);
}

// void LED::setcolorCorrection(u32 c)
// {
//   FastLED.setCorrection(c);
// }

void LED::dynamicBrightness(u16 mah)
{
  FastLED.setMaxPowerInVoltsAndMilliamps(5,mah);
}

void LED::fill(u32 WRGB, bool overlay /*= false*/)
{
  //fill_solid(leds,NUM_TOTAL_LEDS,CRGB::Black);
  WRGB = applycolorCorrection(WRGB);
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
  LED::changed = true;
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
  LED::setCRGB(index, CRGB(0, 0, 0), overlay);
}

void LED::on(s16 index, bool overlay /*= false*/)
{
  LED::setCRGB(index, CRGB(255, 255, 255), overlay);
}

void LED::setW(s16 index, u8 w, bool overlay /*= false*/)
{
  LED::setCRGB(index, CRGB(w, w, w), overlay);
}

void LED::setRGB(s16 index, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setCRGB(index, CRGB(r, g, b), overlay);
}

void LED::setWRGB(s16 index, u8 w, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setCRGB(index, CRGB(r, g, b), overlay); //Not real WRGB yet, since CRGB doesn't support WRGB
}

// void LED::setHEX(s16 index, u32 hex, bool overlay /*= false*/)
// {
//   LED::setCRGB(index, CRGB(hex), overlay);
// };

void LED::setCRGB(s16 index, CRGB CRGB, bool overlay /*= false*/, bool gamma /*= false*/)
{
  #ifdef DEBUG
  CompositeSerial.print("LED\t");
  CompositeSerial.print(index);
  CompositeSerial.print("\t");
  CompositeSerial.print(CRGB.r);
  CompositeSerial.print("\t");
  CompositeSerial.print(CRGB.g);
  CompositeSerial.print("\t");
  CompositeSerial.println(CRGB.b);
  #endif

  if(index < 0)
  return;

  CRGB = compileColor(CRGB, gamma);

  if(!overlay_mode || overlay)
  {
  leds[indexRotation(index)] = CRGB;
  }
  else
  {
  buffer[indexRotation(index)] = CRGB;
  }

  LED::changed = true;
}

void LED::setPalette(s16 index, u8 palette_selected, u8 value, bool overlay /*= false*/, u8 brightness /*= 255*/)
{
  CRGB color = palette[palette_selected][value];

  if(brightness == LOW_STATE_BRIGHTNESS)
  {
    color = toLowBrightness(color);
  }
  else if(brightness < 255)
  {
    color = toBrightness(color, brightness);
  }

  if(!overlay_mode || overlay)
  {
    leds[indexRotation(index)] = color;
  }
  else
  {
    buffer[indexRotation(index)] = color;
  }

  LED::changed = true;
}


// XY
void LED::offXY(u8 xy, bool overlay /*= false*/)
{
  LED::setXYCRGB(xy, CRGB(0, 0, 0), overlay);
}

void LED::onXY(u8 xy, bool overlay /*= false*/)
{
  LED::setXYCRGB(xy, CRGB(255, 255, 255), overlay);
}

void LED::setXYW(u8 xy, u8 w, bool overlay /*= false*/)
{
  LED::setXYCRGB(xy, CRGB(w, w, w), overlay);
}

void LED::setXYRGB(u8 xy, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setXYCRGB(xy, CRGB(r, g, b), overlay);
}

void LED::setXYWRGB(u8 xy, u8 w, u8 r, u8 g, u8 b, bool overlay /*= false*/)
{
  LED::setXYCRGB(xy, CRGB(r, g, b), overlay); //Not real WRGB yet, since CRGB doesn't support WRGB
}


// void LED::setXYHEX(u8 xy, u32 hex, bool overlay /*= false*/)
// {
//   LED::setXYCRGB(xy, CRGB(hex), overlay);
// }

void LED::setXYCRGB(u8 xy, CRGB CRGB, bool overlay /*= false*/, bool gamma /*= false*/)
{
  #ifdef DEBUG
  CompositeSerial.print("LED XY\t");
  CompositeSerial.print(xy, HEX);
  CompositeSerial.print("\t");
  CompositeSerial.print(CRGB.r);
  CompositeSerial.print("\t");
  CompositeSerial.print(CRGB.g);
  CompositeSerial.print("\t");
  CompositeSerial.println(CRGB.b);
  #endif

  CRGB = compileColor(CRGB, gamma);

  if(!overlay_mode || overlay)
  {
    leds[xyToIndex(xy)] = CRGB;
  }
  else
  {
    buffer[xyToIndex(xy)] = CRGB;
  }

  LED::changed = true;
}

void LED::setXYPalette(u8 xy, u8 palette_selected, u8 value, bool overlay /*= false*/, u8 brightness /*= 255*/)
{
  CRGB color = palette[palette_selected][value];

  if(brightness == LOW_STATE_BRIGHTNESS)
  {
    color = toLowBrightness(color);
  }
  else if(brightness < 255)
  {
    color = toBrightness(color, brightness);
  }

  if(!overlay_mode || overlay)
  {
    leds[xyToIndex(xy)] = color;
  }
  else
  {
    buffer[xyToIndex(xy)] = color;
  }

  LED::changed = true;
}

//Processing

void LED::update()
{
  FastLED.show();
}

void LED::rainbow()
{
  while(true)
  {
  int hue = 0;
  while(hue != 255)
  {
    fill_rainbow(leds, NUM_LEDS, hue++);
    FastLED.show();
  }
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

void LED::enableOverlayMode()
{
  if (!overlay_mode)
  {
    overlay_mode = true;
    for(int i = 0; i < NUM_TOTAL_LEDS; i++)
    {
      buffer[i] = leds[i];
    }
  }
  LED::fill(0, true);
}

void LED::disableOverlayMode()
{
  if(overlay_mode)
  {
    overlay_mode = false;
    //LED::fill(0);
    for(int i = 0; i < NUM_TOTAL_LEDS; i++)
    {
      leds[i] = buffer[i];
    }
  }
  LED::update();
}

u32 LED::readXYLED(u8 xy)
{
  if(xytox(xy) < XSIZE && xytoy(xy) < YSIZE)
    return (leds[xyToIndex(xy)].r << 16) + (leds[xyToIndex(xy)].g << 8) + (leds[xyToIndex(xy)].b);
  return 0;
}

u32 LED::readLED(u8 index)
{
  return(leds[indexRotation(index)].r << 16) + (leds[indexRotation(index)].g << 8) + (leds[indexRotation(index)].b);
}

CRGB LED::readXYCRGB(u8 xy)
{
  if(xytox(xy) < XSIZE && xytoy(xy) < YSIZE)
    return leds[xyToIndex(xy)];
  return 0;
}

CRGB LED::readCRGB(u8 index)
{
  return leds[indexRotation(index)];
}



bool LED::rotationCW(u8 r)
{
  if(r != 0 && r < 4)
  {
    for(int i = 0; i < NUM_LEDS; i++)
    {
      buffer[i] = leds[i];
      leds[i] = 0;
    }

    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = buffer[xyToIndex(xyRotation(indexToXY(i),r))];
    }
  }
}

void LED::shift(Direction direction, u8 distance)
{
  for(u8 d = 0 ; d < distance; d++)
  {
    switch(direction)
    {
      case up:
      for(s8 y = 0; y < 8; y++)
      {
        for(s8 x = 0; x < 8; x++)
        {
          leds[xyToIndex(xytoxy(x, y))] = LED::readXYCRGB(xytoxy(x, y + 1));
        }
      }
      break;
      case right:
      for(s8 x = 7; x >= 0; x--)
      {
        for(s8 y = 0; y < 8; y++)
        {
          leds[xyToIndex(xytoxy(x, y))] = LED::readXYCRGB(xytoxy(x - 1, y));
        }
      }
      break;
      case down:
      for(s8 y = 7; y >= 0; y--)
      {
        for(s8 x = 0; x < 8; x++)
        {
          leds[xyToIndex(xytoxy(x, y))] = LED::readXYCRGB(xytoxy(x, y - 1));
        }
      }
      break;
      case left:
      for(s8 x = 0; x < 8; x++)
      {
        // CompositeSerial.print("Coping coloum ");
        // CompositeSerial.print(x);
        // CompositeSerial.print(" to ");
        // CompositeSerial.println(x - 1);
        for(s8 y = 0; y < 8; y++)
        {
          // CompositeSerial.print(x);
          // CompositeSerial.print(y);
          // CompositeSerial.print(" RGB ");
          // CompositeSerial.print(LED::readXYLED(xytoxy(x,y)), HEX);
          // CompositeSerial.print(" to ");
          // CompositeSerial.print(x - 1);
          // CompositeSerial.println(y);
          leds[xyToIndex(xytoxy(x, y))] = LED::readXYCRGB(xytoxy(x + 1, y));
        }
      }
      break;
    }
  }
}

bool LED::getOverlayMode()
{
  return overlay_mode;
}