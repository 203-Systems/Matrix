#include "GFX.h"

extern LED LED;

GFX::GFX() // Constructor
{
  width = XSIZE;
  height = YSIZE;
}

void GFX::drawPixel(s8 x, s8 y, u32 color)
{
  if(x < width && y < height)
  LED.setXYCRGB(xytoxy(x, y), color, overlay);
  return;
}

void GFX::drawLine(s8 x0, s8 y0, s8 x1, s8 y1, u32 color)
{
  bool steep = abs(y1 - y0) > abs(x1 - x0);

  if (steep) {
    adagfxswap(x0, y0);
    adagfxswap(x1, y1);
  }

  if (x0 > x1) {
    adagfxswap(x0, x1);
    adagfxswap(y0, y1);
  }

  s8 dx = x1 - x0;
  s8 dy = abs(y1 - y0);

  s8 err = dx / 2;
  s8 ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      GFX::drawPixel(y0, x0, color);
    } else {
      GFX::drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

void GFX::drawFastVLine(s8 x, s8 y, s8 h, u32 color)
{
  GFX::drawLine(x, y, x, y+h-1, color);
}

void GFX::drawFastHLine(s8 x, s8 y, s8 w, u32 color)
{
  GFX::drawLine(x, y, x+w-1, y, color);
}
void GFX::drawRect(s8 x, s8 y, s8 w, s8 h, u32 color)
{
  GFX::drawFastHLine(x, y, w, color);
  GFX::drawFastHLine(x, y+h-1, w, color);
  GFX::drawFastVLine(x, y, h, color);
  GFX::drawFastVLine(x+w-1, y, h, color);
}
void GFX::fillRect(s8 x, s8 y, s8 w, s8 h, u32 color)
{
  for (s8 i=x; i<x+w; i++) {
    GFX::drawFastVLine(i, y, h, color);
  }
}
void GFX::fillScreen(u32 color)
{
  LED.fill(color, overlay);
}
void GFX::drawCircle(s8 x0, s8 y0, s8 r, u32 color)
{
  s8 f = 1 - r;
  s8 ddF_x = 1;
  s8 ddF_y = -2 * r;
  s8 x = 0;
  s8 y = r;

  GFX::drawPixel(x0  , y0+r, color);
  GFX::drawPixel(x0  , y0-r, color);
  GFX::drawPixel(x0+r, y0  , color);
  GFX::drawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    GFX::drawPixel(x0 + x, y0 + y, color);
    GFX::drawPixel(x0 - x, y0 + y, color);
    GFX::drawPixel(x0 + x, y0 - y, color);
    GFX::drawPixel(x0 - x, y0 - y, color);
    GFX::drawPixel(x0 + y, y0 + x, color);
    GFX::drawPixel(x0 - y, y0 + x, color);
    GFX::drawPixel(x0 + y, y0 - x, color);
    GFX::drawPixel(x0 - y, y0 - x, color);
  }
}

void GFX::drawCircleHelper(s8 x0, s8 y0, s8 r, u8 cornername, u32 color)
{
  s8  f     = 1 - r;
  s8  ddF_x = 1;
  s8  ddF_y = -2 * r;
  s8  x     = 0;
  s8  y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      GFX::drawPixel(x0 + x, y0 + y, color);
      GFX::drawPixel(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      GFX::drawPixel(x0 + x, y0 - y, color);
      GFX::drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      GFX::drawPixel(x0 - y, y0 + x, color);
      GFX::drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      GFX::drawPixel(x0 - y, y0 - x, color);
      GFX::drawPixel(x0 - x, y0 - y, color);
    }
  }
}


void GFX::fillCircle(s8 x, s8 y, s8 r, u32 color)
{
  GFX::drawFastVLine(x, y-r, 2*r+1, color);
  GFX::fillCircleHelper(x, y, r, 3, 0, color);
}

void GFX::fillCircleHelper(s8 x0, s8 y0, s8 r, u8 cornername, s16 delta, u32 color)
{

  s8 f     = 1 - r;
  s8 ddF_x = 1;
  s8 ddF_y = -2 * r;
  s8 x     = 0;
  s8 y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      GFX::drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      GFX::drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      GFX::drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      GFX::drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }

}

void GFX::drawTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 color)
{
  GFX::drawLine(x0, y0, x1, y1, color);
  GFX::drawLine(x1, y1, x2, y2, color);
  GFX::drawLine(x2, y2, x0, y0, color);
}

void GFX::fillTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 color)
{
  s16 a, b, y, last;
  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1)
  {
    adagfxswap(y0, y1); adagfxswap(x0, x1);
  }

  if (y1 > y2)
  {
    adagfxswap(y2, y1); adagfxswap(x2, x1);
  }
  if (y0 > y1)
  {
    adagfxswap(y0, y1); adagfxswap(x0, x1);
  }

  if(y0 == y2)  // Handle awkward all-on-same-line case as its own thing
  {
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    GFX::drawFastHLine(a, y0, b-a+1, color);
    return;
  }

  s16
  dx01 = x1 - x0,
  dy01 = y1 - y0,
  dx02 = x2 - x0,
  dy02 = y2 - y0,
  dx12 = x2 - x1,
  dy12 = y2 - y1;

  s32
  sa   = 0,
  sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++)
  {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) adagfxswap(a,b);
    GFX::drawFastHLine(a, y, b-a+1, color);
  }
}