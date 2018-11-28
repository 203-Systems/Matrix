#ifndef KEYPAD_H
#define KEYPAD_H

#include "Arduino.h"
//#include "MatrixVariable.h"
#include "MatrixParameter.h"
//#include "MatrixSystem.h"
//#include "MIDI.h"
//#include <USBComposite.h>

//typedef enum{ IDLE, PRESSED, HOLD, RELEASED } KeyState;

struct Key {
  uint8_t xy = 0;
  uint8_t velocity = 0;
  //KeyState kstate = IDLE;
};

class KeyPad
{
public:
  KeyPad();
  bool Scan();
  Key list[MULTIPRESS];
private:
  void UpdateList();
  // void On(uint8_t X, uint8_t Y);
  // void Off(uint8_t X, uint8_t Y);
  byte KeyPadStats[KEYPADX]; // const Y is 8, allow configuration like 8*16 or 16*16 as 8*32 in the future.
  byte KeyPadChange[KEYPADX];
};

#endif
