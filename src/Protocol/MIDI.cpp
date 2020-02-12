#include "MIDI.h"

extern LED LED;
// extern USBMIDI USBMidi;

// MIDI::MIDI()
// {
//
// }

void MIDI::noteOn(u8 channel, u8 note, u8 velocity)
{

  #ifdef DEBUG
  CompositeSerial.print("MIDI In On\t");
  CompositeSerial.print(channel);
  CompositeSerial.print("\t");
  CompositeSerial.print(note);
  CompositeSerial.print("\t");
  CompositeSerial.println(velocity);
  #endif

  //LED.on(channel);

  // if(channel == 5)
  //   channel = 1; //unipad support
  if(midi_return)
  {
    USBMIDI::sendNoteOn(channel, note, velocity);
  }

  if(velocity == 0)
  {
    MIDI::noteOff(channel, note, velocity);
  }

  if(unipad_mode)
  channel = 1;

  switch(current_keymap)
  {
    case 0:
    if(note > 35 && note < 100 )
    LED.setXYPalette(user1_keymap_optimized[note-36], channel, velocity);
    break;
    case 1:
    if(note % 10 - 1 < 8)
    LED.setXYPalette(xytoxy(note % 10 - 1, 8 - note/10), channel, velocity);
    break;
    case 2:
    case 3:
    case 4:
    for(u8 y = 0; y < YSIZE; y++)
    {
      for(u8 x = 0; x < XSIZE; x++)
      {
        if(note == keymap[current_keymap][y][x])
        LED.setXYPalette(xytoxy(x, y), channel, velocity);
      }
    }
  }

  offMap[note] = -1;
  // // BottomLED
  // for(u8 i = 0;i < NUM_BOTTOM_LEDS; i++)
  // {
  //   if(note == bottom_led_map[current_keymap][i])
  //   LED.setPalette(i+NUM_LEDS, channel ,velocity);
  // }
}


void MIDI::noteOff(u8 channel, u8 note, u8 velocity)
{

  #ifdef DEBUG
  CompositeSerial.print("MIDI In Off\t");
  CompositeSerial.print(channel);
  CompositeSerial.print("\t");
  CompositeSerial.print(note);
  CompositeSerial.print("\t");
  CompositeSerial.println(velocity);
  #endif


  #ifdef DEBUG
  CompositeSerial.print("MIDI Off \t");
  CompositeSerial.print(channel);
  CompositeSerial.print("\t");
  CompositeSerial.print(note);
  CompositeSerial.print("\t");
  CompositeSerial.println(velocity);
  #endif

  if(midi_return)
  {
    USBMIDI::sendNoteOff(channel, note, velocity);
  }

  if(stfu)
  {
    offMap[note] = stfu;
  }
  else
  {
    switch(current_keymap)
    {
      case 0:
      if(note > 35 && note < 100)
      LED.offXY(user1_keymap_optimized[note - 36]);
      break;
      case 1:
      if(note % 10 - 1 < 8 && note / 10 - 1 < 8 && note > 10 && note < 89) //need add bottom light support
        LED.offXY(xytoxy(note % 10 - 1, 8 - note/10));
      break;
      case 2:
      case 3:
      case 4:
      for(u8 y = 0; y < YSIZE; y++)
      {
        for(u8 x = 0; x < XSIZE; x++)
        {
          if(note == keymap[current_keymap][y][x])
          LED.offXY(xytoxy(x, y));
        }
      }
      break;
    }
  }
  // //BottomLED
  // for(u8 i = 0;i < NUM_BOTTOM_LEDS; i++)
  // {
  //   if(note == bottom_led_map[current_keymap][i])
  //   LED.off(i+NUM_LEDS);
  // }

}

void MIDI::sendXYon(u8 xy, u8 velocity)
{
  u8 y = xy & 0x0F;
  u8 x = (xy & 0xF0) >> 4;

  #ifdef DEBUG
  CompositeSerial.print("MIDI XY Out On \t");
  CompositeSerial.print(x);
  CompositeSerial.print("\t");
  CompositeSerial.print(y);
  CompositeSerial.print("\t");
  CompositeSerial.println(velocity);
  #endif


  USBMIDI::sendNoteOn(midi_channel, keymap[current_keymap][y][x], velocity);
}

void MIDI::sendXYoff(u8 xy, u8 velocity)
{
  u8 y = xy & 0x0F;
  u8 x = (xy & 0xF0) >> 4;

  #ifdef DEBUG
  CompositeSerial.print("MIDI XY Out Off \t");
  CompositeSerial.print(x);
  CompositeSerial.print("\t");
  CompositeSerial.print(y);
  CompositeSerial.print("\t");
  CompositeSerial.println(velocity);
  #endif

  USBMIDI::sendNoteOff(midi_channel, keymap[current_keymap][y][x], 0);
}

void MIDI::handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity)
{
  MIDI::noteOff(channel,note,velocity);
  //USBMIDI::sendNoteOff(channel,note,velocity);
  //leds[IndexInKeyMap(note)] = 0;
  //CompositeSerial.println(channel + " off " + note + " " + velocity);
}

void MIDI::handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity)
{
  MIDI::noteOn(channel,note,velocity);
  //USBMIDI::sendNoteOn(channel,note,velocity);
  //leds[IndexInKeyMap(note)] = color[channel][velocity];
}

// void MIDI::sendNoteOn(u8 channel, u8 note, u8 velocity)
// {
//   // #ifdef DEBUG
//   // CompositeSerial.print("MIDI Out On \t");
//   // CompositeSerial.print(channel);
//   // CompositeSerial.print("\t");
//   // CompositeSerial.print(note);
//   // CompositeSerial.print("\t");
//   // CompositeSerial.println(velocity);
//   // #endif

//   MIDI：：sendNoteOn(channel, note, velocity);
// }

// void MIDI::sendNoteOff(u8 channel, u8 note, u8 velocity)
// {
//   // #ifdef DEBUG
//   // CompositeSerial.print("MIDI Out Off \t");
//   // CompositeSerial.print(channel);
//   // CompositeSerial.print("\t");
//   // CompositeSerial.print(note);
//   // CompositeSerial.print("\t");
//   // CompositeSerial.println(velocity);
//   // #endif

//   if(unipad_mode)
//   {
//     USBMIDI::sendNoteOn(channel, note, 0);
//     return;
//   }
//   USBMIDI::sendNoteOff(channel, note, velocity);
// }

void MIDI::offScan()
{
  if(stfu)
  {
    for(u8 note = 0; note < 128; note ++)
    {
      if(offMap[note] != -1)
      {
        if(offMap[note] == 0)
        switch(current_keymap)
        {
          case 0:
          if(note > 35 && note < 100)
          LED.offXY(user1_keymap_optimized[note - 36]);
          break;
          case 1:
          if(note % 10 - 1 < 8 && note / 10 - 1 < 8 && note > 10 && note < 89)
          LED.offXY(xytoxy(note % 10 - 1, 8 - note/10));
          break;
          case 2:
          case 3:
          case 4:
          for(u8 y = 0; y < YSIZE; y++)
          {
            for(u8 x = 0; x < XSIZE; x++)
            {
              if(note == keymap[current_keymap][y][x])
              LED.offXY(xytoxy(x, y));
            }
          }
          break;
        }
        offMap[note] --;
      }
    }
  }
}
