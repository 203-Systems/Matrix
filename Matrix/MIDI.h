#ifndef MIDI_H
#define MIDI_H

void MIDIon(unsigned int channel, unsigned int note, unsigned int velocity);
void MIDIoff(unsigned int channel, unsigned int note, unsigned int velocity);
void MIDIpoll();

#endif
