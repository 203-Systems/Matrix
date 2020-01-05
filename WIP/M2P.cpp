#include "M2P.h"

extern LED LED;

extern MIDI Midi;
//extern SerialComposite Serials;

M2P::M2P()
{

}

void M2P::poll()
{
  if (CompositeSerial.available() > 0)
  {
    if(CompositeSerial.peek() && b11000000 == b10000000) //header1 check
    {
      u16
    }
  }
}

u16 codeAddress(u16 uncodedAddress)
{
  if(decompressed == 0)
  return 0;

  // while(decompressed < 10000)
  // decompressed *= 10;

  int compressed = 0;

  for(u8 i = 0; i < 4; i++)
  {
    uncodedAddress %= pow(10, 5 - i);
    uncodedAddress -= pow(10, 4 - i);
    codedAddress += codedAddress / 10000 * + 1;

    if(uncodedAddress % pow(10, 4 - i) == 0)
    return codedAddress;
  }

  uncodedAddress %= 10;
  uncodedAddress -= 1;

  return codedAddress + decompress + 1;
}

u16 decodeAddress(u16 codedAddress)
{
  u16 uncodedAddress = 0;

  if(codedAddress == 0)
  return 0;


  for(u8 i = 0; i < 4; i++)
  {
    codedAddress--;
    uncodedAddress += (codedAddress / magicnumber[i] + 1) * pow(10,4 - i);
    codedAddress = codedAddress % magicnumber[i];

    if(codedAddress == 0)
    return uncodedAddress;
  }
  return uncodedAddress + codedAddress;
}

void M2P::decode()
{
  if(CompositeSerial.peek() > 0x0f) //ERRoR checking
  return;

  switch (CompositeSerial.read()) //ToDo u8 To UINT4+UINT4
  {
    case 0x00://0
    LED.off(CompositeSerial.peek()); //XY off
    break;
    case 0x01://1
    LED.off(CompositeSerial.read()); //index Off
    break;
    case 0x02://2
    LED.setXYRGB(CompositeSerial.peek(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XY RGB
    break;
    case 0x03://3
    LED.setRGB(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //index RGB
    break;
    case 0x04://4
    LED.setXYWRGB(CompositeSerial.peek(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //index WRGB
    break;
    case 0x05://5
    LED.setWRGB(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XY WRGB
    break;
    case 0x06://6
    LED.setXYW(CompositeSerial.peek(), CompositeSerial.read()); //XY W
    break;
    case 0x07://7
    LED.setW(CompositeSerial.read(), CompositeSerial.read()); //index W
    break;
    case 0x08://8
    LED.onXY(CompositeSerial.peek()); //XY On
    break;
    case 0x09://9
    LED.on(CompositeSerial.read()); //index On
    break;
    case 0x0A://10
    LED.setXYPalette(CompositeSerial.peek(),CompositeSerial.read(), CompositeSerial.read()); //XY Palette
    break;
    case 0x0B://11
    LED.setPalette(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //index Palette
    break;
    case 0x0C://12
    //Well... Nothing yet XD
    break;
    case 0x0D://13
    sysexSet();
    break;
    case 0x0E://14
    sysexGet();
    break;
    case 0x0F://15
    toMIDI();
    break;
  }
}

void M2P::sysexSet()
{
  switch (CompositeSerial.read() & 0x0F)
  {
    case 8:
    reset();
    break;
    case 9:
    enterBootloader();
    break;
    case 10:
    resetDevice();
    break;
    case 20:
    updatePaletteRGB();
    break;
    case 21:
    updatePaletteWRGB();
    break;
    case 22:
    resetPalette();
    break;
    case 24:
    setgamma((bool)CompositeSerial.read());
    case 25:
    updateCustomKeymap();
    break;
    case 26:
    resetCustomKeymap();
    break;
    case 30:
    setBrightness(CompositeSerial.read());
    break;
    case 31:
    setTouchSensitive(CompositeSerial.read());
    break;
  }
}

void M2P::sysexGet()
{
  switch(CompositeSerial.read() & 0x0F)
  {
    case 0:
    getDeviceInfo();
    break;
    case 1:
    getModuleCount();
    break;
    case 2:
    getModuleInfo();
    break;
    case 5:
    getAllParameter();
    break;
    case 20:
    getPaletteRGB();
    break;
    case 21:
    getPaletteWRGB();
    break;
    case 24:
    getgammaState();
    break;
    case 25:
    getCustomKeymap();
    break;
    case 30:
    getBrightness();
    break;
    case 31:
    getTouchSensitive();
    break;
  }
}

void M2P::toMIDI()
{
  int Mode = CompositeSerial.peek() >> 4;
  int Channel = CompositeSerial.read() & 0x0F;
  int Note = CompositeSerial.read();
  int Velocity = CompositeSerial.read();
  switch (Mode) {
    case 8:
    Midi.sentNoteOff(Channel, Note, Velocity);
    case 9:
    Midi.sentNoteOn(Channel, Note, Velocity);
  }
}
