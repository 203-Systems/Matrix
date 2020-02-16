#ifndef color_H
#define color_H

#include <FastLED.h>
#include "../Core/MatrixSystem.h"
#include "../Parameter/MatrixParameter.h"

/*
class color
{
public:
  color(u32 HEX); //Load HEX
  color(u8 R, u8 G, u8 B, bool HSV = false);
  color(float R, u8 G, u8 B, bool HSV = false);
  color(u8 palette, u8 index);
  operator u32() const;
  void operator=(color color);
  void operator=(u32 HEX);
  u8 W;
  u8 R;
  u8 G;
  u8 B;
}
#endif
*/

CRGB applycolorCorrection(CRGB input);

CRGB applyGamma(CRGB color);

CRGB desaturate(CRGB color);

CRGB compileColor(CRGB color, bool gamma = false);

CRGB toBrightness(CRGB color, u8 brightness);

CRGB toLowBrightness(CRGB color);

CRGB dispatchColorStruct(u8 sysexColor[]);

CRGB dispatchColorData(u8 color_type,u8 sysexColor[]);

u8 dispatchColorDataOffset(u8 color_type);

bool dispatchColorStructGamma(u8 color_type);

bool dispatchColorStructOverlay(u8 color_type);

u32 CRGBtoHEX(CRGB color);
#endif