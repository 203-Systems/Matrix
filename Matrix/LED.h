#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include "MatrixVariable.h"
#include "MatrixParameter.h"
#include <FastLED.h>

class LED
{
public:
  LED();
  void NoteOn(uint8 pallette, uint8 note, uint8 velocity);
  void NoteOff(uint8 note);
  void Off(uint8 X, uint8 Y );
  void On(uint8 X, uint8 Y );
  void SetW(uint8 X, uint8 Y, uint8 w);
  void SetRGB(uint8 X, uint8 Y, uint8 R, uint8 G, uint8 B);
  void SetWRGB(uint8 X, uint8 Y, uint8 W, uint8 R, uint8 G, uint8 B);
  void SetHEX(uint8 X, uint8 Y, uint64 WRGB);
  void SetPallette(uint8 X, uint8 Y, uint8 w);
};

#endif
