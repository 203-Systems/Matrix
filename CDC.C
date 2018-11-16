#include <USBComposite.h>
#include <CDC.h>
#include <MatrixSysex.h>

MatrixSysex Sysex;
usbmidi MIDI;

void CDCDecode()
{
  switch (CompositeSerial.read())
  {
    case 0x00://0
      LEDoff(CompositeSerial.read(), CompositeSerial.read());
      break;
    case 0x01://1
      LEDon(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYRGB
      break;
    case 0x02://2
      LEDon(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYRGBW
      break;
    case 0x03://3
      LEDon(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYW
      break;
    case 0x04://4
      LEDon(CompositeSerial.read(), CompositeSerial.read()); //XY
      break;
    case 0x05://5
      LEDsetPallette(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYP
      break;
    case 0x0D://14
      CDCSysexSet();
      break;
    case 0x0E://14
      CDCSysexGet();
      break;
    case 0x0F://15
      CDCMIDI();
      break;
  }
}

void poll()
{
  if (CompositeSerial.available() > 0)
  {
    int device = CompositeSerial.peek() >> 4;
    if (device == 0)
    {
    CDCDecode();
    }
    if (device > 0 && device < 8) {
    CDCDecode();
    }
    else
    {
    }
  }
}

void CDCSysexSet()
{
  switch (CompositeSerial.read() & 0x0F)
  {
    case 8:
      Sysex.reset();
      break;
    case 9:
      Sysex.EnterBootloader();
      break;
    case 10:

      Sysex.InitializeDevice();
      break;
    case 20:
      Sysex.UpdateColourPaletteRGB();
      break;
    case 21:
      Sysex.UpdateColourPaletteWRGB();
      break;
    case 22:
      Sysex.ResetColourPalette();
      break;
    case 25:
      Sysex.UpdateCustomKeyMap();
      break;
    case 26:
      Sysex.ResetCustomKeyMap();
      break;
    case 30:
      Sysex.SetBrightness(CompositeSerial.read());
      break;
    case 31:
      Sysex.SetTouchSensitive(CompositeSerial.read());
      break;
  }
}

void CDCSysexGet()
{
  switch(CompositeSerial.read() & 0x0F)
  {
    case 0:
      Sysex.GetDeviceInfo();
      break;
    case 1:
      Sysex.GetModuleCount();
      break;
    case 2：
      Sysex.GetModuleInfo();
      break;
    case 5:
      Sysex.GetAllParameter();
      break;
    case 20:
      Sysex.GetColorPaletteRGB();
      break;
    case 21:
      Sysex.GetColorPaletteWRGB();
      break;
    case 24:
      Sysex.GetGammaState();
      break;
    case 25:
      Sysex.GetCustomKeyMap();
      break;
    case 30:
      Sysex.GetBrightness();
      break;
    case 31:
      Sysex.GetTouchSensitive();
      break;
  }
}

void CDCMIDI()
{
  int Mode = CompositeSerial.peek() >> 4;
  int Channel = CompositeSerial.read() & 0x0F;
  int Note = CompositeSerial.read();
  int Velocity = CompositeSerial.read();
   switch (Mode)
   {
     case 8:
       MIDI.handleNoteOff(Channel, Note, Velocity);
     case 9:
       MIDI.handleNoteOff(Channel, Note, Velocity);
   }
}
