#ifndef color_H
#define color_H

#include <FastLED.h>
#include "../Core/MatrixSystem.h"
#include "../Parameter/MatrixParameter.h"

//Color Class
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

CRGB applycolorCorrection(CRGB input); //Add color correction to color input

CRGB applyGamma(CRGB color); //Add gamma correction to color input

CRGB desaturate(CRGB color); //Desaturate color by global variable <desaturate_rate>

CRGB compileColor(CRGB color, bool gamma = false); //Compile color with global variable <desaturated_mode> and parameter <gamma>

CRGB toBrightness(CRGB color, u8 brightness, bool ignore = false); //Scale color to parameter <brightness> / 255

CRGB toLowBrightness(CRGB color, bool ignore = false); //Scale color to MACRO LOW_STATE_BRIGHTNESS (Use the LUT, more efficent than toBrightness())

CRGB dispatchColorStruct(u8 sysexColor[]); //Split parameter <sysexColor[]> to color type and color data for dispatchColorData()

CRGB dispatchColorData(u8 color_type,u8 sysexColor[]); //Read color data based on <color_type> and <sysexColor[]>

u8 dispatchColorDataOffset(u8 color_type); //Return Data offset by color type

bool dispatchColorStructGamma(u8 color_type); //Check if Gamma correction bit is set

bool dispatchColorStructOverlay(u8 color_type); //Check if Overlay bit is set

u32 CRGBtoHEX(CRGB color); //Convert CRGB to UInt32_t

#endif