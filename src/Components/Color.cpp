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
      color_correction_table[3][input.b]);
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
  u8 luma = 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;
  s16 new_r = color.r + color_desaturate_table[luma - color.r];
  s16 new_g = color.g + color_desaturate_table[luma - color.g];
  s16 new_b = color.b + color_desaturate_table[luma - color.b];

  if (new_r > 255)
    new_r = 255;
  if (new_g > 255)
    new_g = 255;
  if (new_b > 255)
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

CRGB compileColor(CRGB color, bool gamma /* = false */)
{
  if (desaturated_mode)
    color = desaturate(color);

  color = applycolorCorrection(color);

  if (gamma)
    color = applyGamma(color);

  return color;
}

CRGB toBrightness(CRGB color, u8 brightness, bool ignore)
{
  if(ignore)
    return color;
  if (brightness == LOW_STATE_BRIGHTNESS)
    return toLowBrightness(color);
  return CRGB(
      scale8_video(color.r, brightness),
      scale8_video(color.g, brightness),
      scale8_video(color.b, brightness));
}

CRGB toLowBrightness(CRGB color, bool ignore)
{
  if(ignore)
    return color;
  return CRGB(
      low_brightness_table[color.r],
      low_brightness_table[color.g],
      low_brightness_table[color.b]);
}

CRGB dispatchColorStruct(u8 sysexColor[])
{
  return dispatchColorData(sysexColor[0], &sysexColor[1]);
}

CRGB dispatchColorData(u8 color_type,u8 sysexColor[])
{
  #ifdef DEBUG
      String color_types[10] = 
  {
    "Off",
    "On",
    "GrayScale",
    "Palette",
    "7bit RGB",
    "8bit RGB",
    "7bit WRGB",
    "8bit WRGB",
    "7bit HSL",
    "8bit HSL"
  };
  CompositeSerial.print("Dispatch Color Data ");
  CompositeSerial.print(color_types[color_type]);
  for(u8 i = 0; i < dispatchColorDataOffset(color_type); i++) 
  {
    CompositeSerial.print(sysexColor[i]);
    CompositeSerial.print(" ");
  }
  CompositeSerial.println(" ");
  #endif
  CRGB color = CRGB(0, 0, 0);
  switch (color_type & 0x0F)
  {
    case 0: //Off
      break;
    case 1: //On
      color = CRGB(255, 255, 255);
      break;
    case 2: //Gray Scale
    {
      u8 l = convert_7BitTo8Bit(sysexColor[0]);
      color = CRGB(l, l, l);
      break;
    }
    case 3: //Palette
      color = palette[sysexColor[0]][sysexColor[1]];
      break;
    case 4: //7Bit RGB
      color = CRGB(
          convert_7BitTo8Bit(sysexColor[0]),
          convert_7BitTo8Bit(sysexColor[1]),
          convert_7BitTo8Bit(sysexColor[2]));
      break;
    case 5: //8Bit RGB
      remap_7bitx3(&sysexColor[0], &sysexColor[1], &sysexColor[2], &sysexColor[3]);
      color = CRGB(sysexColor[0], sysexColor[1], sysexColor[2]);
      break;
    case 6: //7Bit WRGB    //No WRGB yet
      color = CRGB(
          /*convert_7BitTo8Bit(sysexColor[0]),*/
          convert_7BitTo8Bit(sysexColor[1]),
          convert_7BitTo8Bit(sysexColor[2]),
          convert_7BitTo8Bit(sysexColor[3]));
      break;
    case 7: //8Bit WRGB    //No WRGB yet
      remap_7bitx4(&sysexColor[0], &sysexColor[1], &sysexColor[2], &sysexColor[3], &sysexColor[4]);
      color = CRGB(sysexColor[1], sysexColor[2], sysexColor[3]);
      break;
    case 8: //7Bit HSL
    {
        CHSV HSV(
          convert_7BitTo8Bit(sysexColor[0]),
          convert_7BitTo8Bit(sysexColor[1]),
          convert_7BitTo8Bit(sysexColor[2]));
        hsv2rgb_rainbow(HSV, color);
        break;
    }
    case 9: //8Bit HSL
    {
      remap_7bitx3(&sysexColor[0], &sysexColor[1], &sysexColor[2], &sysexColor[3]);
      CHSV HSV = CHSV(sysexColor[0], sysexColor[1], sysexColor[2]);
      hsv2rgb_rainbow(HSV, color);
      break;
    }
  }
  #ifdef DEBUG
    CompositeSerial.print("RGB Result: ");
    CompositeSerial.print(" ");
    CompositeSerial.print(color.r);
    CompositeSerial.print(" ");
    CompositeSerial.print(color.g);
    CompositeSerial.print(" ");
    CompositeSerial.println(color.b);
  #endif
  return color;
}
u8 dispatchColorDataOffset(u8 color_type)
{
  u8 offset_table[10] = {0, 0, 1, 2, 3, 4, 4, 5, 3, 4};
  return offset_table[color_type & 0x0F];
}

bool dispatchColorStructGamma(u8 color_type)
{
  if (color_type & 0b0010000)
    return true;
  return false;
}

bool dispatchColorStructOverlay(u8 color_type)
{
    if (color_type & 0b1000000)
    return true;
  return false;
}

u32 CRGBtoHEX(CRGB color)
{
  return wrgbToHEX(0, color.r, color.g, color.b);  
}