#include "UIelement.h"

extern LED LED;
extern KeyPad KeyPad;

UIelement::UIelement()
{

}

void UIelement::renderAscii(char ascii, u8 xy, u32 color) //XY is the bottom right location
{
  u8 nx = xytox(xy);
  u8 ny = xytoy(xy);


  if(ascii < 32 || ascii > 127)
  return;

  for(u8 x = 0; x < font[ascii - 32][0]; x++)
  {
    if(nx - x <= 0)
    {
      for(u8 y = 0; y < 8; y++)
      {
        if(ny - y <= 0)
        {
          if(bitRead(font[ascii - 32][font[ascii - 32][0] - x], 7 - y))
          LED.setXYCRGB(xytoxy(nx - x, ny - y), color, true);
        }
      }
    }
  }
}

void UIelement::renderHalfHeightNum(u16 num, u8 xy, u32 color, u32 sec_color)
{
  // s8 x = (xy & 0xF0) >> 4;
  // s8 y = (xy & 0x0F);

  // //Assume Matrix is fixed 8 width for now, there can't be more than
  // if(num > 999) 
  if(num > 99)
  UIelement::renderHalfHeightDigit(num / 100, 0x13, color);
  
  if(num > 9)
  UIelement::renderHalfHeightDigit(num % 100 / 10 , 0x43, sec_color);

  UIelement::renderHalfHeightDigit(num % 10, 0x73, color);
}

void UIelement::renderHalfHeightDigit(u8 num, u8 xy, u32 color) //XY is the bottom right location
{
  s8 x = (xy & 0xF0) >> 4;
  for(s8 xi = 2; xi >= 0; xi--)
  {
    if(x == -1 && x >= XSIZE)
    break;
    s8 y = (xy & 0x0F);
    for(s8 yi = 0; yi < 4; yi++)
    {
      if(y == -1 && y >= YSIZE)
      break;

      LED.setXYCRGB(xytoxy(x, y), color * bitRead(half_height_num_font[num][xi], yi), true);
      y--;
    }
    x--;
  }
}

u8 UIelement::binary8bitInput(u8 currentNum, u8 y, u32 color)
{
  for(int x = 0; x < 8; x++)
  {
    if(KeyPad.checkXY(x, y))
    bitWrite(currentNum, 7 - x, !bitRead(currentNum, 7 - x));
    if(bitRead(currentNum, 7 - x))
    {
      LED.setXYCRGB(xytoxy(x, y), color, true);
    }
    else
    {
      LED.setXYCRGB(xytoxy(x, y), toLowBrightness(color), true);
    }
  }
  return currentNum;
}

u8 UIelement::simple8bitInput(s16 currentNum, u8 y, u32 color)
{
  u8 brightness_level[8] = {255, 127, 51, 25, 25, 51, 127, 255};
  s8 addition[8] = {-50, -20, -5, -1, 1, 5, 20, 50};

  for(int x = 0; x < 8; x++)
  {
    if(KeyPad.checkXY(x, y))
      currentNum += addition[x];
  LED.setXYCRGB(xytoxy(x,y), toBrightness(color, brightness_level[x]), true);
  }
  if(currentNum > 255)
    currentNum = 255;
  if(currentNum < 0)
    currentNum = 0;

  return currentNum;
}
