#include "color.h"
/*

  color::color(u32 HEX)
  {
    W = (HEX & 0xff000000) >> 24;
    R = (HEX & 0xff0000) >> 16;
    G = (HEX & 0xff00) >> 8;
    B = HEX & 0xff;
  }

  color::color(u8 R, u8 G, u8 B, bool HSV = false)
  {
    W = this->W;
    R = this->R;
    G = this->G;
    B = this->B;
  }
  color::color(float R, u8 G, u8 B, bool HSV = false)
  {
    W = this->W*255;
    R = this->R*255;
    G = this->G*255;
    B = this->B*255;
  }

  color::color(u8 palette_selector, u8 index)
  {
    W = palette[palette_selector][index][0];
    R = palette[palette_selector][index][1];
    G = palette[palette_selector][index][2];
    B = palette[palette_selector][index][3];
  }

  color::color(u8 palette_selector, u8 index)
  {
    W = palette[palette_selector][index][0];
    R = palette[palette_selector][index][1];
    G = palette[palette_selector][index][2];
    B = palette[palette_selector][index][3];
  }
  
  
  color::operator u32() const
  {
    return W * 0x1000000 + R * 0x10000 + G * 0x100 + B;
  }

  color::operator CRGB() const
  {
    return CRGB(R, G, B);
  }


  void color::operator=(color color)
  {
    W = color.W;
    R = color.R;
    G = color.G;
    B = color.B;
    return;
  }

  void color::operator=(u32 HEX)
  {
    W = (HEX & 0xff000000) >> 24;
    R = (HEX & 0xff0000) >> 16;
    G = (HEX & 0xff00) >> 8;
    B = HEX & 0xff;
    return;
  }

*/

CRGB applycolorCorrection(CRGB input)
{
  //u8 scale_W = (led_color_correction & 0xFF000000) >> 24;
  u8 scale_R = (led_color_correction& 0xFF0000) >> 16;
  u8 scale_G = (led_color_correction & 0xFF00) >> 8;
  u8 scale_B = led_color_correction & 0xFF;
  //pW = scale8_video(pW, scale_);
  u8 output_R = scale8_video(input.r, scale_R);
  u8 output_G = scale8_video(input.g, scale_G);
  u8 output_B = scale8_video(input.b, scale_B);
  return CRGB(output_R, output_G, output_B);
}

CRGB applyGamma(CRGB color)
{
  //u8 new_w = led_gamma[color.w];
  u8 new_r = led_gamma[color.r];
  u8 new_g = led_gamma[color.g];
  u8 new_b = led_gamma[color.b];
  return CRGB(new_r, new_g, new_b);
}

CRGB destarate(CRGB color, u8 desatrate_rate)
{
  if(!desatrate_rate)
    return color;
  float f = desatrate_rate / 255;
  u8 L = 0.299 * color.r + 0.587 * color.g + 0.144 * color.b;
  u8 new_r = color.r + f * (L - color.r);
  u8 new_g = color.g + f * (L - color.g);
  u8 new_b = color.b + f * (L - color.b);
  return CRGB(new_r, new_g, new_b);
}

CRGB compilecolor(CRGB color, bool apply_gamma /* = false */)
{
  color = destarate(color,desatrate_rate);
  color = applycolorCorrection(color);
  if(apply_gamma)
    color = applyGamma(color);
  return color;
}