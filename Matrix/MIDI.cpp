#include "MatrixVariable.h"
#include "MIDI.h"


class usbmidi : public USBMidi {
  virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) {
    MIDIoff(channel, note, velocity);
  }

  virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) {
    MIDIon(channel, note, velocity);
  }
};

MIDI::MIDI()
{
  usbmidi usbmidi;
  usbmidi.registerComponent();
}

MIDI::MIDIpoll()
{
  usbmidi.poll();
}

MIDI::MIDIon(unsigned int channel, unsigned int note, unsigned int velocity)
{
  LEDonMIDI(Channel, note, velocity);
  if (RETURN)
  {
    usbmidi.sendNoteOn(channel, note, velocity);
    // if (CDCenable)
    // {
    //   CDC.print(channel);
    //   CDC.print("\ton\t");
    //   CDC.print(note);
    //   CDC.print("\t");
    //   CDC.println(velocity);
    // }
  }
}

MIDI::MIDIoff(unsigned int channel, unsigned int note, unsigned int velocity)
{
  LEDoffMIDI(note);
  if (RETURN)
  {
    usbmidi.sendNoteOff(channel, note, velocity);
    // if (CDCenable)
    // {
    //   CDC.print(channel);
    //   CDC.print("\toff\t");
    //   CDC.print(note);
    //   CDC.print("\t");
    //   CDC.println(velocity);
  }
}
}
