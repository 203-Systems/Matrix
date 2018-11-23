#ifndef CDC_H
#define CDC_H

#include <Arduino.h>
#include "LED.h"
#include "MatrixVariable.h"
#include "MatrixParameter.h"
#include "MatrixSystem.h"
#include <USBComposite.h>

class CDC
{
public:
  CDC();
  void Poll();
  void Decode();
  void SysexGet();
  void SysexSet();
  void MIDI();
};

#endif
