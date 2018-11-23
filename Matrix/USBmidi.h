#ifndef USBMIDI_H
#define USBMIDI_H

#include "MIDI.h"
#include <USBMIDI.h>

class usbmidi : public USBMidi
{
public:
  void handleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
  void handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
};

extern usbmidi usbmidi;

#endif
