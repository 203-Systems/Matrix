#include "MIDI.h"

extern MIDI Midi;

void usbmidi::handleNoteOff(uint8 channel, uint8 note, uint8 velocity)
{
  Midi.NoteOff(channel, note, velocity);
}

void usbmidi::handleNoteOn(uint8 channel, uint8 note, uint8 velocity)
{
  Midi.NoteOn(channel, note, velocity);
}

MIDI::MIDI()
{
  //USBmidi();
  USBmidi.registerComponent();
  USBmidi.begin();
}

void MIDI::begin()
{

}

void MIDI::Poll()
{
  USBmidi.poll();
}

void MIDI::NoteOn(uint8 channel, uint8 note, uint8 velocity)
{
  //LEDonMIDI(channel, note, velocity);
  if (RETURN)
  {
    USBmidi.sendNoteOn(channel, note, velocity);
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

void MIDI::NoteOff(uint8 channel, uint8 note, uint8 velocity)
{
  //LEDoffMIDI(note);
  if (RETURN)
  {
    USBmidi.sendNoteOff(channel, note, velocity);
    // if (CDCenable)
    // {
    //   CDC.print(channel);
    //   CDC.print("\toff\t");
    //   CDC.print(note);
    //   CDC.print("\t");
    //   CDC.println(velocity);
    // }
  }
}


void MIDI::SentNoteOn(uint8 channel, uint8 note, uint8 velocity)
{
    USBmidi.sendNoteOff(channel, note, velocity);
}

void MIDI::SentNoteOff(uint8 channel, uint8 note, uint8 velocity)
{
    USBmidi.sendNoteOff(channel, note, velocity);
}
