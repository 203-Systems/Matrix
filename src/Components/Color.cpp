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
  //color_correction_table[0][input.w], //For WRGB
  return CRGB(
    color_correction_table[1][input.r],
    color_correction_table[2][input.g],
    color_correction_table[3][input.b]
    );
}

CRGB applyGamma(CRGB color)
{
  //u8 new_w = led_gamma[color.w];
  u8 new_r = led_gamma[color.r];
  u8 new_g = led_gamma[color.g];
  u8 new_b = led_gamma[color.b];
  return CRGB(new_r, new_g, new_b);
}

CRGB desaturate(CRGB color)
{
  u8 luma = 0.299 * color.r + 0.587 * color.g + 0.144 * color.b;
  s16 new_r = color.r + color_desaturate_table[luma - color.r];
  s16 new_g = color.g + color_desaturate_table[luma - color.g];
  s16 new_b = color.b + color_desaturate_table[luma - color.b];

  if(new_r > 255)
    new_r = 255;
  if(new_g > 255)
    new_g = 255;
  if(new_b > 255)
    new_b = 255;

  // #ifdef DEBUG
  // CompositeSerial.print("Destrate\t");
  // CompositeSerial.print(d_rate);
  // CompositeSerial.print("\t");
  // CompositeSerial.print(luma);
  // CompositeSerial.print("\t|\t");
  // CompositeSerial.print(color.r);
  // CompositeSerial.print("\t");
  // CompositeSerial.print(color.g);
  // CompositeSerial.print("\t");
  // CompositeSerial.print(color.b);
  // CompositeSerial.print("\t|\t");
  // CompositeSerial.print(scale8_video(luma - color.r, d_rate));
  // CompositeSerial.print("\t");
  // CompositeSerial.print(scale8_video(luma - color.g, d_rate));
  // CompositeSerial.print("\t");
  // CompositeSerial.print(scale8_video(luma - color.b, d_rate));
  // CompositeSerial.print("\t|\t");
  // CompositeSerial.print(new_r);
  // CompositeSerial.print("\t");
  // CompositeSerial.print(new_g);
  // CompositeSerial.print("\t");
  // CompositeSerial.println(new_b);
  // #endif

  return CRGB(new_r, new_g, new_b);
}

CRGB compileColor(CRGB color, bool apply_gamma /* = false */)
{
  if(desaturated_mode)
    color = desaturate(color);

  color = applycolorCorrection(color);

  if(apply_gamma)
    color = applyGamma(color);

  return color;
}

CRGB toBrightness(CRGB color, u8 brightness)
{
  if(brightness == LOW_STATE_BRIGHTNESS)
    return toLowBrightness(color);
  return CRGB(
    scale8_video(color.r, brightness),
    scale8_video(color.g, brightness),
    scale8_video(color.b, brightness) 
  );
}

CRGB toLowBrightness(CRGB color)
{
  return CRGB(
    low_brightness_table[color.r],
    low_brightness_table[color.g],
    low_brightness_table[color.b]
  );
}