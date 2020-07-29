#include "EEPROM.h"

extern EEPROMClass EEPROM_USER;
extern EEPROMClass EEPROM_PALETTE;
extern EEPROMClass EEPROM_SYS;

void setupEEPROM()
{
  EEPROM_USER.init(eeprom_user_adds_0, eeprom_user_adds_1, eeprom_pagesize);
  EEPROM_PALETTE.init(eeprom_palette_adds_0, eeprom_palette_adds_1, eeprom_pagesize);
  EEPROM_SYS.init(eeprom_sys_adds_0, eeprom_sys_adds_1, eeprom_pagesize);
}

void variableLoad()
{
  if(EEPROM_USER.read(E_INIT) == 0x00CB)
  {
    saveAllSetting();
    return;
  }

  if(EEPROM_USER.read(E_INIT) != 0x0203)
  {
    initEEPROM();
    return;
  }

  if(EEPROM_USER.read(E_EEPROMVERSION) > EEPROMVERSION)
  {
    initEEPROM();
    return;
  }

  switch(EEPROM_USER.read(E_EEPROMVERSION))
  {
    case 0: //0 > 1
      EEPROM_USER.write(E_DESATURATED_MODE, desaturated_mode);
    case EEPROMVERSION:
      loadSetting();
      loadPalette();
      //loadKeyMap();
      break;
    default:
      initEEPROM();
  }
}

void loadSetting()
{
  device_id = EEPROM_USER.read(E_DEVICE_ID);
  rotation = EEPROM_USER.read(E_ROTATION);
  brightness = EEPROM_USER.read(E_BRIGHTNESS);
  fps = EEPROM_USER.read(E_FPS);
  gamma_enable = EEPROM_USER.read(E_GAMMA_ENABLE);
  midi_enable = EEPROM_USER.read(E_MIDI_ENABLE);
  m2p_enable = EEPROM_USER.read(E_M2P_ENABLE);
  midi_return = EEPROM_USER.read(E_RETURN_ENABLE);
  unipad_mode = EEPROM_USER.read(E_UNIPAD_MODE);
  bootAnimationSelector = EEPROM_USER.read(E_BOOTANIMATION);
  debug_mode = EEPROM_USER.read(E_DEBUG_ENABLE);
  current_keymap = EEPROM_USER.read(E_CURRENT_KEYMAP);
  led_color_correction = (EEPROM_USER.read(E_color_CORRECTION_1) << 16) + EEPROM_USER.read(E_color_CORRECTION_2);
  led_color_temperture = (EEPROM_USER.read(E_color_TEMPERTURE_1) << 16) + EEPROM_USER.read(E_color_TEMPERTURE_2);
  fn_hold = EEPROM_USER.read(E_FN_HOLD);
  stfu = EEPROM_USER.read(E_STFU);
  desaturated_mode = EEPROM_USER.read(E_DESATURATED_MODE);
  pro_input_mode = EEPROM_USER.read(E_PRO_INPUT_MODE);
}

// void loadKeyMap()
// {
//
// }

void loadPalette()
{
  memcpy(palette,pre_compilled_palette,768);
  for(u8 p = 0; p < 2; p++)
  {
    for(u8 i = 0; i < 128; i++)
    {
      palette[p+2][i] = readColorFromEEPROM(p, i);
    }
  }
}

CRGB readColorFromEEPROM(u8 palette, u8 index) 
{
  //w = EEPROM_PALETTE.read((palette * 256) + 2 * index) >> 8;
  u8 r = EEPROM_PALETTE.read((palette * 256) + 2 * index) & 0xFF;
  u8 g = EEPROM_PALETTE.read((palette * 256) + 2 * index + 1) >> 8;
  u8 b = EEPROM_PALETTE.read((palette * 256) + 2 * index + 1) & 0xFF;
    #ifdef DEBUG
      CompositeSerial.print("Read Palette from EEPROM ");
      CompositeSerial.print(palette);
      CompositeSerial.print(" ");
      CompositeSerial.print(index);
      CompositeSerial.print(" ");
      CompositeSerial.print(r);
      CompositeSerial.print(" ");
      CompositeSerial.print(g);
      CompositeSerial.print(" ");
      CompositeSerial.println(b);
  #endif
  return CRGB(r, g, b);
}

void saveColorToEEPROM(u8 palette, u8 index, CRGB color) 
{
  EEPROM_PALETTE.write((palette * 256) + 2 * index, /*(color.w << 8) + */ color.r);
  EEPROM_PALETTE.write((palette * 256) + 2 * index + 1, (color.g << 8) + color.b);
  #ifdef DEBUG
    CompositeSerial.print("Save Palette to EEPROM ");
    CompositeSerial.print(palette);
    CompositeSerial.print(" ");
    CompositeSerial.print(index);
    CompositeSerial.print(" ");
    CompositeSerial.print(color.r);
    CompositeSerial.print(" ");
    CompositeSerial.print(color.g);
    CompositeSerial.print(" ");
    CompositeSerial.println(color.b);
  #endif
}

void initEEPROM()
{
  formatEEPROM();
  saveAllSetting();
}

void formatEEPROM()
{
  EEPROM_USER.format();
  EEPROM_PALETTE.format();
  EEPROM_USER.write(E_INIT, 0x00CB);
}

void saveAllSetting()
{
  EEPROM_USER.write(E_INIT, 0x0203);
  EEPROM_USER.write(E_EEPROMVERSION, EEPROMVERSION);
  EEPROM_USER.write(E_DEVICE_ID, device_id);
  EEPROM_USER.write(E_ROTATION, rotation);
  EEPROM_USER.write(E_BRIGHTNESS, brightness);
  EEPROM_USER.write(E_FPS, fps);
  EEPROM_USER.write(E_GAMMA_ENABLE, (u8)gamma_enable);
  EEPROM_USER.write(E_MIDI_ENABLE, (u8)midi_enable);
  EEPROM_USER.write(E_M2P_ENABLE, (u8)m2p_enable);
  EEPROM_USER.write(E_RETURN_ENABLE, (u8)midi_return);
  EEPROM_USER.write(E_UNIPAD_MODE, (u8)unipad_mode);
  EEPROM_USER.write(E_BOOTANIMATION, bootAnimationSelector);
  EEPROM_USER.write(E_DEBUG_ENABLE, (u8)debug_mode);
  EEPROM_USER.write(E_CURRENT_KEYMAP, current_keymap);
  EEPROM_USER.write(E_color_CORRECTION_1, led_color_correction >> 8);
  EEPROM_USER.write(E_color_CORRECTION_2, led_color_correction & 0xFFFF);
  EEPROM_USER.write(E_FN_HOLD, fn_hold);
  EEPROM_USER.write(E_STFU, stfu);
  EEPROM_USER.write(E_DESATURATED_MODE, desaturated_mode);
  EEPROM_USER.write(E_PRO_INPUT_MODE, pro_input_mode);
}

// void saveKeyMap()
// {
//   for(u8 p = 0; p < 3; p++)
//   {
//     for(u8 y = 0; y < 8; y++)
//     {
//       for(u8 x = 0; x < 4; x++)
//       {
//         EEPROM_USER.write(E_CUSTOM_KEYMAP_1 + 128*p + y * 4 + x, keymap[2+p][y][x*2]*0x100 + keymap[2+p][y][x*2+1]);
//       }
//     }
//
//     for(u8 y = 0; y < 2; y++)
//     {
//       for(u8 x = 0; x < 4; x++)
//       {
//         EEPROM_USER.write(E_CUSTOM_FN_KEYMAP_1 + 128*p + y*4 + x, fn_keymap[2+p][y][x*2]*0x100 + fn_keymap[2+p][y][x*2+1]);
//       }
//     }
//
//     for(u8 i = 0; i < 18; i++)
//     {
//     EEPROM_USER.write(E_CUSTOM_BOTTOM_KEYMAP_1 + 128*p + i, bottom_led_map[2+p][i*2] *0x100 + bottom_led_map[2+p][i*2 + 1]);
//     }
//
//     EEPROM_USER.write(E_CUSTOM_KEYMAP_1_color + 128*p, (keymap_color[2+p] & 0xFFFF0000) >> 16);
//     EEPROM_USER.write(E_CUSTOM_KEYMAP_1_color + 128*p + 1, keymap_color[2+p] & 0xFFFF);
//
//     for(u8 y = 0; y < 2; y++)
//     {
//       for(u8 x = 0; x < 8; x++)
//       {
//         EEPROM_USER.write(E_CUSTOM_KEYMAP_1_IDLE + 128*p + y*16 + x, (fn_keymap_idle_color[2+p][y][x*2] & 0xFFFF0000) >> 16);
//         EEPROM_USER.write(E_CUSTOM_KEYMAP_1_IDLE + 128*p + y*16 + x + 1, fn_keymap_idle_color[2+p][y][x*2] & 0xFFFF);
//       }
//     }
//
//     for(u8 y = 0; y < 2; y++)
//     {
//       for(u8 x = 0; x < 8; x++)
//       {
//         EEPROM_USER.write(E_CUSTOM_KEYMAP_1_ACTIVE + 128*p + y*16 + x, (fn_keymap_idle_color[2+p][y][x*2] & 0xFFFF0000) >> 16);
//         EEPROM_USER.write(E_CUSTOM_KEYMAP_1_ACTIVE + 128*p + y*16 + x + 1, fn_keymap_idle_color[2+p][y][x*2] & 0xFFFF);
//       }
//     }
//   }
// }
//
// void savePalette()
// {
//   for(u8 p = 0; p < 2; p++)
//   {
//     for(u8 i = 0; i <128; i++)
//     {
//       EEPROM_PALETTE.write(i * 2 + 256 * p, (palette[p+2][i] & 0xFFFF0000) >> 16);
//       EEPROM_PALETTE.write(i * 2 + 256 * p + 1, palette[p+2][i] & 0x0000FFFF);
//     }
//   }
// }