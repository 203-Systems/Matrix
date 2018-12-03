#include "MIDI.h"

extern LED LED;


MIDI::MIDI()
{
  //usbmidi usbmidi;
}

void MIDI::poll()
{
  USBMIDI.poll();
}

void MIDI::noteOn(u8 channel, u8 note, u8 velocity)
{
  for(u8 y = 0; y < KEYPADY; y++)
  {
    for(u8 x = 0; x < KEYPADX; x++)
    {
      if(note == keymap[y][x])
      LED.setXYPalette(channel, x, y, velocity);
    }
  }
  //BottomLED
  for(u8 i = 0;i < NUM_BOTTOM_LEDS; i++)
  {
    if(note == bottomLEDmap[i])
    LED.setPalette(channel, i+NUM_LEDS ,velocity);
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


void MIDI::noteOff(u8 channel, u8 note, u8 velocity)
{
  for(u8 y = 0; y < KEYPADY; y++)
  {
    for(u8 x = 0; x < KEYPADX; x++)
    {
      if(note == keymap[y][x])
      LED.offXY(x,y);
    }
  }
  //BottomLED
  for(u8 i = 0;i < NUM_BOTTOM_LEDS; i++)
  {
    if(note == bottomLEDmap[i])
    LED.off(i+NUM_LEDS);
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

void MIDI::sentXYon(u8 x, u8 y, u8 velocity)
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

void MIDI::sentXYoff(u8 x, u8 y, u8 velocity)
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

void MIDI::sentNoteOn(u8 channel, u8 note, u8 velocity)
{
  USBMIDI.sendNoteOn(channel, note, velocity);
}

void MIDI::sentNoteOff(u8 channel, u8 note, u8 velocity)
{
  USBMIDI.sendNoteOff(channel, note, velocity);
}
