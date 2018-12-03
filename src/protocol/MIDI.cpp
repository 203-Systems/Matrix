#include "MIDI.h"

extern LED LED;
extern MatrixSystem Matrix;

MIDI::MIDI()
{
  //usbmidi usbmidi;
}

void MIDI::poll()
{
  USBMIDI.poll();
}

void MIDI::noteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{
  if(LEDwrite)
  {
    for(uint8_t y = 0; y < KEYPADY; y++)
    {
      for(uint8_t x = 0; x < KEYPADX; x++)
      {
        if(note == keymap[y][x])
        LED.setPalette(channel, x, y, velocity);
      }
    }
    //BottomLED
    for(uint8_t i = 0;i < NUM_BOTTOM_LEDS; i++)
    {
      if(note == bottomLEDmap[i])
      LED.setPalette(channel, Matrix.bottomLEDrotation(i+NUM_LEDS) ,velocity);
    }
  }

  if (massage_return)
  {
    MIDI::sentNoteOn(channel, note, velocity);
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

void MIDI::noteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{
  if(LEDwrite)
  {
    for(uint8_t y = 0; y < KEYPADY; y++)
    {
      for(uint8_t x = 0; x < KEYPADX; x++)
      {
        if(note == keymap[y][x])
        LED.off(x,y);
      }
    }
    //BottomLED
    for(uint8_t i = 0;i < NUM_BOTTOM_LEDS; i++)
    {
      if(note == bottomLEDmap[i])
      LED.off(i+NUM_LEDS);
    }
  }

  if (massage_return)
  {
    MIDI::sentNoteOff(channel, note, velocity);
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

void MIDI::sentXYon(uint8_t x, uint8_t y, uint8_t velocity)
{
  switch (rotation)
  {
    case 1: //90
    MIDI::sentNoteOn(midi_channel, keymap[x][KEYPADY - y - 1], 127);
    break;
    case 2: //180
    MIDI::sentNoteOn(midi_channel, keymap[KEYPADY - y - 1][KEYPADX - x - 1], 127);
    break;
    case 3: //270
    MIDI::sentNoteOn(midi_channel, keymap[KEYPADX - x - 1][y], 127);
    break;
    default: //0
    MIDI::sentNoteOn(midi_channel, keymap[y][x], 127);
  }
}

void MIDI::sentXYoff(uint8_t x, uint8_t y, uint8_t velocity)
{
  switch (rotation)
  {
    case 1: //90
    MIDI::sentNoteOff(midi_channel, keymap[x][KEYPADY - y - 1], 0);
    break;
    case 2: //180
    MIDI::sentNoteOff(midi_channel, keymap[KEYPADY - y - 1][KEYPADX - x - 1], 0);
    break;
    case 3: //270
    MIDI::sentNoteOff(midi_channel, keymap[KEYPADX - x - 1][y], 0);
    break;
    default: //0
    MIDI::sentNoteOff(midi_channel, keymap[y][x], 0);
  }
}

void MIDI::sentNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{
  USBMIDI.sendNoteOn(channel, note, velocity);
}

void MIDI::sentNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{
  USBMIDI.sendNoteOff(channel, note, velocity);
}
