#ifndef KEYPAD_H
#define KEYPAD_H

#include "Arduino.h"
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"
#include "../HAL/Timer.h"
#include "../HAL/Key.h"

class KeyPad
{
public:
  KeyPad();
  void init();
  bool scan();
  u16 checkXY(u8 x, u8 y, bool no_rotation = false);
  u16 checkXY(u8 xy, bool no_rotation = false);
  KeyInfo getKey(u8 x, u8 y);
  KeyInfo getKey(u8 xy);
  KeyInfo fn;
  u16 changelist[MULTIPRESS];
  KeyInfo keypadState[XSIZE][YSIZE];
  void cleanList();
  bool addtoList(u16 id);
private:
  void initType1();
  bool scanType1();
  void initType2();
  bool scanType2();
  // void initType3();
  // bool scanType3();
  bool scanFN();
  KeyInfo updateKey(KeyInfo currentKey, float input);

  //Key keypadStats [XSIZE];
  u8 listUsed = 0;
};

//extern KeyPad KeyPad;

#endif
