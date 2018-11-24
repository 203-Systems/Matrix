#ifndef KEYPAD_H
#define KEYPAD_H

#include "Arduino.h"
#include "MatrixVariable.h"
#include "MatrixParameter.h"
#include "MatrixSystem.h"
#include "MIDI.h"
#include <USBComposite.h>

class KeyPad
{
public:
  KeyPad();
  bool Scan();
  void On(uint8_t X, uint8_t Y);
  void Off(uint8_t X, uint8_t Y);
  bool KeyPadStats[KEYPADX][KEYPADY];
};

#endif
