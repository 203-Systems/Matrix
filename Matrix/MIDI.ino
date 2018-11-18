void MIDIon(unsigned int channel, unsigned int note, unsigned int velocity)
{
  LEDonMIDI(Channel, note, velocity);
  if (Return)
  {
    MIDI.sendNoteOn(channel, note, velocity);
    if (CDCenable)
    {
      CDC.print(channel);
      CDC.print("\ton\t");
      CDC.print(note);
      CDC.print("\t");
      CDC.println(velocity);
    }
  }
}

void MIDIoff(unsigned int channel, unsigned int note, unsigned int velocity)
{
  LEDoffMIDI(note);
  if (Return)
  {
    MIDI.sendNoteOff(channel, note, velocity);
    if (CDCenable)
    {
      CDC.print(channel);
      CDC.print("\toff\t");
      CDC.print(note);
      CDC.print("\t");
      CDC.println(velocity);
    }
  }
}

