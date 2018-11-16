#include <USBComposite.h>
#include "CDC.h"
#include "MatrixSysex.h"

// usbmidi MIDI;

USBCompositeSerial CDC;

void CDCDecode()
{
  switch (CDC.read())
  {
    case 0x00://0
      LEDoff(CDC.read(), CDC.read());
      break;
    case 0x01://1
      LEDon(CDC.read(), CDC.read(), CDC.read(), CDC.read(), CDC.read()); //XYRGB
      break;
    case 0x02://2
      LEDon(CDC.read(), CDC.read(), CDC.read(), CDC.read(), CDC.read(), CDC.read()); //XYRGBW
      break;
    case 0x03://3
      LEDon(CDC.read(), CDC.read(), CDC.read()); //XYW
      break;
    case 0x04://4
      LEDon(CDC.read(), CDC.read()); //XY
      break;
    case 0x05://5
      LEDsetPallette(CDC.read(), CDC.read(), CDC.read()); //XYP
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

void CDCpoll()
{
  if (CDC.available() > 0)
  {
    int device = CDC.peek() >> 4;
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
  switch (CDC.read() & 0x0F)
  {
    case 8:
      reset();
      break;
    case 9:
      EnterBootloader();
      break;
    case 10:

      InitializeDevice();
      break;
    case 20:
      UpdateColourPaletteRGB();
      break;
    case 21:
      UpdateColourPaletteWRGB();
      break;
    case 22:
      ResetColourPalette();
      break;
    case 25:
      UpdateCustomKeyMap();
      break;
    case 26:
      ResetCustomKeyMap();
      break;
    case 30:
      SetBrightness(CDC.read());
      break;
    case 31:
      SetTouchSensitive(CDC.read());
      break;
  }
}

void CDCSysexGet()
{
  switch(CDC.read() & 0x0F)
  {
    case 0:
      GetDeviceInfo();
      break;
    case 1:
      GetModuleCount();
      break;
    case 2:
      GetModuleInfo();
      break;
    case 5:
      GetAllParameter();
      break;
    case 20:
      GetColorPaletteRGB();
      break;
    case 21:
      GetColorPaletteWRGB();
      break;
    case 24:
      GetGammaState();
      break;
    case 25:
      GetCustomKeyMap();
      break;
    case 30:
      GetBrightness();
      break;
    case 31:
      GetTouchSensitive();
      break;
  }
}

void CDCMIDI()
{
  int Mode = CDC.peek() >> 4;
  int Channel = CDC.read() & 0x0F;
  int Note = CDC.read();
  int Velocity = CDC.read();
   // switch (Mode)
   // {
   //   case 8:
   //     MIDI.handleNoteOff(Channel, Note, Velocity);
   //   case 9:
   //     MIDI.handleNoteOff(Channel, Note, Velocity);
   // }
}
