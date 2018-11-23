#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>
#include "MatrixVariable.h"
#include "MatrixParameter.h"
#include "MatrixSystem.h"
#include <USBMIDI.h>

class usbmidi : public USBMidi
{
public:
  virtual void handleNoteOff(uint8 channel, uint8 note, uint8 velocity);
  virtual void handleNoteOn(uint8 channel, uint8 note, uint8 velocity);
};

class MIDI
{
public:
  usbmidi USBmidi;
  MIDI();
  void begin();
  void NoteOn(uint8 channel, uint8 note, uint8 velocity);
  void NoteOff(uint8 channel, uint8 note, uint8 velocity);
  void Poll();
  void SentNoteOn(uint8 channel, uint8 note, uint8 velocity);
  void SentNoteOff(uint8 channel, uint8 note, uint8 velocity);
};

//extern MIDI Midi;

#endif
