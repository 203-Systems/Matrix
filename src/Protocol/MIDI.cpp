#include "MIDI.h"

extern LED LED;
extern UI UI;
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
  if (midi_return)
  {
    USBMIDI::sendNoteOn(channel, note, velocity);
  }

  if (velocity == 0)
  {
    MIDI::noteOff(channel, note, velocity);
  }

  if (unipad_mode)
    channel = 1;

  switch (current_keymap)
  {
  case 0:
    if (note > 35 && note < 100)
      LED.setXYPalette(user1_keymap_optimized[note - 36], channel, velocity);
    break;
  case 1:
    if (note % 10 - 1 < 8)
      LED.setXYPalette(xytoxy(note % 10 - 1, 8 - note / 10), channel, velocity);
    break;
  case 2:
  case 3:
  case 4:
    for (u8 y = 0; y < YSIZE; y++)
    {
      for (u8 x = 0; x < XSIZE; x++)
      {
        if (note == keymap[current_keymap][y][x])
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

  if (midi_return)
  {
    USBMIDI::sendNoteOff(channel, note, velocity);
  }

  if (stfu)
  {
    offMap[note] = stfu;
  }
  else
  {
    switch (current_keymap)
    {
    case 0:
      if (note > 35 && note < 100)
        LED.offXY(user1_keymap_optimized[note - 36]);
      break;
    case 1:
      if (note % 10 - 1 < 8 && note / 10 - 1 < 8 && note > 10 && note < 89) //need add bottom light support
        LED.offXY(xytoxy(note % 10 - 1, 8 - note / 10));
      break;
    case 2:
    case 3:
    case 4:
      for (u8 y = 0; y < YSIZE; y++)
      {
        for (u8 x = 0; x < XSIZE; x++)
        {
          if (note == keymap[current_keymap][y][x])
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
  MIDI::noteOff(channel, note, velocity);
  //USBMIDI::sendNoteOff(channel,note,velocity);
  //leds[IndexInKeyMap(note)] = 0;
  //CompositeSerial.println(channel + " off " + note + " " + velocity);
}

void MIDI::handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity)
{
  MIDI::noteOn(channel, note, velocity);
  //USBMIDI::sendNoteOn(channel,note,velocity);
  //leds[IndexInKeyMap(note)] = color[channel][velocity];
}

void MIDI::offScan()
{
  if (stfu)
  {
    for (u8 note = 0; note < 128; note++)
    {
      if (offMap[note] != -1)
      {
        if (offMap[note] == 0)
          switch (current_keymap)
          {
          case 0:
            if (note > 35 && note < 100)
              LED.offXY(user1_keymap_optimized[note - 36]);
            break;
          case 1:
            if (note % 10 - 1 < 8 && note / 10 - 1 < 8 && note > 10 && note < 89)
              LED.offXY(xytoxy(note % 10 - 1, 8 - note / 10));
            break;
          case 2:
          case 3:
          case 4:
            for (u8 y = 0; y < YSIZE; y++)
            {
              for (u8 x = 0; x < XSIZE; x++)
              {
                if (note == keymap[current_keymap][y][x])
                  LED.offXY(xytoxy(x, y));
              }
            }
            break;
          }
        offMap[note]--;
      }
    }
  }
}

void MIDI::handleSysex(uint8_t *sysexBuffer, uint32 len)
{
#ifdef DEBUG
  CompositeSerial.print("Sysex - len:");
  CompositeSerial.print(len);
  CompositeSerial.print(" ");
  for (int i = 0; i < len; i++)
  {
    CompositeSerial.print(sysexBuffer[i]);
    CompositeSerial.print(" ");
  }
  CompositeSerial.println();
#endif

  if (!memcmp(sysexBuffer, SYSEX_HEADER, 5)) //Matrix Specific
  {
    if (sysexBuffer[5] == 0x12)
    {
#ifdef DEBUG
      CompositeSerial.println("Sysex - Matrix Specific - Write");
#endif
      switch (sysexBuffer[6])
      {
      case 0: //Enter Bootloader
        enterBootloader();
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
        MIDI::scrollText(sysexBuffer, len);
        break;
      case 4:
        break;
      case 16: //LED index
      case 17: //LED XY
        MIDI::setLED(sysexBuffer, len);
        break;
      }
    }
    else if (sysexBuffer[5] == 0x11)
    {
#ifdef DEBUG
      CompositeSerial.println("Sysex - Matrix Specific - Read");
#endif
    }
  }
  else if (sysexBuffer[0] == 0x7E) //Non Real Time Universal
  {
#ifdef DEBUG
    CompositeSerial.println("Sysex - Non Real Time Universal");
#endif
    if (!memcmp(sysexBuffer + 1, IDENTITY_REQUEST, 2))
    {
      MIDI::identityReply();
    }
  }
  else if (sysexBuffer[0] == 0x7F) //Real Time Universal
  {
#ifdef DEBUG
    CompositeSerial.println("Sysex - Real Time Universal");
#endif
  }
  else
  {
    //Bruh, who tf sent this to me? Not my packet.
  }
}

void MIDI::identityReply()
{
  u8 identity[13] = {0x7E, 0x06, 0x02, SYSEXID[0], SYSEXID[1], SYSEXID[2], PID >> 8, PID & 0x7F, device_id & 0x7F, MAJOR_VER, MINOR_VER, PATCH_VER, BUILD_VER};
  USBMIDI::sendSysex(identity, 13);
}

// void MIDI::serialNumberReply()
// {
//   u8 identity[13] = {0x7E, 0x06, 0x02, SYSEXID[0], SYSEXID[1], SYSEXID[2], PID >> 8 , PID & 0x7F, device_id & 0x7F, MAJOR_VER, MINOR_VER, PATCH_VER, BUILD_VER};
//   USBMIDI::sendSysex(identity, 13);
// }

void MIDI::scrollText(uint8_t *sysexBuffer, uint16_t len)
{
  sysexBuffer += 7;

  bool loop = sysexBuffer[0];
  u8 speed = sysexBuffer[1];
  CRGB color = dispatchColorStruct(&sysexBuffer[2]);
  u8 offset = dispatchColorDataOffset(sysexBuffer[2]) + 1;
  len = len - 5 - offset;
  sysexBuffer += (offset + 2);
#ifdef DEBUG
  CompositeSerial.print("Sysex Text scroll ");
  CompositeSerial.print(loop);
  CompositeSerial.print(" ");
  CompositeSerial.print(speed);
  CompositeSerial.print(" ");
  CompositeSerial.print(color.r);
  CompositeSerial.print(" ");
  CompositeSerial.print(color.g);
  CompositeSerial.print(" ");
  CompositeSerial.print(color.b);
  CompositeSerial.print(" ");
  CompositeSerial.print(offset);
  CompositeSerial.print(" ");
  CompositeSerial.println(len);
  for (int i = 0; i < len; i++)
  {
    CompositeSerial.print((char)sysexBuffer[i]);
  }
  CompositeSerial.println();
#endif

  //Create array
  char ascii[len + 1];
  memcpy(ascii, sysexBuffer, len);
  ascii[len] = 0;
  UI.scrollText(ascii, CRGBtoHEX(color), speed, loop);
}


void MIDI::setLED(uint8_t *sysexBuffer, uint16_t len)
{
  bool xy = sysexBuffer[6] == 17;
  u8 color_type = sysexBuffer[7];
  bool gamma = dispatchColorStructGamma(color_type);
  bool overlay = dispatchColorStructOverlay(color_type);
  u8 block_size = dispatchColorDataOffset(color_type) + 2;
  sysexBuffer += 8;
  for (u8 i = 0; i < len - 8; i += block_size)
  {

    CRGB color = dispatchColorData(color_type, sysexBuffer + i + 2);
    if (xy)
    {
      u8 xy = (sysexBuffer[i] << 4) + (sysexBuffer[i + 1] & 0x0F);
      LED.setXYCRGB(xy, color, overlay, gamma);
#ifdef DEBUG
      CompositeSerial.print("Sysex LED Set XY ");
      CompositeSerial.print(color_type);
      CompositeSerial.print(" ");
      CompositeSerial.print(xy);
      CompositeSerial.print(" ");
      CompositeSerial.print(overlay);
      CompositeSerial.print(" ");
      CompositeSerial.print(gamma);
      CompositeSerial.print(" ");
      CompositeSerial.print(color.r);
      CompositeSerial.print(" ");
      CompositeSerial.print(color.g);
      CompositeSerial.print(" ");
      CompositeSerial.println(color.b);
#endif
    }
    else
    {
      LED.setCRGB(sysexBuffer[i + 1], color, overlay, gamma);
#ifdef DEBUG
      CompositeSerial.print("Sysex LED Set ");
      CompositeSerial.print(color_type);
      CompositeSerial.print(" ");
      CompositeSerial.print(sysexBuffer[i + 1]);
      CompositeSerial.print(" ");
      CompositeSerial.print(overlay);
      CompositeSerial.print(" ");
      CompositeSerial.print(gamma);
      CompositeSerial.print(" ");
      CompositeSerial.print(color.r);
      CompositeSerial.print(" ");
      CompositeSerial.print(color.g);
      CompositeSerial.print(" ");
      CompositeSerial.println(color.b);
#endif
    }
  }
}