#ifndef GFX_H
#define GFX_H

#include "../HAL/LED.h"
#include "../Core/MatrixSystem.h"
#include "../Parameter/MatrixParameter.h"

#define adagfxswap(a, b) { s8 t = a; a = b; b = t; }
class GFX
{
public:
  GFX(); // Constructor
  void drawPixel(s8 x, s8 y, u32 color);
  void drawLine(s8 x0, s8 y0, s8 x1, s8 y1, u32 color);
  void drawFastVLine(s8 x, s8 y, s8 h, u32 color);
  void drawFastHLine(s8 x, s8 y, s8 w, u32 color);
  void drawRect(s8 x, s8 y, s8 w, s8 h, u32 color);
  void fillRect(s8 x, s8 y, s8 w, s8 h, u32 color);
  void fillScreen(u32 color);
  void drawCircle(s8 x0, s8 y0, s8 r, u32 color);
  void drawCircleHelper(s8 x0, s8 y0, s8 r, u8 cornername,
    u32 color);
  void fillCircle(s8 x, s8 y, s8 r, u32 color);
  void fillCircleHelper(s8 x, s8 y, s8 r, u8 cornername,
    s16 delta, u32 color);
  void drawTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 color);
  void fillTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 color);
  void drawRoundRect(s8 x, s8 y, s8 w, s8 h, s8 r, u32 color);
  void fillRoundRect(s8 x, s8 y, s8 w, s8 h, s8 r, u32 color);
protected:
  u8 width;
  u8 height;
  bool overlay = true;
};

#endif
