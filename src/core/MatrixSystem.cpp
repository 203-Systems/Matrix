#include "MatrixSystem.h"


void setupUSB()
{

  if(device_id != 0)
  {
    USBComposite.setProductString((DEVICENAME + String(' ') + String(device_id)).c_str());
    USBComposite.setVendorId(VID2);
    USBComposite.setProductId(PID2+device_id);
  }
  else
  {
    USBComposite.setProductString(DEVICENAME);
    USBComposite.setVendorId(VID);
    USBComposite.setProductId(PID);
  }

  USBComposite.setManufacturerString(MAUNFACTURERNAME);
  //USBComposite.setProductString(DEVICENAME);
  USBComposite.setSerialString(SERIALSTRING);

  USBmidi.registerComponent();
  CompositeSerial.registerComponent();
  USBComposite.begin();

}

void setupHardware()
{
  FastLED.setBrightness(brightness);
  setupEEPROM();
}

void setupEEPROM()
{
  EEPROM.PageBase0 = 0x802F000;
  EEPROM.PageBase1 = 0x802F800;
  EEPROM.PageSize  = 0x800;
  EEPROM.init();
}

void variableLoad()
{
  if(EEPROM.read(0) == 0xFFFF)
  {
    initEEPROM();
    return;
  }

  device_id = EEPROM.read(1);
  rotation = EEPROM.read(2);
  brightness = EEPROM.read(3);
  gamma_enable = EEPROM.read(4);
  midi_enable = EEPROM.read(5);
  m2p_enable = EEPROM.read(6);
  powercord_enable = EEPROM.read(7);
  massage_return = EEPROM.read(8);

  if(EEPROM.read(9))
  loadPalette();

  if(EEPROM.read(518))
  loadKeymap();

  touch_sensitive = EEPROM.read(582);
  // if(EEPROM.read(583))
  // loadTouchmap();
}

void initEEPROM()
{
  EEPROM.write(0, 0);
  EEPROM.write(1, device_id);
  EEPROM.write(2, rotation);
  EEPROM.write(3, brightness);
  EEPROM.write(4, (u8)gamma_enable);
  EEPROM.write(5, (u8)midi_enable);
  EEPROM.write(6, (u8)m2p_enable);
  EEPROM.write(7, (u8)powercord_enable);
  EEPROM.write(8, (u8)massage_return);
  EEPROM.write(9, false);

  for(int i = 10; i < 518; i++)
  {
    EEPROM.write(i, 0xFF);
  }

  EEPROM.write(518, false);

  for(int i = 0; i < 64; i++)
  {
    EEPROM.write(i + 519, 0);
  }

  EEPROM.write(583, touch_sensitive);
  EEPROM.write(584, false);
  EEPROM.write(585, 0);
}


//Sysex set
void reset()
{
  nvic_sys_reset();
  // pinMode(RESET_PIN, OUTPUT);
  // digitalWrite(RESET_PIN, LOW);

}

void setDeviceID()
{
  setDeviceID(CompositeSerial.read());
}

void setDeviceID(u8 id)
{
  CompositeSerial.print("Write Device ID into EEPROM: ");
  CompositeSerial.println(EEPROM.write(1, id));
  device_id = EEPROM.read(1);
}



void enterBootloader()
{
  (*(vu32*)0x4002101C) = 0;
  (*(vu32*)0x40007000) &=~ (1 << 8);
  (*(vu16*)0x40006C28) = 0x424C;
  (*(vu32*)0x40007000) |= (1 << 8);
  reset();
}

void resetDevice()
{
  formatEEPROM();
  reset();
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
    EEPROM.read(i * 4 + 10)*0x1000000 + //W
    EEPROM.read(i * 4 + 11)*0x10000 + //R
    EEPROM.read(i * 4 + 12)*0x100 + //G
    EEPROM.read(i * 4 + 13); //B
  }
}

void loadKeymap()
{
  for(int y = 0; y < KEYPADY; y++)
  {
    for(int x = 0; x < KEYPADX; x++)
    {
      keymap[y][x] = EEPROM.read(y * KEYPADX + x + 519);
    }
  }
}

void updatePaletteRGB()
{
  EEPROM.write(9, true);
  if(CompositeSerial.peek() < 128)
  {
    u8 colour = CompositeSerial.read();
    EEPROM.write(colour * 4 + 10, 0x00);
    EEPROM.write(colour * 4 + 11, CompositeSerial.read());
    EEPROM.write(colour * 4 + 12, CompositeSerial.read());
    EEPROM.write(colour * 4 + 13, CompositeSerial.read());

    palette[2][colour] =
    EEPROM.read(colour * 4 + 10) * 0x1000000 +
    EEPROM.read(colour * 4 + 11) * 0x10000 +
    EEPROM.read(colour * 4 + 12) * 0x100 +
    EEPROM.read(colour * 4 + 13);
  }
  else if(CompositeSerial.peek() == 255)
  {
    return;
  }
}

void updatePaletteWRGB()
{
  EEPROM.write(9, true);
  if(CompositeSerial.peek() < 128)
  {
    u8 colour = CompositeSerial.read();
    EEPROM.write(colour * 4 + 10, CompositeSerial.read());
    EEPROM.write(colour * 4 + 11, CompositeSerial.read());
    EEPROM.write(colour * 4 + 12, CompositeSerial.read());
    EEPROM.write(colour * 4 + 13, CompositeSerial.read());

    palette[2][colour] =
    EEPROM.read(colour * 4 + 10) * 0x1000000 +
    EEPROM.read(colour * 4 + 11) * 0x10000 +
    EEPROM.read(colour * 4 + 12) * 0x100 +
    EEPROM.read(colour * 4 + 13);
  }
  else if(CompositeSerial.peek() == 255)
  {
    return;
  }
}

void resetPalette()
{
  EEPROM.write(9, false);
  // for(int i = 0; i < sizeof(palette[0]); i++)
  // {
  //   palette[2][i] = palette[0][i];
  // }
}

void setgamma(bool g)
{

  gamma_enable = g;
}

void updateCustomKeymap()
{
  while(CompositeSerial.peek() != 255)
  {
    u8 x = CompositeSerial.read();
    u8 y = CompositeSerial.read();

    EEPROM.write(y * KEYPADX + x + 519, CompositeSerial.read());

    keymap[y][x] = EEPROM.read(y * KEYPADX + x + 519);
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
  EEPROM.write(3, b);
  brightness = b;
}


void setTouchSensitive(u8 s)
{
  EEPROM.write(3, s);
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

void getDeviceID()
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

void getgammaState()
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

void rotationCW(u8 r)
{
  r += rotation;
  if(r > 3)
  {
    setRotation(r % 4);
  }
  else
  {
    setRotation(r);
  }
}

void setRotation(u8 r)
{
  CompositeSerial.print("Write Rotation into EEPROM: ");
  CompositeSerial.println(EEPROM.write(2, r));
  rotation = EEPROM.read(2);
}

//Math
u8 wrgbToHEX(u8 w, u8 r, u8 g, u8 b)
{
  return w * 0x10000000 + r * 0x10000 + g * 0x100 + b;
}

u8 xyToIndex(u8 xy)
{
  u8 xyr = xyReverseRotation(xy);
  u8 x = (xyr & 0xF0) >> 4;
  u8 y = xyr & 0x0F;

  return x + y * KEYPADX;
}

u8 indexToXY(u8 index)
{
  return (index % KEYPADX) * 0x10 + (index / KEYPADX);
}

u8 indexRotation(int index)
{
  // XY xy = indexToXY(index);
  if(index < NUM_LEDS)
  {
    return xyToIndex(indexToXY(index));
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

u8 xytoxy(u8 x, u8 y)
{
  return x * 0x10 + y;
}

u8 xyRotation(u8 xy)
{
  u8 x = (xy & 0xF0) >> 4;
  u8 y = xy & 0x0F;
  u8 xr;
  u8 yr;
  switch(rotation)
  {
    case 1:
    xr = y;
    yr = 7 - x;
    break;
    case 2:
    xr = 7 - x;
    yr = 7 - y;
    break;
    case 3:
    xr = 7 - y;
    yr = x;
    break;
    default:
    xr = x;
    yr = y;
  }
  return xr * 0x10 + yr;
}

u8 xyReverseRotation(u8 xy)
{
  u8 x = (xy & 0xF0) >> 4;
  u8 y = xy & 0x0F;
  u8 xr;
  u8 yr;
  switch(rotation)
  {
    case 1:
    xr = 7 - y;
    yr = x;
    break;
    case 2:
    xr = 7 - x;
    yr = 7 - y;
    break;
    case 3:
    xr = y;
    yr = 7 - x;
    break;
    default:
    xr = x;
    yr = y;
  }
  return xr * 0x10 + yr;
}
