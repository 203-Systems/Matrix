#include "MIDI.h"

#ifdef DEBUG
#include <USBComposite.h>
#endif

extern LED LED;

// MIDI::MIDI()
// {
//
// }

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

  //LED.on(channel);

  // if(channel == 5)
  //   channel = 1; //unipad support

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

  #ifdef DEBUG
  CompositeSerial.print("MIDI Off \t");
  CompositeSerial.print(channel);
  CompositeSerial.print("\t");
  CompositeSerial.print(note);
  CompositeSerial.print("\t");
  CompositeSerial.println(velocity);
  #endif

  offMap[note] = 2;
  // //BottomLED
  // for(u8 i = 0;i < NUM_BOTTOM_LEDS; i++)
  // {
  //   if(note == bottom_led_map[current_keymap][i])
  //   LED.off(i+NUM_LEDS);
  // }

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


  MIDI::sentNoteOn(midi_channel, keymap[current_keymap][y][x], 127);
}

void MIDI::sentXYoff(u8 xy, u8 velocity)
{
  u8 y = xy & 0x0F;
  u8 x = (xy & 0xF0) >> 4;
  MIDI::sentNoteOff(midi_channel, keymap[current_keymap][y][x], 0);
}

void MIDI::handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity)
{
  MIDI::noteOff(channel,note,velocity);
  //USBMIDI.sendNoteOff(channel,note,velocity);
  //leds[IndexInKeyMap(note)] = 0;
  //CompositeSerial.println(channel + " off " + note + " " + velocity);
}

void MIDI::handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity)
{
  MIDI::noteOn(channel,note,velocity);
  //USBMIDI.sendNoteOn(channel,note,velocity);
  //leds[IndexInKeyMap(note)] = colour[channel][velocity];
}

// void MIDI::registerComponent()
// {
//   USBMIDI.registerComponent();
// }

// bool MIDI::available()
// {
//   return USBMIDI.available();
// }

// void MIDI::poll()
// {
//   USBMIDI.poll();
//   MIDI::offScan();
// }

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
  if(unipad_mode)
  {
    USBMIDI.sendNoteOn(channel, note, 0);
    return;
  }
  USBMIDI.sendNoteOff(channel, note, velocity);
}

// void MIDI::sendVelocityChange(u8 channel, u8 note, u8 velocity)
// {
//   USBMIDI.sendVelocityChange(channel, note, velocity);
// }
//
// void MIDI::sendControlChange(u8 channel, u8 controller, u8 value)
// {
//   USBMIDI.sendControlChange(channel, controller, value);
// }
//
// void MIDI::sendProgramChange(u8 channel, u8 program)
// {
//   USBMIDI.sendProgramChange(channel,program);
// }
//
// void MIDI::sendAfterTouch(u8 channel, u8 velocity)
// {
//   USBMIDI.sendAfterTouch(channel, velocity);
// }
//
// void MIDI::sendPitchChange(u16 pitch)
// {
//   USBMIDI.sendPitchChange(pitch);
// }
//
// void MIDI::sendSongPosition(u16 position)
// {
//   USBMIDI.sendSongPosition(position);
// }
//
// void MIDI::sendSongSelect(u16 song)
// {
//   USBMIDI.sendSongSelect(song);
// }
//
// void MIDI::sendTuneRequest()
// {
//   USBMIDI.sendTuneRequest();
// }
//
// void MIDI::sendSync()
// {
//   USBMIDI.sendSync();
// }
//
// void MIDI::sendStart()
// {
//   USBMIDI.sendStart();
// }
//
// void MIDI::sendContinue()
// {
//   USBMIDI.sendContinue();
// }
//
// void MIDI::sendStop()
// {
//   USBMIDI.sendStop();
// }
//
// void MIDI::sendActiveSense()
// {
//   USBMIDI.sendActiveSense();
// }
//
// void MIDI::sendReset()
// {
//   USBMIDI.sendReset();
// }


void MIDI::offScan()
{
  for(u8 note = 0; note < 128; note ++)
  {
    if(offMap[note] != -1)
    {
      if(offMap[note] == 0)
      switch(current_keymap)
      {
        case 0:
        if(note > 35 && note < 100 )
        LED.offXY(user1_keymap_optimized[note - 36]);
        break;
        case 1:
        if(note % 10 - 1 < 8)
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
