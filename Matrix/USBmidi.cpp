#include "USBMIDI.h"

extern MIDI MIDI;

void usbmidi::handleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity){
  MIDI.SentNoteOff(channel, note, velocity);
}

void usbmidi::handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity){
  MIDI.SentNoteOn(channel, note, velocity);
}
