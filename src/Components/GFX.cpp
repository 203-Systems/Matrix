#include "GFX.h"

extern LED LED;

GFX::GFX() // Constructor
{
  width = XSIZE;
  height = YSIZE;
}

void GFX::drawPixel(s8 x, s8 y, u32 colour)
{
  if(x < width && y < height)
  LED.setXYHEX(xytoxy(x, y), colour, overlay);
  return;
}

void GFX::drawLine(s8 x0, s8 y0, s8 x1, s8 y1, u32 colour)
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
      GFX::drawPixel(y0, x0, colour);
    } else {
      GFX::drawPixel(x0, y0, colour);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

void GFX::drawFastVLine(s8 x, s8 y, s8 h, u32 colour)
{
  GFX::drawLine(x, y, x, y+h-1, colour);
}

void GFX::drawFastHLine(s8 x, s8 y, s8 w, u32 colour)
{
  GFX::drawLine(x, y, x+w-1, y, colour);
}
void GFX::drawRect(s8 x, s8 y, s8 w, s8 h, u32 colour)
{
  GFX::drawFastHLine(x, y, w, colour);
  GFX::drawFastHLine(x, y+h-1, w, colour);
  GFX::drawFastVLine(x, y, h, colour);
  GFX::drawFastVLine(x+w-1, y, h, colour);
}
void GFX::fillRect(s8 x, s8 y, s8 w, s8 h, u32 colour)
{
  for (s8 i=x; i<x+w; i++) {
    GFX::drawFastVLine(i, y, h, colour);
  }
}
void GFX::fillScreen(u32 colour)
{
  LED.fill(colour, overlay);
}
void GFX::drawCircle(s8 x0, s8 y0, s8 r, u32 colour)
{
  s8 f = 1 - r;
  s8 ddF_x = 1;
  s8 ddF_y = -2 * r;
  s8 x = 0;
  s8 y = r;

  GFX::drawPixel(x0  , y0+r, colour);
  GFX::drawPixel(x0  , y0-r, colour);
  GFX::drawPixel(x0+r, y0  , colour);
  GFX::drawPixel(x0-r, y0  , colour);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    GFX::drawPixel(x0 + x, y0 + y, colour);
    GFX::drawPixel(x0 - x, y0 + y, colour);
    GFX::drawPixel(x0 + x, y0 - y, colour);
    GFX::drawPixel(x0 - x, y0 - y, colour);
    GFX::drawPixel(x0 + y, y0 + x, colour);
    GFX::drawPixel(x0 - y, y0 + x, colour);
    GFX::drawPixel(x0 + y, y0 - x, colour);
    GFX::drawPixel(x0 - y, y0 - x, colour);
  }
}

void GFX::drawCircleHelper(s8 x0, s8 y0, s8 r, u8 cornername, u32 colour)
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
      GFX::drawPixel(x0 + x, y0 + y, colour);
      GFX::drawPixel(x0 + y, y0 + x, colour);
    }
    if (cornername & 0x2) {
      GFX::drawPixel(x0 + x, y0 - y, colour);
      GFX::drawPixel(x0 + y, y0 - x, colour);
    }
    if (cornername & 0x8) {
      GFX::drawPixel(x0 - y, y0 + x, colour);
      GFX::drawPixel(x0 - x, y0 + y, colour);
    }
    if (cornername & 0x1) {
      GFX::drawPixel(x0 - y, y0 - x, colour);
      GFX::drawPixel(x0 - x, y0 - y, colour);
    }
  }
}


void GFX::fillCircle(s8 x, s8 y, s8 r, u32 colour)
{
  GFX::drawFastVLine(x, y-r, 2*r+1, colour);
  GFX::fillCircleHelper(x, y, r, 3, 0, colour);
}

void GFX::fillCircleHelper(s8 x0, s8 y0, s8 r, u8 cornername, s16 delta, u32 colour)
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
      GFX::drawFastVLine(x0+x, y0-y, 2*y+1+delta, colour);
      GFX::drawFastVLine(x0+y, y0-x, 2*x+1+delta, colour);
    }
    if (cornername & 0x2) {
      GFX::drawFastVLine(x0-x, y0-y, 2*y+1+delta, colour);
      GFX::drawFastVLine(x0-y, y0-x, 2*x+1+delta, colour);
    }
  }

}

void GFX::drawTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 colour)
{
  GFX::drawLine(x0, y0, x1, y1, colour);
  GFX::drawLine(x1, y1, x2, y2, colour);
  GFX::drawLine(x2, y2, x0, y0, colour);
}

void GFX::fillTriangle(s8 x0, s8 y0, s8 x1, s8 y1, s8 x2, s8 y2, u32 colour)
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
    GFX::drawFastHLine(a, y0, b-a+1, colour);
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
    GFX::drawFastHLine(a, y, b-a+1, colour);
  }
}

void GFX::drawRoundRect(s8 x, s8 y, s8 w, s8 h, s8 r, u32 colour)
{
  // smarter version
  GFX::drawFastHLine(x+r  , y    , w-2*r, colour); // Top
  GFX::drawFastHLine(x+r  , y+h-1, w-2*r, colour); // Bottom
  GFX::drawFastVLine(x    , y+r  , h-2*r, colour); // Left
  GFX::drawFastVLine(x+w-1, y+r  , h-2*r, colour); // Right
  // draw four corners
  GFX::drawCircleHelper(x+r    , y+r    , r, 1, colour);
  GFX::drawCircleHelper(x+w-r-1, y+r    , r, 2, colour);
  GFX::drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, colour);
  GFX::drawCircleHelper(x+r    , y+h-r-1, r, 8, colour);
}

void GFX::fillRoundRect(s8 x, s8 y, s8 w, s8 h, s8 r, u32 colour)
{
  // smarter version
  GFX::fillRect(x+r, y, w-2*r, h, colour);

  // draw four corners
  GFX::fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, colour);
  GFX::fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, colour);
}
