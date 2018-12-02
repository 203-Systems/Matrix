#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
#include "../core/MatrixSystem.h"
#include <FastLED.h>

enum LEDMODE{ on, off, w, rgb, wrgb, hex, pallette};
enum INDEXMODE{ INDEX, XY };

class LED
{
public:
  LED();
  void SetBrightness(uint8_t b);
  void Fill(uint64_t WRGB, bool override = false);

  // void SetLED(INDEXMODE indexmode, LEDMODE ledmode, uint8_t x1, uint8_t y1, uint64_t p1, uint8_t p2, uint8_t p3, uint8_t p4);

  //XY
  void Off(uint8_t x, uint8_t y, bool override = false);
  void On(uint8_t x, uint8_t y, bool override = false);
  void SetW(uint8_t x, uint8_t y, uint8_t w, bool override = false);
  void SetRGB(uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B, bool override = false);
  void SetWRGB(uint8_t x, uint8_t y, uint8_t W, uint8_t R, uint8_t G, uint8_t B, bool override = false);
  void SetHEX(uint8_t x, uint8_t y, uint64_t WRGB, bool override = false);
  void SetPallette(uint8_t x, uint8_t y, uint8_t pallette, uint8_t colour, bool override = false);

  //Raw index - for BottomLED ，POWERCORD and raw strap.
  void Off(uint8_t index, bool override = false);
  void On(uint8_t index, bool override = false);
  void SetW(uint8_t index, uint8_t w, bool override = false);
  void SetRGB(uint8_t index, uint8_t R, uint8_t G, uint8_t B, bool override = false);
  void SetWRGB(uint8_t index, uint8_t W, uint8_t R, uint8_t G, uint8_t B, bool override = false);
  void SetHEX(uint8_t index, uint64_t WRGB, bool override = false);
  void SetPallette(uint8_t index, uint8_t pallette, uint8_t colour, bool override = false);

  //Processing
  void Update();
  void Rainbow();
  void FillRegion(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint64_t WRGB, bool override = false);
  void FillRegion(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t W, bool override = false);
  void FillRegion(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t P, uint8_t C, bool override = false);
  void FillRegion(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t W, uint8_t R, uint8_t G, uint8_t B, bool override = false);
  void FillRegion(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t R, uint8_t G, uint8_t B, bool override = false);
  uint64_t ApplyGamma(uint64_t WRGB);
};

#endif
