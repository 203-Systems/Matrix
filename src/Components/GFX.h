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
  void drawPixel(s8 x, s8 y, u32 colour);
  void drawLine(s8 x0, s8 y0, s8 x1, s8 y1, u32 colour);
  void drawFastVLine(s8 x, s8 y, s8 h, u32 colour);
  void drawFastHLine(s8 x, s8 y, s8 w, u32 colour);
  void drawRect(s8 x, s8 y, s8 w, s8 h, u32 colour);
  void fillRect(s8 x, s8 y, s8 w, s8 h, u32 colour);
  void fillScreen(u32 colour);
  void drawCircle(s8 x0, s8 y0, s8 r, u32 colour);
  void drawCircleHelper(s8 x0, s8 y0, s8 r, u8 cornername,
    u32 colour);
  void fillCircle(s8 x, s8 y, s8 r, u32 colour);
  void fillCircleHelper(s8 x, s8 y, s8 r, u8 cornername,
    s16 delta, u32 colour);
  void drawTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 colour);
  void fillTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 colour);
  void drawRoundRect(s8 x, s8 y, s8 w, s8 h, s8 r, u32 colour);
  void fillRoundRect(s8 x, s8 y, s8 w, s8 h, s8 r, u32 colour);
protected:
  u8 width;
  u8 height;
  bool overlay = true;
};

#endif
