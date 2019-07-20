
#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include "Arduino.h"
#include "../Parameter/MatrixVariable.h"
// #include "../Parameter/MatrixParameter.h"
// #include "../Core/MatrixSystem.h"
// #include "../Protocol/MIDI.h"
#include "../HAL/KeyPad.h"
#include "../HAL/LED.h"
// #include "../HAL/Timer.h"

class UIelement
{
public:
  UIelement();
  void renderAscii(char ascii, u8 xy, u32 colour, bool ignore_gamma = false);
  void renderHalfHeightNum(u8 num, u8 xy, u32 colour, u32 sec_colour, bool ignore_gamma = false);
  void renderHalfHeightDigit(u8 num, u8 xy, u32 colour, bool ignore_gamma = false);
  u8 binary8bitInput(u8 currentNum, u8 y, u32 colour, bool ignore_gamma = false);
  u8 simple8bitInput(s16 currentNum, u8 y, u32 colour, bool ignore_gamma = false);
private:
};

#endif
