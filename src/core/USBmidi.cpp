#include "USBmidi.h"

extern MIDI Midi;

void usbmidi::handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity)
{
  Midi.noteOff(channel,note,velocity);
  //USBMIDI.sendNoteOff(channel,note,velocity);
  //leds[IndexInKeyMap(note)] = 0;
  //CompositeSerial.println(channel + " off " + note + " " + velocity);
}

void usbmidi::handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity)
{
  Midi.noteOn(channel,note,velocity);
  //USBMIDI.sendNoteOn(channel,note,velocity);
  //leds[IndexInKeyMap(note)] = colour[channel][velocity];
}
