#include "Colour.h"
/*

  colour::colour(u32 HEX)
  {
    W = (HEX & 0xff000000) >> 24;
    R = (HEX & 0xff0000) >> 16;
    G = (HEX & 0xff00) >> 8;
    B = HEX & 0xff;
  }

  colour::colour(u8 R, u8 G, u8 B, bool HSV = false)
  {
    W = this->W;
    R = this->R;
    G = this->G;
    B = this->B;
  }
  colour::colour(float R, u8 G, u8 B, bool HSV = false)
  {
    W = this->W*255;
    R = this->R*255;
    G = this->G*255;
    B = this->B*255;
  }

  colour::colour(u8 palette_selector, u8 index)
  {
    W = palette[palette_selector][index][0];
    R = palette[palette_selector][index][1];
    G = palette[palette_selector][index][2];
    B = palette[palette_selector][index][3];
  }

  colour::colour(u8 palette_selector, u8 index)
  {
    W = palette[palette_selector][index][0];
    R = palette[palette_selector][index][1];
    G = palette[palette_selector][index][2];
    B = palette[palette_selector][index][3];
  }
  
  
  colour::operator u32() const
  {
    return W * 0x1000000 + R * 0x10000 + G * 0x100 + B;
  }

  colour::operator CRGB() const
  {
    return CRGB(R, G, B);
  }


  void colour::operator=(colour colour)
  {
    W = colour.W;
    R = colour.R;
    G = colour.G;
    B = colour.B;
    return;
  }

  void colour::operator=(u32 HEX)
  {
    W = (HEX & 0xff000000) >> 24;
    R = (HEX & 0xff0000) >> 16;
    G = (HEX & 0xff00) >> 8;
    B = HEX & 0xff;
    return;
  }

*/

CRGB applyColourCorrection(CRGB input)
{
  //u8 scale_W = (led_colour_correction & 0xFF000000) >> 24;
  u8 scale_R = (led_colour_correction& 0xFF0000) >> 16;
  u8 scale_G = (led_colour_correction & 0xFF00) >> 8;
  u8 scale_B = led_colour_correction & 0xFF;
  //pW = scale8_video(pW, scale_);
  u8 output_R = scale8_video(input.r, scale_R);
  u8 output_G = scale8_video(input.g, scale_G);
  u8 output_B = scale8_video(input.b, scale_B);
  return CRGB(output_R, output_G, output_B);
}

CRGB applyGamma(CRGB colour)
{
  //u8 new_w = led_gamma[color.w];
  u8 new_r = led_gamma[colour.r];
  u8 new_g = led_gamma[colour.g];
  u8 new_b = led_gamma[colour.b];
  return CRGB(new_r, new_g, new_b);
}

CRGB destarate(CRGB colour, u8 desatrate_rate)
{
  if(!desatrate_rate)
    return colour;
  float f = desatrate_rate / 255;
  u8 L = 0.299 * colour.r + 0.587 * colour.g + 0.144 * colour.b;
  u8 new_r = colour.r + f * (L - colour.r);
  u8 new_g = colour.g + f * (L - colour.g);
  u8 new_b = colour.b + f * (L - colour.b);
  return CRGB(new_r, new_g, new_b);
}

CRGB compileColour(CRGB colour, bool apply_gamma /* = false */)
{
  colour = destarate(colour,desatrate_rate);
  colour = applyColourCorrection(colour);
  if(apply_gamma)
    colour = applyGamma(colour);
  return colour;
}