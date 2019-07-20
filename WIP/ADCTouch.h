#ifndef ADCTOUCH_H
#define ADCTOUCH_H

#include "Arduino.h"
#include <ADCTouchSensor.h>
#include <USBComposite.h>
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"
#include "../HAL/Timer.h"

enum KeyStates {IDLE, PRESSED, HOLD, RELEASED };

struct TouchKey {
  u16 id = 0;
  //s8 velocity = 0;
  KeyStates kstate = IDLE;
};

struct TouchKey_noID {
  //s8 velocity = 0;
  KeyStates kstate = IDLE;
  u32 activeTime = 0;
  //bool changed = false;
};

class ADCTouch
{
public:
  ADCTouch();
  void init();
  bool scan();
  TouchKey changelist[8];
private:
  void cleanList();
  bool addtoList(u8 id, KeyStates keyState);
  TouchKey_noID touchState[8];
  u8 listUsed = 0;
};

#endif
