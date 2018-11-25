#ifndef USBMIDI_H
#define USBMIDI_H

#include "MIDI.h"
#include <USBMIDI.h>

class usbmidi : public USBMidi
{
public:
  void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity);
  void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity);
};

extern usbmidi USBmidi;

#endif
