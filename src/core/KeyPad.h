#ifndef KEYPAD_H
#define KEYPAD_H

#include "Arduino.h"
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
#include "../core/Timer.h"
//#include "MatrixSystem.h"
//#include "../protocol/MIDI.h"
//#include <USBComposite.h>

//typedef enum{ IDLE, PRESSED, HOLD, RELEASED } KeyState;

struct Key {
  u8 xy = 0;
  u8 velocity = 0;
  //KeyState kstate = IDLE;
};

class KeyPad
{
public:
  KeyPad();
  bool scan();

  Key list[MULTIPRESS];
  //u32 FNholded = 0;
  bool fn;
  bool fnChanged;
  u8 timesFNpressed = 0;
  Timer fnTimer;
private:
  void updateList();
  // void On(u8 X, u8 Y);
  // void Off(u8 X, u8 Y);
  bool fnCache;
  byte keypadStats[KEYPADX]; // const Y is 8, allow configuration like 8*16 or 16*16 as 8*32 in the future.
  byte keypadChanged[KEYPADX];
};

#endif
