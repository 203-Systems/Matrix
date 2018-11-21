#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>
#include <USBMIDI.h>

class MIDI
{
public:
  void MIDI();
  void MIDIon(unsigned int channel, unsigned int note, unsigned int velocity);
  void MIDIoff(unsigned int channel, unsigned int note, unsigned int velocity);
  void MIDIpoll();
};

extern MIDI MIDI;

#endif
