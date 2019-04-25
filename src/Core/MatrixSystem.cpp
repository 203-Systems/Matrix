#include "MatrixSystem.h"

EEPROMClass EEPROM_USER;
EEPROMClass EEPROM_PALETTE;
EEPROMClass EEPROM_SYS;

extern LED LED;
extern KeyPad KeyPad;
extern MIDI Midi;

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
  USBComposite.setSerialString(getDeviceIDString());

  Midi.registerComponent();

  #ifdef DEBUG
  CompositeSerial.registerComponent();
  #endif
  
  USBComposite.begin();

}

void setupHardware()
{
  LED.init();
  KeyPad.init();
}

void bootDevice()
{

}


//Sysex set
void reset()
{
  nvic_sys_reset();
}

// void setDeviceID()
// {
//   setDeviceID(CompositeSerial.read());
// }

void setDeviceID(u8 id)
{
  EEPROM_USER.write(E_DEVICE_ID, id);
  device_id = id;
}



void enterBootloader()
{
  bkp_init();
  bkp_enable_writes();
  bkp_write(10, 0x424C);
  bkp_disable_writes();
  reset();
}

void resetDevice()
{
  formatEEPROM();
  reset();
}

void formatEEPROM()
{
  // #ifdef DEBUG
  // SerialComposite.print("EEPROM Format info :")
  EEPROM_USER.format();
  EEPROM_PALETTE.format();
}

void setgamma(bool g)
{
  gamma_enable = g;
  EEPROM_USER.write(E_GAMMA_ENABLE,g);
}

void nextBrightnessState()
{
  for(u8 i = 0; i < sizeof(brightness_level); i++)  //
  {
    if(brightness_level[i] > brightness)
    {
      setBrightness(brightness_level[i]);
      return;
    }
  }
  setBrightness(brightness_level[0]);
}

void setBrightness(u8 b)
{
  EEPROM_USER.write(E_BRIGHTNESS, b);
  brightness = b;
  LED.setBrightness(brightness);
}

void setCurrentKeyMap(u8 m)
{
  EEPROM_USER.write(E_CURRENT_KEYMAP, m);
  current_keymap = m;
}

void setUnipadMode(bool u)
{
  EEPROM_USER.write(E_UNIPAD_MODE, u);
  unipad_mode = u;
}
void setFnHold(bool h)
{
  EEPROM_USER.write(E_FN_HOLD, h);
  fn_hold = h;
}

void setLedCorrection(u32 c)
{
    EEPROM_USER.write(E_COLOUR_CORRECTION_1, c >> 16);
    EEPROM_USER.write(E_COLOUR_CORRECTION_2, c & 0xFFFF);
    LED.setColourCorrection(c);
    led_color_correction = c;
    #ifdef DEBUG
    CompositeSerial.print("Set Colour Correction ");CompositeSerial.println(c);
    #endif
}
//Sysex get
// void getDeviceInfo()
// {
//   //TODO
// }
//
// void getModuleCount()
// {
//   //TODO
// }
//
// void getModuleInfo()
// {
//
// }
//
// void getDeviceID()
// {
//   CompositeSerial.write((u8)0);
//   CompositeSerial.write(14);
//   CompositeSerial.write(3);
//   CompositeSerial.write(device_id);
// }
//
//
// void getAllParameter()
// {
//   //TODO
// }
//
// void getPaletteRGB()
// {
//   CompositeSerial.write((u8)(0));
//   CompositeSerial.write(14);
//   CompositeSerial.write(20);
//
//   for(u8 i = 0; i < sizeof(palette[2]); i++)
//   {
//     CompositeSerial.write(i);
//     CompositeSerial.write(palette[2][i] & 0xFF0000 >> 16);
//     CompositeSerial.write(palette[2][i] & 0xFF00 >> 8);
//     CompositeSerial.write(palette[2][i] & 0xFF);
//   }
//   CompositeSerial.write(255);
// }
//
// void getPaletteWRGB()
// {
//   CompositeSerial.write((u8)(0));
//   CompositeSerial.write(14);
//   CompositeSerial.write(21);
//
//   for(u8 i = 0; i < sizeof(palette[2]); i++)
//   {
//     CompositeSerial.write(i);
//     CompositeSerial.write(palette[2][i] & 0xFF000000 >> 24);
//     CompositeSerial.write(palette[2][i] & 0xFF0000 >> 16);
//     CompositeSerial.write(palette[2][i] & 0xFF00 >> 8);
//     CompositeSerial.write(palette[2][i] & 0xFF);
//   }
//   CompositeSerial.write(255);
// }
//
// void getgammaState()
// {
//   CompositeSerial.write((u8)(0));
//   CompositeSerial.write(14);
//   CompositeSerial.write(24);
// }
//
// void getCustomKeymap()
// {
//   CompositeSerial.write((u8)(0));
//   CompositeSerial.write(14);
//   CompositeSerial.write(25);
// }
//
// void getBrightness()
// {
//   CompositeSerial.write((u8)(0));
//   CompositeSerial.write(14);
//   CompositeSerial.write(25);
//   CompositeSerial.write(brightness);
// }

// void getTouchSensitive()
// {
//   CompositeSerial.write((u8)(0));
//   CompositeSerial.write(14);
//   CompositeSerial.write(31);
//   CompositeSerial.write(touch_sensitive);
// }

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
  LED.rotationCW(r);
}

void setRotation(u8 r)
{
  #ifdef DEBUG
  CompositeSerial.print("Set Rotation: ");
  CompositeSerial.println(EEPROM_USER.write(2, r));
  #else
  EEPROM_USER.write(E_ROTATION, r);
  #endif
  //rotation = EEPROM_USER.read(2);
  rotation = r;
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

  return x + y * XSIZE;
}

u8 indexToXY(u8 index)
{
  return (index % XSIZE) * 0x10 + (index / XSIZE);
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

XY xytoxy(u8 xy)
{
  XY nxy;
  nxy.x = (xy & 0xF0) >> 4;
  nxy.y = xy & 0x0F;
  return nxy;
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

u8 xyRotation(u8 xy, u8 r)
{
  u8 x = (xy & 0xF0) >> 4;
  u8 y = xy & 0x0F;
  u8 xr;
  u8 yr;
  switch(r)
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

u8 xyReverseRotation(u8 xy, u8 r)
{
  u8 x = (xy & 0xF0) >> 4;
  u8 y = xy & 0x0F;
  u8 xr;
  u8 yr;
  switch(r)
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

u32 toBrightness(u32 hex, float f)
{
  u8 w = (((hex & 0xFF000000) >> 24) * f);
  u8 r = (((hex & 0x00FF0000) >> 16) * f);
  u8 g = (((hex & 0x0000FF00) >> 8) * f);
  u8 b = ((hex & 0x000000FF) * f);

  return w * 0x1000000 + r * 0x10000 + g * 0x100 + b;
}


void recordReportCode(u8 code)
{
  #ifdef DEBUG
  CompositeSerial.print("Code loged N");
  CompositeSerial.print(available_report_code);
  CompositeSerial.print(" ");
  CompositeSerial.println(code);
  #endif
  report_code[available_report_code] = code;
  available_report_code ++;
  if(available_report_code ==  10)
    available_report_code = 0;
}
