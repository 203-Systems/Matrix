#include "CDC.h"

LED LED;

CDC::CDC()
{
  CompositeSerial.registerComponent();
}

void CDC::Poll()
{
  if (CompositeSerial.available() > 0)
  {
    int device = CompositeSerial.peek() >> 4;
    if (device == 0)
    {
      Decode();
    }
    if (device > 0 && device < 8) //Modular
    {
      Decode();
    }
    else
    {
      //Corrupt Packet
    }
  }
}

void CDC::Decode()
{
  switch (CompositeSerial.read())
  {
    case 0x00://0
    LED.Off(CompositeSerial.read(), CompositeSerial.read());
    break;
    case 0x01://1
    LED.SetRGB(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYRGB
    break;
    case 0x02://2
    LED.SetWRGB(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYWRGB
    break;
    case 0x03://3
    LED.SetW(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYW
    break;
    case 0x04://4
    LED.On(CompositeSerial.read(), CompositeSerial.read()); //XY
    break;
    case 0x05://5
    LED.SetPallette(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYP
    break;
    case 0x0D://14
    SysexSet();
    break;
    case 0x0E://14
    SysexGet();
    break;
    case 0x0F://15
    MIDI();
    break;
  }
}

void CDC::SysexSet()
{
  switch (CompositeSerial.read() & 0x0F)
  {
    // case 8:
    // reset();
    // break;
    // case 9:
    // Matrix.EnterBootloader();
    // break;
    // case 10:
    // Matrix.InitializeDevice();
    // break;
    // case 20:
    // Matrix.UpdateColourPaletteRGB();
    // break;
    // case 21:
    // Matrix.UpdateColourPaletteRGBW();
    // break;
    // case 22:
    // Matrix.ResetColourPalette();
    // break;
    // case 25:
    // Matrix.UpdateCustomKeyMap();
    // break;
    // case 26:
    // Matrix.ResetCustomKeyMap();
    // break;
    // case 30:
    // Matrix.SetBrightness(CompositeSerial.read());
    // break;
    // case 31:
    // Matrix.SetTouchSensitive(CompositeSerial.read());
    // break;
  }
}

void CDC::SysexGet()
{
  switch(CompositeSerial.read() & 0x0F)
  {

  }
}

void CDC::MIDI()
{
  int Mode = CompositeSerial.peek() >> 4;
  int Channel = CompositeSerial.read() & 0x0F;
  int Note = CompositeSerial.read();
  int Velocity = CompositeSerial.read();
  //  switch (Mode) {
  //    case 8:
  //      midi.handleNoteOff(Channel, Note, Velocity);
  //    case 9:
  //      midi.handleNoteOff(Channel, Note, Velocity);
  //  }
}
