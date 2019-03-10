#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>
#include <USBMIDI.h>
#include "../HAL/LED.h"
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"

//usbmidi usbmidi;

class usbmidi : public USBMidi
{
public:
  void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) override;
  void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) override;
};

class MIDI
{
public:
  usbmidi USBmidi;
  MIDI();
  void registerComponent();
  void noteOn(u8 channel, u8 note, u8 velocity);
  void noteOff(u8 channel, u8 note, u8 velocity);
  void poll();
  void sentXYon(u8 xy, u8 velocity);
  void sentXYoff(u8 xy, u8 velocity);
  void sentNoteOn(u8 channel, u8 note, u8 velocity);
  void sentNoteOff(u8 channel, u8 note, u8 velocity);
};

extern MIDI Midi;

#endif
