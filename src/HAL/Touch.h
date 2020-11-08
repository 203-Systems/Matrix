#ifndef TOUCH_H
#define TOUCH_H

#include "Arduino.h"
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"
#include "../HAL/Timer.h"
#include "../HAL/Key.h"
#include "../HAL/KeyPad.h"

// struct Key {
//   u16 id = 0;
//   s16 velocity = 0;
//   //KeyState kstate = IDLE;
//   u32 activeTime = 0;
//   s8 state = -1; // -1 for NULL 0 = IDLE 1 = PRESSED 2 = ACTIVED 3 = HOLD 4 = RELEASED
// };

// enum KeyStates : u8  {IDLE, PRESSED, ACTIVED,/* HOLD, HOLD_ACTIVED,*/ RELEASED, /*HOLD_RELEASED*/};
// //IDLE > PRESSED > ACTIVED >HOLD > ACTIVED > RELEASED > IDLE
// const String KeyStatesString[] = {"IDLE", "PRESSED", "ACTIVED", "RELEASED"};

// struct KeyInfo {
//   //s8 velocity = 0;
//   KeyStates state = IDLE;
//   u32 activeTime = 0;
//   float velocity = 0;
//   bool changed = false; //for Pressed,Hold, RELEASED, AFTERTOUCH
//   bool hold = false;
//   u32 holdTime()
//   {
//     if(state == IDLE)
//     return 0;

//     if(activeTime > millis())
//     return 0;

//     return millis() - activeTime;
//   }
//   operator bool() { return velocity > 0; }
// };

class Touch
{
public:
  Touch();
  void init();
  bool scan();
  KeyInfo getKey(u8 index);
  u16 changelist[8];
  KeyInfo touchState[8];
  void cleanList();
  bool addtoList(u16 id);
  float calculatePercentage();
  bool rawInput[16];
private:
  void initType1();
  bool scanType1();
  KeyInfo updateKey(KeyInfo currentKey, float input);

  u8 listUsed = 0;
  float last_percentage; 
};

#endif
