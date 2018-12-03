#ifndef KEYPAD_H
#define KEYPAD_H

#include "Arduino.h"
//#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
//#include "MatrixSystem.h"
//#include "../protocol/MIDI.h"
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
  bool scan();

  Key list[MULTIPRESS];
  //uint32_t FNholded = 0;
  bool fn;
  bool fnChanged;
  uint32_t lastFNpressed = 0;
  uint8_t timesFNpressed = 0;
private:
  void updateList();
  // void On(uint8_t X, uint8_t Y);
  // void Off(uint8_t X, uint8_t Y);
  bool fnCache;
  byte keypadStats[KEYPADX]; // const Y is 8, allow configuration like 8*16 or 16*16 as 8*32 in the future.
  byte keypadChanged[KEYPADX];
};

#endif
