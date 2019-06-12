#ifndef KEYPAD_H
#define KEYPAD_H

#include "Arduino.h"
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"
#include "../HAL/Timer.h"

//enum KeyState {IDLE, PRESSED, HOLD, RELEASED };

struct Key {
  u16 id = 0;
  s16 velocity = 0;
  //KeyState kstate = IDLE;
  u32 activeTime = 0;
  s8 state = -1; // -1 for NULL 0 = IDLE 1 = PRESSED 2 = ACTIVED 3 = HOLD 4 = RELEASED
};

enum KeyStates {IDLE, PRESSED, ACTIVED, HOLD, HOLD_ACTIVED, RELEASED};
//IDLE > PRESSED > ACTIVED >HOLD > ACTIVED > RELEASED > IDLE

struct Key {
  //s8 velocity = 0;
  KeyStates state = IDLE;
  u32 activeTime = 0;
  u16 velocity = 0;
  bool changed = false; //for Pressed,Hold, RELEASED, AFTERTOUCH
};

class KeyPad
{
public:
  KeyPad();
  void init();
  bool scan();
  u16 checkXY(u8 x, u8 y, bool no_rotation = false);
  u16 checkXY(u8 xy, bool no_rotation = false);
  //u32 FNholded = 0;
  Key fn;
  s16 changelist[MULTIPRESS];
  Key keypadState[XSIZE][YSIZE];
  // bool fn;
  // bool fnChanged;
  // u8 timesFNpressed = 0;
  // Timer fnTimer;
  //Key fn;
private:
  void initType1();
  bool scanType1();
  void initType2();
  bool scanType2();
  void initType3();
  bool scanType3();
  bool scanFN();
  Key updateKey(Key currentKey, u32 input);
  void cleanList();
  bool addtoList(u16 id);

  //Key keypadStats [XSIZE];
  u8 listUsed = 0;
};

//extern KeyPad KeyPad;

#endif
