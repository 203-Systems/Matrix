#include "MatrixSystem.h"

void variableLoad()
{

}


//Sysex set
void reset()
{
  digitalWrite(RESET_PIN,LOW);
}

void setDeviceID()
{
  device_id = CompositeSerial.read();
  reset();
}


void enterBootloader()
{
  reset();
}

void initializeDevice()
{
  //TODO
}

void updateColourPaletteRGB()
{
  if(CompositeSerial.peek() < 128)
  {
    palette[2][CompositeSerial.read()] = wrgbToHEX(0,CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read());
  }
  else if(CompositeSerial.peek() == 255)
  {
    return;
  }
}

void updateColourPaletteWRGB()
{
  if(CompositeSerial.peek() < 128)
  {
    palette[2][CompositeSerial.read()] = wrgbToHEX(CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read());
  }
  else if(CompositeSerial.peek() == 255)
  {
    return;
  }
}

void resetColourPalette()
{
  // for(int i = 0; i < sizeof(palette[0]); i++)
  // {
  //   palette[2][i] = palette[0][i];
  // }
}

void setGamma(bool g)
{
  gamma_enable = g;
}

void updateCustomKeymap()
{
  while(CompositeSerial.peek() != 255)
  {
    keymap[CompositeSerial.read()][CompositeSerial.read()] = CompositeSerial.read();
  }
}

void resetCustomKeymap()
{
  // for(int x = 0; x < KEYPADX; x++)
  // {
  //   for(int y = 0; y < KEYPADY; y++)
  //   {
  //     keymap[x][y] = defaultKeymap[x][y];
  //   }
  // }
}

void setBrightness(u8 b)
{
  brightness = b;
  reset();
}


void setTouchSensitive(u8 s)
{
  touch_sensitive = s;
}

//Sysex get
void getDeviceInfo()
{
  //TODO
}

void getModuleCount()
{
  //TODO
}

void getModuleInfo()
{

}

void getdevice_id()
{
  CompositeSerial.write((u8)0);
  CompositeSerial.write(14);
  CompositeSerial.write(3);
  CompositeSerial.write(device_id);
}


void getAllParameter()
{
  //TODO
}

void getColorPaletteRGB()
{
  CompositeSerial.write((u8)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(20);

  for(u8 i = 0; i < sizeof(palette[3]); i++)
  {
    CompositeSerial.write(i);
    CompositeSerial.write(palette[i] && 0xFF0000);
    CompositeSerial.write(palette[i] && 0xFF00);
    CompositeSerial.write(palette[i] && 0xFF);
  }
  CompositeSerial.write(255);
}

void getColorPaletteWRGB()
{
  CompositeSerial.write((u8)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(21);

  for(u8 i = 0; i < sizeof(palette[3]); i++)
  {
    CompositeSerial.write(i);
    CompositeSerial.write(palette[i] && 0xFF000000);
    CompositeSerial.write(palette[i] && 0xFF0000);
    CompositeSerial.write(palette[i] && 0xFF00);
    CompositeSerial.write(palette[i] && 0xFF);
  }
  CompositeSerial.write(255);
}

void getGammaState()
{
  CompositeSerial.write((u8)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(24);
}

void getCustomKeymap()
{
  CompositeSerial.write((u8)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(25);
}

void getBrightness()
{
  CompositeSerial.write((u8)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(25);
  CompositeSerial.write(brightness);
}

void getTouchSensitive()
{
  CompositeSerial.write((u8)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(31);
  CompositeSerial.write(touch_sensitive);
}

//Math
u8 wrgbToHEX(u8 w, u8 r, u8 g, u8 b)
{
  return w * 0x10000000 + r * 0x10000 + g * 0x100 + b;
}

u8 xyToIndex(u8 x, u8 y)
{

  switch (rotation)
  {
    case 1: //90
    return (KEYPADY - y - 1) + x * KEYPADX;
    case 2: //180
    return (KEYPADX - x - 1) + (KEYPADY - y - 1) * KEYPADY;
    case 3: //270
    return y + (KEYPADX - x - 1) * KEYPADX;
    default:
    return x + y * KEYPADX;
  }
}

// XY indexToXY(u8 index)
// {
//   XY xy;
//   xy.x = index%KEYPADX;
//   xy.y = index/KEYPADX;
//   return xy;
// }

u8 indexRotation(int index)
{
  // XY xy = indexToXY(index);
  if(index < NUM_LEDS)
  {
    return xyToIndex(index % KEYPADX, index / KEYPADX);
  }
  else if(index >= NUM_LEDS && index < NUM_TOTAL_LEDS)
  {
    return bottomLEDrotation(index);
  }
  return index;
}

u8 bottomLEDrotation(int index)
{
  switch (rotation)
  {
    case 1: //90
    if(index >= NUM_BOTTOM_LEDS / 4 * 3 - 1)
    {
      return index - NUM_BOTTOM_LEDS / 4 * 3;
    }
    return index + NUM_BOTTOM_LEDS / 4 * 1;
    case 2: //180
    if(index >= NUM_BOTTOM_LEDS / 4 * 2 - 1)
    {
      return index - NUM_BOTTOM_LEDS / 4 * 2;
    }
    return index + NUM_BOTTOM_LEDS / 4 * 2;
    case 3: //270
    if(index >= NUM_BOTTOM_LEDS / 4 * 1 - 1)
    {
      return index - NUM_BOTTOM_LEDS / 4 * 1;
    }
    return index + NUM_BOTTOM_LEDS / 4 * 3;
    default:
    return index;
  }
}
