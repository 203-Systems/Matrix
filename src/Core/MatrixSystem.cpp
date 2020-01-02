#include "MatrixSystem.h"

EEPROMClass EEPROM_USER;
EEPROMClass EEPROM_PALETTE;
EEPROMClass EEPROM_SYS;

extern LED LED;
extern KeyPad KeyPad;
extern MIDI Midi;
//extern ADCTouch TouchBar;

u8 cW = 255;
u8 cR = 255;
u8 cG = 255;
u8 cB = 255;

void setupUSB()
{
  USBComposite.clear();
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
  USBComposite.setSerialString(getDeviceIDString());

  Midi.registerComponent();
  // Midi.setRXPacketSize(256);
  // Midi.setTXPacketSize(64);

  CompositeSerial.registerComponent();

  USBComposite.begin();

}

void setupHardware()
{
  LED.init();
  KeyPad.init();
  //TouchBar.init();
  setColourCorrection(led_colour_correction, true);
  applyColourCorrectionToPalette();
}

void specialBoot()
{
  if (KeyPad.scan())
  {
    if(KeyPad.checkXY(0, 5, true) && KeyPad.checkXY(0, 6, true) && KeyPad.checkXY(0, 7, true))
    {
      formatEEPROM();
      LED.fill(0xFF00FF);
    }

    if(KeyPad.checkXY(1, 1, true) && KeyPad.checkXY(0, 0, true))
    {
      factoryTest();
    }

    if(KeyPad.checkXY(7, 0, true))
    {
      setBrightness(16);
    }

    if(KeyPad.checkXY(7, 0, true) && KeyPad.checkXY(6, 1, true))
    {
      setBrightness(255);
    }

  }
}

void factoryTest()
{
  LED.setBrightness(64);
  LED.fill(0);
  LED.update();

  while(KeyPad.fn.state != PRESSED)
  {
    if (mainTimer.tick(1000/fps))
    {
      if(KeyPad.scan())
      {
        for(int i = 0; i < MULTIPRESS; i++)
        {
          u8 x = xytox(KeyPad.changelist[i]);
          u8 y = xytoy(KeyPad.changelist[i]);
          if(KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
          {
            if(LED.readLED(KeyPad.changelist[i]))
            {
              LED.offXY(KeyPad.changelist[i], true);
            }
            else
            {
              LED.setXYHEX(KeyPad.changelist[i], 0xFFFFFF, true, true);
            }
          }
        }
        LED.update();
      }
    }
  }
}

//Sysex set
void reboot()
{
  bkp_init();
  bkp_enable_writes();
  bkp_write(10, 0x424D);
  bkp_disable_writes();
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
  LED.fill(0,true);
  LED.setXYHEX(0x32,0xFF0000, true);
  LED.setXYHEX(0x42,0xFF0000, true);
  LED.setXYHEX(0x23,0xFF0000, true);
  LED.setXYHEX(0x33,0xFF0000, true);
  LED.setXYHEX(0x43,0xFF0000, true);
  LED.setXYHEX(0x53,0xFF0000, true);
  LED.setXYHEX(0x34,0xFF0000, true);
  LED.setXYHEX(0x44,0xFF0000, true);
  LED.setXYHEX(0x35,0xFF0000, true);
  LED.setXYHEX(0x45,0xFF0000, true);
  LED.update();
  bkp_init();
  bkp_enable_writes();
  bkp_write(10, 0x424C);
  bkp_disable_writes();
  nvic_sys_reset();
}

void resetDevice()
{
  formatEEPROM();
  reboot();
}

void formatEEPROM()
{
  // #ifdef DEBUG
  // SerialComposite.print("EEPROM Format info :")
  EEPROM_USER.format();
  EEPROM_PALETTE.format();
}

void applyColourCorrectionToPalette()
{
  cW = (led_colour_correction & 0xFF000000) >> 24;
  cR = (led_colour_correction & 0xFF0000) >> 16;
  cG = (led_colour_correction & 0xFF00) >> 8;
  cB = led_colour_correction & 0xFF;
  for(u8 p = 0; p < 4; p++)
  {
    for(u8 i = 0; i < 128; i++)
    {
      palette[p][i] = applyColourCorrection(palette[p][i]);
    }
  }
}

u32 applyColourCorrection(u32 input)
{
  u8 pW = (input & 0xFF000000) >> 24;
  u8 pR = (input & 0xFF0000) >> 16;
  u8 pG = (input & 0xFF00) >> 8;
  u8 pB = input & 0xFF;
  pW = scale8_video(pW, cW);
  pR = scale8_video(pR, cR);
  pG = scale8_video(pG, cG);
  pB = scale8_video(pB, cB);
  return pW * 0x1000000 + pR * 0x10000 + pG * 0x100 + pB;
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

void setTouchThreshold(u16 t)
{
  EEPROM_USER.write(E_TOUCH_THRESHOLD, t);
  touch_threshold = t;
}

void setColourCorrection(u32 c, bool dont_write)
{
  if(!dont_write)
  {
  EEPROM_USER.write(E_COLOUR_CORRECTION_1, c >> 16);
  EEPROM_USER.write(E_COLOUR_CORRECTION_2, c & 0xFFFF);
  }
  //LED.setColourCorrection(c);
  led_colour_correction = c;
  cW = (c & 0xFF000000) >> 24;
  cR = (c & 0xFF0000) >> 16;
  cG = (c & 0xFF00) >> 8;
  cB = c & 0xFF;
  #ifdef DEBUG
  CompositeSerial.print("Set Colour Correction ");CompositeSerial.println(c);
  #endif
}

void setSTFU(u16 v)
{
  stfu = v;
  EEPROM_USER.write(E_STFU, v);
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
// void resetTouchBar()
// {
//   TouchBar.init();
// }


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

// XY xytoxy(u8 xy)
// {
//   XY nxy;
//   nxy.x = (xy & 0xF0) >> 4;
//   nxy.y = xy & 0x0F;
//   return nxy;
// }

u8 xytox(u8 xy)
{
  return (xy & 0xF0) >> 4;
}

u8 xytoy(u8 xy)
{
  return xy & 0x0F;
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

u8 touchbarRotate(u8 id)
{
  switch(rotation)
  {
    case 0:
    case 1:
    return id;
    case 2:
    case 3:
    return 7-id;
  }
}

u32 toBrightness(u32 hex, float f, bool on)
{
  if(on)
  return hex;
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

// float velocityCurve(float input)
// {
//   return input;
// }

u8 convert_6BitTo8Bit(u8 input)
{
  return map(input, 0, 63, 0, 255);
}

u8 convert_7BitTo8Bit(u8 input)
{
  return map(input, 0, 127, 0, 255);
}
