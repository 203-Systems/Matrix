#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>
#include <USBMIDI.h>
#include "../HAL/LED.h"
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"

//usbmidi usbmidi;

class MIDI
{
public:
  MIDI();
  void noteOn(u8 channel, u8 note, u8 velocity);
  void noteOff(u8 channel, u8 note, u8 velocity);
  void poll();
  void sentXYon(u8 xy, u8 velocity);
  void sentXYoff(u8 xy, u8 velocity);
  void sentNoteOn(u8 channel, u8 note, u8 velocity);
  void sentNoteOff(u8 channel, u8 note, u8 velocity);
};

#endif
