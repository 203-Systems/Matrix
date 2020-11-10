#include "MatrixSystem.h"

EEPROMClass EEPROM_USER;
EEPROMClass EEPROM_PALETTE;
EEPROMClass EEPROM_SYS;

extern LED LED;
extern KeyPad KeyPad;
extern MIDI Midi;
extern Touch Touch;
extern USBCompositeSerial CompositeSerial;

u8 cW = 255;
u8 cR = 255;
u8 cG = 255;
u8 cB = 255;

String device_name_with_ID;
String serial_number;

void setupUSB()
{
  USBComposite.clear();
  if (device_id != 0)
  {
    device_name_with_ID = (DEVICENAME + String(' ') + String(device_id));
    USBComposite.setProductString(device_name_with_ID.c_str());
    USBComposite.setVendorId(VID2);
    USBComposite.setProductId(PID2 + device_id);
  }
  else
  {
    USBComposite.setProductString(DEVICENAME);
    USBComposite.setVendorId(VID);
    USBComposite.setProductId(PID);
  }

  USBComposite.setManufacturerString(MAUNFACTURERNAME);
  //USBComposite.setSerialString(getDeviceSerialString().c_str());
  serial_number = getDeviceSerialString();
  USBComposite.setSerialString(serial_number.c_str());

  Midi.registerComponent();
  CompositeSerial.registerComponent();

  USBComposite.begin();
}

void setupHardware()
{
  LED.init();
  KeyPad.init();
  Touch.init();
}

void specialBoot()
{
  KeyPad.scan();
  if (KeyPad.checkXY(0, 5, true) && KeyPad.checkXY(1, 6, true) && KeyPad.checkXY(0, 7, true))
  {
    LED.setXYCRGB(0x33, 0xFF00FF, true);
    LED.setXYCRGB(0x34, 0xFF00FF, true);
    LED.setXYCRGB(0x43, 0xFF00FF, true);
    LED.setXYCRGB(0x44, 0xFF00FF, true);
    LED.update();
    formatEEPROM();
    return;
  }

  if (KeyPad.checkXY(1, 1, true) && KeyPad.checkXY(0, 0, true))
  {
    factoryTest();
    return;
  }

  if (KeyPad.checkXY(6, 6, true) && KeyPad.checkXY(7, 7, true))
  {
    setBrightness(16);
    return;
  }

  if (KeyPad.checkXY(7, 0, true) && KeyPad.checkXY(6, 1, true))
  {
    setBrightness(255);
    return;
  }
}

void factoryTest()
{
  LED.setBrightness(64);
  LED.fill(0);
  LED.update();

  while (KeyPad.fn.state != PRESSED)
  {
    if (ledTimer.tick(fps_micros))
    {
      if (KeyPad.scan())
      {
        for (int i = 0; i < MULTIPRESS; i++)
        {
          if (KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
          {
            LED.setXYCRGB(KeyPad.changelist[i], 0xFFFFFF, true);
          }
        }
        LED.update();
      }
    }
  }
  LED.fill(0);
  LED.update();
  while (KeyPad.fn.state != IDLE)
  {
    if (ledTimer.tick(fps_micros))
    {
      KeyPad.scan();
    }
  }

  while (KeyPad.fn.state != PRESSED)
  {
    if (ledTimer.tick(fps_micros))
    {
      KeyPad.scan();
      if (Touch.scan())
      {
        for (int i = 0; i < 16; i++)
        {
          CompositeSerial.print(Touch.rawInput[i]);
          CompositeSerial.print(" ");
          if (Touch.rawInput[i])
          {
            u8 x = (i % 4) * 2;
            u8 y = (i / 4) * 2;
            LED.setXYCRGB(xytoxy(x, y), 0x00FF00, true);
            LED.setXYCRGB(xytoxy(x, y + 1), 0x00FF00, true);
            LED.setXYCRGB(xytoxy(x + 1, y), 0x00FF00, true);
            LED.setXYCRGB(xytoxy(x + 1, y + 1), 0x00FF00, true);
          }
        }
        CompositeSerial.println();
        LED.update();
      }
    }
  }
  LED.fill(0);
  LED.update();
}

// void loadDeviceSerialNumber()
// {
//   u32 serial_num[3] = {DEVICE_SERIAL_1, DEVICE_SERIAL_2, DEVICE_SERIAL_3};
//   char char_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
//   u8 c = 0;
//   for(u8 i = 0; i < 3; i ++)
//   {
//     u32 current_byte = 0xF0000000;
//     for(s8 b = 7; b >= 0; b--)
//     {
//       serial_number[c] = char_table[(serial_num[i] & current_byte) >> 4*b];
//       current_byte = current_byte >> 4;
//       c++;
//     }
//   }
// }

String getDeviceSerialString()
{
  String serial;
  u32 serial_num[3] = {DEVICE_SERIAL_1, DEVICE_SERIAL_2, DEVICE_SERIAL_3};
  char char_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  for (u8 i = 0; i < 3; i++)
  {
    u32 current_byte = 0xF0000000;
    for (s8 b = 7; b >= 0; b--)
    {
      serial += char_table[(serial_num[i] & current_byte) >> 4 * b];
      current_byte = current_byte >> 4;
    }
  }
  return serial;
}

//Sysex set
void reboot()
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
  LED.fill(0, true);
  LED.setXYCRGB(0x32, 0xFF0000, true);
  LED.setXYCRGB(0x42, 0xFF0000, true);
  LED.setXYCRGB(0x23, 0xFF0000, true);
  LED.setXYCRGB(0x33, 0xFF0000, true);
  LED.setXYCRGB(0x43, 0xFF0000, true);
  LED.setXYCRGB(0x53, 0xFF0000, true);
  LED.setXYCRGB(0x34, 0xFF0000, true);
  LED.setXYCRGB(0x44, 0xFF0000, true);
  LED.setXYCRGB(0x35, 0xFF0000, true);
  LED.setXYCRGB(0x45, 0xFF0000, true);
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

void setupPalette()
{
  compileColorScaleTable();
  compilePalette();
}

void compileColorScaleTable()
{
  u8 scale[4] = {
      (led_color_correction & 0xFF000000) >> 24,
      (led_color_correction & 0xFF0000) >> 16,
      (led_color_correction & 0xFF00) >> 8,
      led_color_correction & 0xFF};

  for (u8 c = 0; c < 4; c++)
  {
    for (int i = 0; i < 256; i++)
    {
      color_correction_table[c][i] = scale8_video(i, scale[c]);
    }
  }

  for (int i = 0; i < 256; i++)
  {
    color_desaturate_table[i] = scale8_video(i, desaturate_rate);
  }

  for (int i = 0; i < 256; i++)
  {
    low_brightness_table[i] = scale8_video(i, LOW_STATE_BRIGHTNESS);
  }
}

void compilePalette()
{
  for (u8 p = 0; p < 4; p++)
  {
    for (u8 i = 0; i < 128; i++)
    {
      palette[p][i] = compileColor(palette[p][i]);
    }
  }
}

void setgamma(bool g)
{
  gamma_enable = g;
  EEPROM_USER.write(E_GAMMA_ENABLE, g);
}

void nextBrightnessState()
{
  for (u8 i = 0; i < sizeof(brightness_level); i++) //
  {
    if (brightness_level[i] > brightness)
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

// void setTouchThreshold(u16 t)
// {
//   EEPROM_USER.write(E_TOUCH_THRESHOLD, t);
//   touch_threshold = t;
// }

void setColorCorrection(u32 c, bool dont_write)
{
  if (!dont_write)
  {
    EEPROM_USER.write(E_color_CORRECTION_1, c >> 16);
    EEPROM_USER.write(E_color_CORRECTION_2, c & 0xFFFF);
  }
  //LED.setColorCorrection(c);
  led_color_correction = c;
  // cW = (c & 0xFF000000) >> 24;
  // cR = (c & 0xFF0000) >> 16;
  // cG = (c & 0xFF00) >> 8;
  // cB = c & 0xFF;
  setupPalette();
#ifdef DEBUG
  CompositeSerial.print("Set color Correction ");
  CompositeSerial.println(c);
#endif
}

void setSTFU(u16 v)
{
  stfu = v;
  EEPROM_USER.write(E_STFU, v);
}

void setDesaturatedMode(bool e)
{
  desaturated_mode = e;
  EEPROM_USER.write(E_DESATURATED_MODE, e);
  setupPalette();
}
void setProInputMode(bool e)
{
  pro_input_mode = e;
  EEPROM_USER.write(E_PRO_INPUT_MODE, e);
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
  if (r > 3)
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
  CompositeSerial.println(EEPROM_USER.write(E_ROTATION, r));
#else
  EEPROM_USER.write(E_ROTATION, r);
#endif
  //rotation = EEPROM_USER.read(2);
  rotation = r;
}

//Math
u32 wrgbToHEX(u8 w, u8 r, u8 g, u8 b)
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
  if (index < NUM_LEDS)
  {
    return xyToIndex(indexToXY(index));
  }
  else if (index >= NUM_LEDS && index < NUM_TOTAL_LEDS)
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
    if (index >= NUM_BOTTOM_LEDS / 4 * 3 - 1)
    {
      return index - NUM_BOTTOM_LEDS / 4 * 3;
    }
    return index + NUM_BOTTOM_LEDS / 4 * 1;
  case 2: //180
    if (index >= NUM_BOTTOM_LEDS / 4 * 2 - 1)
    {
      return index - NUM_BOTTOM_LEDS / 4 * 2;
    }
    return index + NUM_BOTTOM_LEDS / 4 * 2;
  case 3: //270
    if (index >= NUM_BOTTOM_LEDS / 4 * 1 - 1)
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
  switch (rotation)
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
  switch (r)
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
  switch (rotation)
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
  switch (r)
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

u8 touchbarRotation(u8 id)
{
  switch (rotation)
  {
  case 0:
  case 1:
    return id;
  case 2:
  case 3:
    return 7 - id;
  }
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
  available_report_code++;
  if (available_report_code == 10)
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

void remap_7bitx3(u8 *p1, u8 *p2, u8 *p3, u8 *p4)
{
  *p1 = (*p1 << 1) + (*p2 >> 6);
  *p2 = (*p2 << 2) + (*p3 >> 5);
  *p3 = (*p3 << 3) + (*p4 >> 4);
  return;
}

void remap_7bitx4(u8 *p1, u8 *p2, u8 *p3, u8 *p4, u8 *p5)
{
  *p1 = (*p1 << 1) + (*p2 >> 6);
  *p2 = (*p2 << 2) + (*p3 >> 5);
  *p3 = (*p3 << 3) + (*p4 >> 4);
  *p4 = (*p4 << 4) + (*p5 >> 3);
  return;
}