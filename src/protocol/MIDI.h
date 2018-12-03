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
  void noteOn(uint8_t channel, uint8_t note, uint8_t velocity);
  void noteOff(uint8_t channel, uint8_t note, uint8_t velocity);
  void poll();
  void sentXYon(uint8_t x, uint8_t y, uint8_t velocity);
  void sentXYoff(uint8_t x, uint8_t y, uint8_t velocity);
  void sentNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
  void sentNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
};

#endif
