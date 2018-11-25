#ifndef M2P_H
#define M2P_H

//M2P Stand for Matrix Massage Protocol

#include <Arduino.h>
#include "LED.h"
#include "MIDI.h"
#include "MatrixVariable.h"
#include "MatrixParameter.h"
#include "MatrixSystem.h"
#include <USBComposite.h>

class M2P
{
public:
  M2P();
  void Poll();
  void Decode();
  void SysexGet();
  void SysexSet();
  void MIDI();
};

#endif
