#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>
#include "MatrixVariable.h"
#include "MatrixParameter.h"
#include "MatrixSystem.h"
#include "MIDI.h"

class KeyPad
{
public:
  KeyPad();
  bool Scan();
  void On(uint8 X, uint8 Y);
  void Off(uint8 X, uint8 Y);
  bool KeyPadStats[KEYPADX][KEYPADY];
};

#endif
