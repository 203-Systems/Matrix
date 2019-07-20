#include "EEPROM.h"

extern EEPROMClass EEPROM_USER;
extern EEPROMClass EEPROM_PALETTE;
extern EEPROMClass EEPROM_SYS;

void setupEEPROM()
{
  recordReportCode(EEPROM_USER.init(eeprom_user_adds_0, eeprom_user_adds_1, eeprom_pagesize));
  recordReportCode(EEPROM_PALETTE.init(eeprom_palette_adds_0, eeprom_palette_adds_1, eeprom_pagesize));
  recordReportCode(EEPROM_SYS.init(eeprom_sys_adds_0, eeprom_sys_adds_1, eeprom_pagesize));
}

void variableLoad()
{
  if(EEPROM_USER.read(E_INIT) != FWVERSION)
  {
    initEEPROM();
    return;
  }
  loadSetting();
  loadKeyMap();
  loadPalette();
}

void loadSetting()
{
  device_id = EEPROM_USER.read(E_DEVICE_ID);
  rotation =EEPROM_USER.read(E_ROTATION);
  brightness = EEPROM_USER.read(E_BRIGHTNESS);
  max_mAh = EEPROM_USER.read(E_MAX_MA);
  fps = EEPROM_USER.read(E_FPS);
  gamma_enable = EEPROM_USER.read(E_GAMMA_ENABLE);
  midi_enable = EEPROM_USER.read(E_MIDI_ENABLE);
  m2p_enable = EEPROM_USER.read(E_M2P_ENABLE);
  midi_return = EEPROM_USER.read(E_RETURN_ENABLE);
  unipad_mode = EEPROM_USER.read(E_UNIPAD_MODE);
  bootAnimationSelector = EEPROM_USER.read(E_BOOTANIMATION);
  debug_mode = EEPROM_USER.read(E_DEBUG_ENABLE);
  current_keymap = EEPROM_USER.read(E_CURRENT_KEYMAP);
  led_color_correction = (EEPROM_USER.read(E_COLOUR_CORRECTION_1) << 16) + EEPROM_USER.read(E_COLOUR_CORRECTION_2);
  led_color_temperture = (EEPROM_USER.read(E_COLOUR_TEMPERTURE_1) << 16) + EEPROM_USER.read(E_COLOUR_TEMPERTURE_2);
  fn_hold = EEPROM_USER.read(E_FN_HOLD);
  touch_threshold = EEPROM_USER.read(E_TOUCH_THRESHOLD);
}

void loadKeyMap()
{

}

void loadPalette()
{
  for(u8 p = 0; p < 2; p++)
  {
    for(u8 i = 0; i <128; i++)
    {
       palette[p+2][i] = EEPROM_PALETTE.read(i * 2 + 256 * p) * 0x10000 + EEPROM_PALETTE.read(i * 2 + 256 * p + 1);
    }
  }
}

void initEEPROM()
{
  EEPROM_USER.format();
  EEPROM_PALETTE.format();

  saveSetting();
  saveKeyMap();
  savePalette();
}

void saveSetting()
{
  EEPROM_USER.write(E_INIT, FWVERSION);
  EEPROM_USER.write(E_DEVICE_ID, device_id);
  EEPROM_USER.write(E_ROTATION, rotation);
  EEPROM_USER.write(E_BRIGHTNESS, brightness);
  EEPROM_USER.write(E_MAX_MA, max_mAh);
  EEPROM_USER.write(E_FPS, fps);
  EEPROM_USER.write(E_GAMMA_ENABLE, (u8)gamma_enable);
  EEPROM_USER.write(E_MIDI_ENABLE, (u8)midi_enable);
  EEPROM_USER.write(E_M2P_ENABLE, (u8)m2p_enable);
  EEPROM_USER.write(E_RETURN_ENABLE, (u8)midi_return);
  EEPROM_USER.write(E_UNIPAD_MODE, (u8)unipad_mode);
  EEPROM_USER.write(E_BOOTANIMATION, bootAnimationSelector);
  EEPROM_USER.write(E_DEBUG_ENABLE, (u8)debug_mode);
  EEPROM_USER.write(E_CURRENT_KEYMAP, current_keymap);
  EEPROM_USER.write(E_COLOUR_CORRECTION_1, led_color_correction >> 8);
  EEPROM_USER.write(E_COLOUR_CORRECTION_2, led_color_correction & 0xFFFF);
  EEPROM_USER.write(E_TOUCH_THRESHOLD, touch_threshold);
}

void saveKeyMap()
{
  for(u8 p = 0; p < 3; p++)
  {
    for(u8 y = 0; y < 8; y++)
    {
      for(u8 x = 0; x < 4; x++)
      {
        EEPROM_USER.write(E_CUSTOM_KEYMAP_1 + 128*p + y * 4 + x, keymap[2+p][y][x*2]*0x100 + keymap[2+p][y][x*2+1]);
      }
    }

    for(u8 y = 0; y < 2; y++)
    {
      for(u8 x = 0; x < 4; x++)
      {
        EEPROM_USER.write(E_CUSTOM_FN_KEYMAP_1 + 128*p + y*4 + x, fn_keymap[2+p][y][x*2]*0x100 + fn_keymap[2+p][y][x*2+1]);
      }
    }

    for(u8 i = 0; i < 18; i++)
    {
    EEPROM_USER.write(E_CUSTOM_BOTTOM_KEYMAP_1 + 128*p + i, bottom_led_map[2+p][i*2] *0x100 + bottom_led_map[2+p][i*2 + 1]);
    }

    EEPROM_USER.write(E_CUSTOM_KEYMAP_1_COLOR + 128*p, (keymap_colour[2+p] & 0xFFFF0000) >> 16);
    EEPROM_USER.write(E_CUSTOM_KEYMAP_1_COLOR + 128*p + 1, keymap_colour[2+p] & 0xFFFF);

    for(u8 y = 0; y < 2; y++)
    {
      for(u8 x = 0; x < 8; x++)
      {
        EEPROM_USER.write(E_CUSTOM_KEYMAP_1_IDLE + 128*p + y*16 + x, (fn_keymap_idle_color[2+p][y][x*2] & 0xFFFF0000) >> 16);
        EEPROM_USER.write(E_CUSTOM_KEYMAP_1_IDLE + 128*p + y*16 + x + 1, fn_keymap_idle_color[2+p][y][x*2] & 0xFFFF);
      }
    }

    for(u8 y = 0; y < 2; y++)
    {
      for(u8 x = 0; x < 8; x++)
      {
        EEPROM_USER.write(E_CUSTOM_KEYMAP_1_ACTIVE + 128*p + y*16 + x, (fn_keymap_idle_color[2+p][y][x*2] & 0xFFFF0000) >> 16);
        EEPROM_USER.write(E_CUSTOM_KEYMAP_1_ACTIVE + 128*p + y*16 + x + 1, fn_keymap_idle_color[2+p][y][x*2] & 0xFFFF);
      }
    }
  }
}

void savePalette()
{
  for(u8 p = 0; p < 2; p++)
  {
    for(u8 i = 0; i <128; i++)
    {
      EEPROM_PALETTE.write(i * 2 + 256 * p, (palette[p+2][i] & 0xFFFF0000) >> 16);
      EEPROM_PALETTE.write(i * 2 + 256 * p + 1, palette[p+2][i] & 0x0000FFFF);
    }
  }
}
