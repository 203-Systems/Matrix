#include "MatrixSystem.h"

void initializeEEPROM()
{
  EEPROM.PageBase0 = 0x801F000;
  EEPROM.PageBase1 = 0x801F400;
  EEPROM.PageSize  = 0x400;
}

void variableLoad()
{
  if(EEPROM.read(0) & B00000001 > 0)
  loadPalette();

  if(EEPROM.read(0) & B00000010 > 0)
  loadKeymap();

  //EEPROM.read(0x00) & b00000100;

  gamma_enable = EEPROM.read(0) & B00001000 > 0;
  powercord_enable = EEPROM.read(0) & B00010000 >  0;
  midi_enable = EEPROM.read(0) & B00100000 > 0;
  m2p_enable = EEPROM.read(0) & B01000000 > 0;
  massage_return = EEPROM.read(0) & B10000000 > 0;

  rotation = EEPROM.read(579);
  device_id = EEPROM.read(580);

  if(EEPROM.read(581) > 0)
  brightness = EEPROM.read(581);

  if(EEPROM.read(582) > 0)
  touch_sensitive = EEPROM.read(582);
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

void resetDevice()
{
  formatEEPROM();
  EEPROM.write(0x00, B01100000); //customPalette,customKeymap,customtouchbar,gamma,powercord,MIDI,M2P
}

void formatEEPROM()
{
  EEPROM.format();
}

void loadPalette()
{
  for(int i = 0; i < 128; i++)
  {
    palette[2][i] =
    EEPROM.read(i * 4 + 1)*0x1000000 + //W
    EEPROM.read(i * 4 + 2)*0x10000 + //R
    EEPROM.read(i * 4 + 3)*0x100 + //G
    EEPROM.read(i * 4 + 4); //B
  }
}

void loadKeymap()
{
  for(int y = 0; y < KEYPADY; y++)
  {
    for(int x = 0; x < KEYPADX; x++)
    {
      keymap[y][x] = EEPROM.read(y * KEYPADX + x + 514);
    }
  }
}

void updatePaletteRGB()
{
  if(CompositeSerial.peek() < 128)
  {
    u8 colour = CompositeSerial.read();
    EEPROM.write(colour * 4, 0x00);
    EEPROM.write(colour * 4 + 1, CompositeSerial.read());
    EEPROM.write(colour * 4 + 2, CompositeSerial.read());
    EEPROM.write(colour * 4 + 3, CompositeSerial.read());

    palette[2][colour] =
    EEPROM.read(colour * 4) * 0x1000000 +
    EEPROM.read(colour * 4 + 1) * 0x10000 +
    EEPROM.read(colour * 4 + 2) * 0x100 +
    EEPROM.read(colour * 4 + 3);
  }
  else if(CompositeSerial.peek() == 255)
  {
    return;
  }
}

void updatePaletteWRGB()
{
  if(CompositeSerial.peek() < 128)
  {
    u8 colour = CompositeSerial.read();
    EEPROM.write(colour * 4, CompositeSerial.read());
    EEPROM.write(colour * 4 + 1, CompositeSerial.read());
    EEPROM.write(colour * 4 + 2, CompositeSerial.read());
    EEPROM.write(colour * 4 + 3, CompositeSerial.read());

    palette[2][colour] =
    EEPROM.read(colour * 4) * 0x1000000 +
    EEPROM.read(colour * 4 + 1) * 0x10000 +
    EEPROM.read(colour * 4 + 2) * 0x100 +
    EEPROM.read(colour * 4 + 3);
  }
  else if(CompositeSerial.peek() == 255)
  {
    return;
  }
}

void resetPalette()
{
  EEPROM.write(0, EEPROM.read(0) & B01111111);
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
    u8 x = CompositeSerial.read();
    u8 y = CompositeSerial.read();

    EEPROM.write(y * KEYPADX + x + 514, CompositeSerial.read());

    keymap[y][x] = EEPROM.read(y * KEYPADX + x + 514);
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
  EEPROM.write(581, b);
  brightness = b;
  reset();
}


void setTouchSensitive(u8 s)
{
  EEPROM.write(582, s);
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

void getPaletteRGB()
{
  CompositeSerial.write((u8)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(20);

  for(u8 i = 0; i < sizeof(palette[2]); i++)
  {
    CompositeSerial.write(i);
    CompositeSerial.write(palette[2][i] & 0xFF0000 >> 16);
    CompositeSerial.write(palette[2][i] & 0xFF00 >> 8);
    CompositeSerial.write(palette[2][i] & 0xFF);
  }
  CompositeSerial.write(255);
}

void getPaletteWRGB()
{
  CompositeSerial.write((u8)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(21);

  for(u8 i = 0; i < sizeof(palette[2]); i++)
  {
    CompositeSerial.write(i);
    CompositeSerial.write(palette[2][i] & 0xFF000000 >> 24);
    CompositeSerial.write(palette[2][i] & 0xFF0000 >> 16);
    CompositeSerial.write(palette[2][i] & 0xFF00 >> 8);
    CompositeSerial.write(palette[2][i] & 0xFF);
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

//special
void nextBrightnessState()
{
  if(brightness >= 192) //Bright AF
  {
    setBrightness(32);
  }
  else if(brightness >= 160) //VeryBright
  {
    setBrightness(192);
  }
  else if(brightness >= 128) //Bright
  {
    setBrightness(160);
  }
  else if(brightness >= 96) //Normal
  {
    setBrightness(128);
  }
  else if(brightness >= 64) //Dim
  {
    setBrightness(96);
  }
  else if(brightness >= 32) //VeryDim
  {
    setBrightness(64);
  }
  else
  {
    setBrightness(32);
  }
}

void rotationCW(u8 r)
{
rotation += r;
if(rotation > 3)
  rotation %= 4;
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
