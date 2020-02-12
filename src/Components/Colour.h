#ifndef COLOUR_H
#define COLOUR_H

#include <FastLED.h>
#include "../Core/MatrixSystem.h"
#include "../Parameter/MatrixParameter.h"

/*
class colour
{
public:
  colour(u32 HEX); //Load HEX
  colour(u8 R, u8 G, u8 B, bool HSV = false);
  colour(float R, u8 G, u8 B, bool HSV = false);
  colour(u8 palette, u8 index);
  operator u32() const;
  void operator=(colour colour);
  void operator=(u32 HEX);
  u8 W;
  u8 R;
  u8 G;
  u8 B;
}
#endif
*/

CRGB applyColourCorrection(CRGB input);

CRGB applyGamma(CRGB colour);

CRGB destarate(CRGB colour, u8 desatrate_rate);

CRGB compileColour(CRGB colour, bool apply_gamma = false);

#endif