#include <Color.h>

Color::Color(ColorMode mode, u32 p1, u8 p2, u8 p3, u8 p4, u8 p5, u8 p6)
{
  switch(mode)
  {
    case Off:
      HEX = 0;
      break;
    case On:
      #ifdef RGBW
      HEX = 0xFF000000;
      #else
      HEX = 0xFFFFFF;
      #endif
      break;
    case W:
      #ifdef RGBW
      HEX = p1 * 0x1000000;
      #else
      HEX = p1 * 0x10000 + p1 * 0x100 + p1;
      #endif
      if(p2)
        applyGamma(HEX);
      break;
    case RGB:
      HEX = p1 * 0x10000 + p2 * 0x100 + p3;
      if(p4)
        applyGamma(HEX);
      break;
    case RGBW:
      HEX = p4 * 0x1000000 + p1 * 0x10000 + p2 * 0x100 + p3;
      if(p5)
        applyGamma(HEX);
      break;
    case HEX:
      HEX = p1;
      if(p2)
        applyGamma(HEX);
      break;
    case Palette:
      HEX = palette[p1][p2];
      break;
  }
}

operator u32() const
{
  return HEX;
}

u32 applyGamma(u32 color)
{
  HEX =
  gamma[(color & 0xff000000) >> 24] * 0x1000000 +
  gamma[(color & 0x00ff0000) >> 16] *0x10000 +
  gamma[(color & 0x0000ff00) >> 8] *0x100 +
  gamma[(color & 0x000000ff)];
}
