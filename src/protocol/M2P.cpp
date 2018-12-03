#include "M2P.h"

extern LED LED;
extern MatrixSystem Matrix;
extern MIDI Midi;
extern SerialComposite Serials;

M2P::M2P()
{

}

void M2P::poll()
{
  if (CompositeSerial.available() > 0)
  {
    int device = CompositeSerial.peek() >> 4;
    if (device == 0)
    {
      decode();
    }
    if (device > 0 && device < 8) //Modular
    {
      decode();
    }
    else
    {
      //ERRoR checking
    }
  }
}

void M2P::decode()
{
  if(CompositeSerial.peek() > 0x0f) //ERRoR checking
  return;

  switch (CompositeSerial.read()) //ToDo uint8_t To UINT4+UINT4
  {
    case 0x00://0
    LED.off(CompositeSerial.peek() & 0xF0, CompositeSerial.read() & 0x0F);
    break;
    case 0x01://1
    LED.off(CompositeSerial.read());
    break;
    case 0x02://2
    LED.setRGB(CompositeSerial.peek() & 0xF0, CompositeSerial.read() & 0x0F, CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYRGB
    break;
    case 0x03://3
    LED.setRGB(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYRGB
    break;
    case 0x04://4
    LED.setWRGB(CompositeSerial.peek() & 0xF0, CompositeSerial.read() & 0x0F, CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYWRGB
    break;
    case 0x05://5
    LED.setWRGB(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYWRGB
    break;
    case 0x06://6
    LED.setW(CompositeSerial.peek() & 0xF0, CompositeSerial.read() & 0x0F, CompositeSerial.read()); //XYW
    break;
    case 0x07://7
    LED.setW(CompositeSerial.read(), CompositeSerial.read()); //XYW
    break;
    case 0x08://8
    LED.on(CompositeSerial.read()); //XY
    break;
    case 0x09://9
    LED.on(CompositeSerial.read()); //XY
    break;
    case 0x0A://10
    LED.setPalette(CompositeSerial.peek() & 0xF0, CompositeSerial.read() & 0x0F,CompositeSerial.read(), CompositeSerial.read()); //XYP
    break;
    case 0x0B://11
    LED.setPalette(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYP
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
    Matrix.reset();
    break;
    case 9:
    Matrix.enterBootloader();
    break;
    case 10:
    Matrix.initializeDevice();
    break;
    case 20:
    Matrix.updateColourPaletteRGB();
    break;
    case 21:
    Matrix.updateColourPaletteWRGB();
    break;
    case 22:
    Matrix.resetColourPalette();
    break;
    case 24:
    Matrix.setGamma((bool)CompositeSerial.read());
    case 25:
    Matrix.updateCustomKeymap();
    break;
    case 26:
    Matrix.resetCustomKeymap();
    break;
    case 30:
    Matrix.setBrightness(CompositeSerial.read());
    break;
    case 31:
    Matrix.setTouchSensitive(CompositeSerial.read());
    break;
  }
}

void M2P::sysexGet()
{
  switch(CompositeSerial.read() & 0x0F)
  {
    case 0:
    Matrix.getDeviceInfo();
    break;
    case 1:
    Matrix.getModuleCount();
    break;
    case 2:
    Matrix.getModuleInfo();
    break;
    case 5:
    Matrix.getAllParameter();
    break;
    case 20:
    Matrix.getColorPaletteRGB();
    break;
    case 21:
    Matrix.getColorPaletteWRGB();
    break;
    case 24:
    Matrix.getGammaState();
    break;
    case 25:
    Matrix.getCustomKeymap();
    break;
    case 30:
    Matrix.getBrightness();
    break;
    case 31:
    Matrix.getTouchSensitive();
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
    Midi.sentNoteoff(Channel, Note, Velocity);
    case 9:
    Midi.sentNoteon(Channel, Note, Velocity);
  }
}
