#include "UIelement.h"

extern LED LED;
extern KeyPad KeyPad;

UIelement::UIelement()
{

}

void UIelement::renderAscii(char ascii, u8 xy, u32 colour, bool ignore_gamma /* = false */) //XY is the bottom right location
{
  XY nxy = xytoxy(xy);

  if(ascii < 32 || ascii > 127)
  return;

  for(u8 x = 0; x < font[ascii - 32][0]; x++)
  {
    if(nxy.x - x <= 0)
    {
      for(u8 y = 0; y < 8; y++)
      {
        if(nxy.y - y <= 0)
        {
          if(bitRead(font[ascii - 32][font[ascii - 32][0] - x], 7 - y))
          LED.setXYHEX(xytoxy(nxy.x - x, nxy.y - y), colour, true, ignore_gamma);
        }
      }
    }
  }
}

void UIelement::renderHalfHeightNum(u8 num, u8 xy, u32 colour, bool ignore_gamma /* = false */)
{
  //LED.fillRegionOff(0x00, 0x73, true);
  if(num > 99)
  UIelement::renderHalfHeightDigit(num / 100, 0x13, colour, ignore_gamma);

  if(num > 9)
  UIelement::renderHalfHeightDigit(num % 100 / 10 , 0x43, 0x00FFFFFF, ignore_gamma);

  UIelement::renderHalfHeightDigit(num % 10, 0x73, colour, ignore_gamma);
}

void UIelement::renderHalfHeightDigit(u8 num, u8 xy, u32 colour, bool ignore_gamma /* = false */) //XY is the bottom right location
{
  s8 x = (xy & 0xF0) >> 4;
  for(s8 xi = 2; xi >= 0; xi--)
  {
    if(x == -1 && x == XSIZE)
    break;
    s8 y = (xy & 0x0F);
    for(s8 yi = 0; yi < 4; yi++)
    {
      if(y == -1 && y == YSIZE)
      break;

      LED.setXYHEX(xytoxy(x, y), colour * bitRead(half_height_num_font[num][xi], yi), true, ignore_gamma);
      y--;
    }
    x--;
  }
}

u8 UIelement::binary8bitInput(u8 currentNum, u8 y, u32 colour, bool ignore_gamma /* = false */)
{
  for(int x = 0; x < 8; x++)
  {
    if(KeyPad.checkXY(x, y))
    bitWrite(currentNum, 7 - x, !bitRead(currentNum, 7 - x));
    if(bitRead(currentNum, 7 - x))
    {
      LED.setXYHEX(xytoxy(x, y), colour, true, ignore_gamma);
    }
    else
    {
      LED.setXYHEX(xytoxy(x, y), LED.toBrightness(colour, LOWSTATEBRIGHTNESS), true, ignore_gamma);
    }
  }
  return currentNum;
}
