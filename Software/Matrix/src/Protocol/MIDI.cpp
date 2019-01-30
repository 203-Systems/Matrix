#include "MIDI.h"

#ifdef DEBUG
#include <USBComposite.h>
#endif

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

  #ifdef DEBUG
  CompositeSerial.print("MIDI In \t");
  CompositeSerial.print(channel);
  CompositeSerial.print("\t");
  CompositeSerial.print(note);
  CompositeSerial.print("\t");
  CompositeSerial.println(velocity);
  #endif

  for(u8 y = 0; y < KEYPADY; y++)
  {
    for(u8 x = 0; x < KEYPADX; x++)
    {
      if(note == keymap[y][x])
      LED.setXYPalette(xytoxy(x, y), channel, velocity);
    }
  }
  //BottomLED
  for(u8 i = 0;i < NUM_BOTTOM_LEDS; i++)
  {
    if(note == bottomLEDmap[i])
    LED.setPalette(i+NUM_LEDS, channel ,velocity);
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
      LED.offXY(xytoxy(x, y));
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

void MIDI::sentXYon(u8 xy, u8 velocity)
{
  u8 y = xy & 0x0F;
  u8 x = (xy & 0xF0) >> 4;
  #ifdef DEBUG
  CompositeSerial.print("MIDI XY Out \t");
  CompositeSerial.print(x);
  CompositeSerial.print("\t");
  CompositeSerial.print(y);
  CompositeSerial.print("\t");
  CompositeSerial.println(velocity);
  #endif


  MIDI::sentNoteOn(midi_channel, keymap[y][x], 127);
}

void MIDI::sentXYoff(u8 xy, u8 velocity)
{
  u8 y = xy & 0x0F;
  u8 x = (xy & 0xF0) >> 4;
  MIDI::sentNoteOff(midi_channel, keymap[y][x], 0);
}

void MIDI::sentNoteOn(u8 channel, u8 note, u8 velocity)
{
  #ifdef DEBUG
  CompositeSerial.print("MIDI Out \t");
  CompositeSerial.print(channel);
  CompositeSerial.print("\t");
  CompositeSerial.print(note);
  CompositeSerial.print("\t");
  CompositeSerial.println(velocity);
  #endif

  USBMIDI.sendNoteOn(channel, note, velocity);
}

void MIDI::sentNoteOff(u8 channel, u8 note, u8 velocity)
{
  USBMIDI.sendNoteOff(channel, note, velocity);
}
