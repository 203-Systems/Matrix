#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>
#include <USBMIDI.h>
#include "../core/LED.h"
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
#include "../core/MatrixSystem.h"

//usbmidi usbmidi;

class MIDI
{
public:
  MIDI();
  void noteOn(u8 channel, u8 note, u8 velocity);
  void noteOff(u8 channel, u8 note, u8 velocity);
  void poll();
  void sentXYon(u8 x, u8 y, u8 velocity);
  void sentXYoff(u8 x, u8 y, u8 velocity);
  void sentNoteOn(u8 channel, u8 note, u8 velocity);
  void sentNoteOff(u8 channel, u8 note, u8 velocity);
};

#endif
