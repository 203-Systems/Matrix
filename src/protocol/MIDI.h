#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>
#include <USBMIDI.h>
#include "../core/LED.h"
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
#include "../core/MatrixSystem.h"

//usbmidi usbmidi;

class MIDI
{
public:
  MIDI();
  void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
  void NoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
  void Poll();
  void SentXYon(uint8_t x, uint8_t y, uint8_t velocity);
  void SentXYoff(uint8_t x, uint8_t y, uint8_t velocity);
  void SentNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
  void SentNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
};

#endif
