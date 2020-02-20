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
      //System
      case 0: //Enter Bootloader
        enterBootloader();
        break;
      case 1: //Reboot Device
        reboot();
        break;
      case 2: //Clear Device Config
        UI.clearEEPROM();
        break;
      case 3:
        UI.standbyMode();
        break;
      case 4:
        break;
      //LED
      case 32: //LED index
      case 33: //LED XY
        MIDI::setLED(sysexBuffer, len);
        break;

      //Graphic
      case 59:
        MIDI::scrollText(sysexBuffer, len);
        break;

      //Config/Custom Data
      case 64: //Set Variable
      case 65: //Inject Palette 7bit
        MIDI::writePalette(sysexBuffer, len);
        break;
      }
    }
    else if (sysexBuffer[5] == 0x11)
    {
#ifdef DEBUG
      CompositeSerial.println("Sysex - Matrix Specific - Read");
#endif
      switch (sysexBuffer[6])
      {
      case 16:
        MIDI::replyDeviceName();
        break;
      case 17: //Get Device Hardware Serial
        MIDI::replySerialNumber();
        break;
      case 18: //Device Firmware
        MIDI::replyFirmwareVersion(len != 6 && sysexBuffer[7] == 1);
        break;
      case 19: //Device ID
        MIDI::replyDeviceID();
        break;
      }
    }
  }
  else if (sysexBuffer[0] == 0x7E) //Non Real Time Universal
  {
#ifdef DEBUG
    CompositeSerial.println("Sysex - Non Real Time Universal");
#endif
    if (!memcmp(sysexBuffer + 1, IDENTITY_REQUEST, 2))
    {
      MIDI::replyIdentity();
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

void MIDI::sendSysexWithHeader(u8 *sysex, u8 len)
{
  u8 message[5 + len];
  memcpy(message, SYSEX_HEADER, 5);
  memcpy(&message[5], sysex, len);
#ifdef DEBUG
  CompositeSerial.print("send Sysex with header len:");
  CompositeSerial.print(sizeof(message));
  CompositeSerial.println();
  for (u8 i = 0; i < sizeof(message); i++)
  {
    CompositeSerial.print(message[i], HEX);
    CompositeSerial.print(" ");
  }
  CompositeSerial.println();
  for (u8 i = 0; i < len; i++)
  {
    CompositeSerial.print(sysex[i], HEX);
    CompositeSerial.print(" ");
  }
  CompositeSerial.println();
#endif

  USBMIDI::sendSysex(message, 5 + len);
}

void MIDI::replyIdentity()
{
  u8 identity[14] = {0x7E, 0x06, 0x02, SYSEXID[0], SYSEXID[1], SYSEXID[2], PID >> 8, PID & 0x7F, device_id >> 7, device_id & 0x7F, MAJOR_VER, MINOR_VER, PATCH_VER, BUILD_VER};
  USBMIDI::sendSysex(identity, 14);
}

void MIDI::replyDeviceName()
{
  u8 reply[2 + device_name.length()];
  reply[0] = 0x12;
  reply[1] = 0x10;
  memcpy(&reply[2], device_name.c_str(), device_name.length());
  MIDI::sendSysexWithHeader(reply, sizeof(reply));
}

void MIDI::replySerialNumber()
{
  //   u32 serial[3] = {DEVICE_SERIAL_1, DEVICE_SERIAL_2, DEVICE_SERIAL_3};

  //   #ifdef DEBUG
  //   CompositeSerial.print(serial[0], HEX);
  //   CompositeSerial.print(serial[1], HEX);
  //   CompositeSerial.println(serial[2], HEX);
  //   #endif

  //   u8 reply[16] = {0x12, 0x17};
  //   for(u8 i = 0; i < 96; i ++)
  //   {
  //     bitWrite(reply[2+i/7], i%7, bitRead(serial[i/32], i%32));
  //   }
  //   MIDI::sendSysexWithHeader(reply, 16);

  //   #ifdef DEBUG
  //     for (int i = 0; i < 14; i++)
  //   {
  //     CompositeSerial.print(reply[2+i], HEX);
  //     CompositeSerial.print(" ");
  //   }
  //   CompositeSerial.println();
  // #endif
  u8 reply[26] = {0x12, 0x11};
  char serial_buffer[25];
  getDeviceSerialString().toCharArray(serial_buffer, 25);
#ifdef DEBUG
  CompositeSerial.print("Sysex Request Serial Number ");
  CompositeSerial.println(getDeviceSerialString().c_str());
#endif

  memcpy(&reply[2], serial_buffer, 24);
  MIDI::sendSysexWithHeader(reply, 26);
}

void MIDI::replyFirmwareVersion(u8 mode)
{
  if (mode == 1)
  {
    u8 reply[7] = {0x12, 0x12, 0x01, MAJOR_VER, MINOR_VER, PATCH_VER, BUILD_VER};
    MIDI::sendSysexWithHeader(reply, sizeof(reply));
  }
  else
  {
    u8 reply[3 + sizeof(FWVERSION_STRING) - 1];
    reply[0] = 0x12;
    reply[1] = 0x18;
    reply[2] = 0x00;
    memcpy(&reply[3], FWVERSION_STRING, sizeof(FWVERSION_STRING) - 1);
    MIDI::sendSysexWithHeader(reply, sizeof(reply));
#ifdef DEBUG
    CompositeSerial.print("Sysex Request Device Firmware Version (ASCII) len:");
    CompositeSerial.print(sizeof(FWVERSION_STRING));
    CompositeSerial.print(" ");
    CompositeSerial.println(FWVERSION_STRING);
#endif
  }
}

void MIDI::replyDeviceID()
{
  u8 reply[4] = {0x12, 0x13, device_id >> 7, device_id & 0b01111111};
  MIDI::sendSysexWithHeader(reply, sizeof(reply));
}

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
  bool xy_mode = sysexBuffer[6] == 33;
  u8 led_class;

  if(!xy_mode)
  {
    led_class = sysexBuffer[7]; //Ignore for now, since <LED Class> Isn't implented yet
    sysexBuffer ++;
  }

  u8 color_type = sysexBuffer[7];
  bool gamma = dispatchColorStructGamma(color_type);
  bool overlay = dispatchColorStructOverlay(color_type);
  u8 block_size = dispatchColorDataOffset(color_type) + 1 + xy_mode;
  sysexBuffer += 8;

  for(u8 i = 0; i < len - 8 - !xy_mode; i += block_size)
  {

    CRGB color = dispatchColorData(color_type, sysexBuffer + i + 1 + xy_mode);
    if (xy_mode)
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
      LED.setCRGB(sysexBuffer[i], color, overlay, gamma);
#ifdef DEBUG
      CompositeSerial.print("Sysex LED Set ");
      CompositeSerial.print(led_class);
      CompositeSerial.print(" ");
      CompositeSerial.print(color_type);
      CompositeSerial.print(" ");
      CompositeSerial.print(sysexBuffer[i]); //Index
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
      // CompositeSerial.print(i);
      // CompositeSerial.print(" ");
      // CompositeSerial.print(len - 8 - !xy_mode);
      // CompositeSerial.print(" ");
      // CompositeSerial.println(block_size);
#endif
    }
  }
}

void MIDI::writePalette(uint8_t *sysexBuffer, uint16_t len)
{
  u8 palette_index = sysexBuffer[7];
#ifdef DEBUG
  CompositeSerial.print("Sysex Inject Palette ");
  CompositeSerial.print(palette_index);
#endif
  if (sysexBuffer[6] == 0x40 && len == 392) //7bit
  {
#ifdef DEBUG
    CompositeSerial.println("7bit");
#endif
    sysexBuffer += 8;
    for (u8 i = 0; i < 128; i++)
    {
      CRGB color = CRGB(
          convert_7BitTo8Bit(sysexBuffer[i * 3 + 0]),
          convert_7BitTo8Bit(sysexBuffer[i * 3 + 1]),
          convert_7BitTo8Bit(sysexBuffer[i * 3 + 2]));
      saveColorToEEPROM(palette_index, i, color);
    }
  }
  else if (sysexBuffer[6] == 0x41 && len == 520) //8bit
  {
  }
  setupPalette();
}