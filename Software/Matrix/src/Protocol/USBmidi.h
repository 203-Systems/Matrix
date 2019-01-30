#ifndef USBMIDI_H
#define USBMIDI_H

#include "../protocol/MIDI.h"
#include <USBMIDI.h>

class usbmidi : public USBMidi
{
public:
  void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) override;
  void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) override;
};

extern usbmidi USBmidi;

#endif
