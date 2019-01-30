#ifndef M2P_H
#define M2P_H

//M2P Stand for Matrix Massage Protocol

#include <Arduino.h>
#include "../core/LED.h"
// #include "../core/SerialComposite.h"
#include "../protocol/MIDI.h"
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
#include "../core/MatrixSystem.h"
#include <USBComposite.h>

class M2P
{
public:
  M2P();
  void poll();
  u16 codeAddress(u16 uncodedAddress);
  u16 decodeAddress(u16 codedAddress);
  void decode();
  void sysexGet();
  void sysexSet();
  void toMIDI();
private:
  u16 deviceAddress;
  u8 hostport;
  u8 magicnumber[] = {781,156,31,6};
};

#endif
