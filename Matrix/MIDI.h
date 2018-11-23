#ifndef MIDI_H
#define MIDI_H

#include "Arduino.h"
#include "MatrixVariable.h"
#include "MatrixParameter.h"
#include <USBMIDI.h>

class usbmidi : public USBMidi
{
public:
  virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity);
  virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity);
};

class MIDI
{
public:
  usbmidi USBmidi;
  MIDI();
  void begin();
  void NoteOn(unsigned int channel, unsigned int note, unsigned int velocity);
  void NoteOff(unsigned int channel, unsigned int note, unsigned int velocity);
  void Poll();
};

//extern MIDI Midi;

#endif
