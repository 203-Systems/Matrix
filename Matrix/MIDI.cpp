#include "MIDI.h"
#include <USBmidi.h>
#include "MatrixVariable.h"

void usbmidi::handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity)
{
  //sMidi.NoteOff(channel, note, velocity);
}

void usbmidi::handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity)
{
  //Midi.NoteOn(channel, note, velocity);
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

void MIDI::NoteOn(unsigned int channel, unsigned int note, unsigned int velocity)
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

void MIDI::NoteOff(unsigned int channel, unsigned int note, unsigned int velocity)
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
