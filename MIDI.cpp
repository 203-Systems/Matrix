#include "MIDI.h"

extern LED LED;
extern MatrixSystem Matrix;

MIDI::MIDI()
{
  //usbmidi usbmidi;
}

void MIDI::Begin()
{
  //usbmidi.registerComponent();
}

void MIDI::Poll()
{
  USBMIDI.poll();
}

void MIDI::NoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{

  for(uint8_t y = 0; y < KEYPADY; y++)
  {
      for(uint8_t x = 0; x < KEYPADX; x++)
      {
        if(note == KeyMap[y][x])
          LED.SetPallette(channel, x, y, velocity);
      }
  }
  //BottomLED
  for(uint8_t i = 0;i < NUM_BOTTOM_LEDS; i++)
  {
        if(note == BottomLEDMap[i])
          LED.SetPallette(channel, i+NUM_LEDS ,velocity);
  }

  if (RETURN)
  {
    MIDI::SentNoteOn(channel, note, velocity);
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

void MIDI::NoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{

  for(uint8_t y = 0; y < KEYPADY; y++)
  {
      for(uint8_t x = 0; x < KEYPADX; x++)
      {
        if(note == KeyMap[y][x])
          LED.Off(x,y);
      }
  }
  //BottomLED
  for(uint8_t i = 0;i < NUM_BOTTOM_LEDS; i++)
  {
        if(note == BottomLEDMap[i])
          LED.Off(i+NUM_LEDS);
  }

  if (RETURN)
  {
    MIDI::SentNoteOff(channel, note, velocity);
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


void MIDI::SentNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{
  USBMIDI.sendNoteOn(channel, note, velocity);
}

void MIDI::SentNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{
  USBMIDI.sendNoteOff(channel, note, velocity);
}
