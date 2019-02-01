#ifndef KEYPAD_H
#define KEYPAD_H

#include "Arduino.h"
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"
#include "../HAL/Timer.h"
//#include "MatrixSystem.h"
//#include "../protocol/MIDI.h"
//#include <USBComposite.h>

//typedef enum{ IDLE, PRESSED, HOLD, RELEASED } KeyState;

struct Key {
  u8 xy = 0;
  s8 velocity = 0;
  //KeyState kstate = IDLE;
};

class KeyPad
{
public:
  KeyPad();
  bool scan();
  bool checkXY(u8 x, u8 y);
  bool checkXY(u8 xy);

  Key list[MULTIPRESS];
  //u32 FNholded = 0;
  bool fn;
  bool fnChanged;
  u8 timesFNpressed = 0;
  Timer fnTimer;
private:
  void updateList();
  bool fnCache;
  u8 keypadState[XSIZE]; // y is define by type, u8, u16 , u32, u64
  u8 keypadChanged[XSIZE];
};

#endif
