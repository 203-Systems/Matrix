#ifndef EEPROM_H
#define EEPROM_H

#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"
#include <EEPROM.h>
#include <FastLED.h>

  void setupEEPROM();

  void variableLoad();
  CRGB readColorFromEEPROM(u8 palette, u8 index);
  void saveColorToEEPROM(u8 palette, u8 index, CRGB color);

  void loadSetting();
  // void loadKeyMap();
  // void loadPalette();

  void formatEEPROM();
  void initEEPROM();
  void saveAllSetting();
  // void saveKeyMap();
  // void savePalette();

  enum EEPROM_USER_MAP
  {
    E_INIT = 0,
    E_EEPROMVERSION = 1,
    E_DEVICE_ID = 2,
    E_ROTATION = 3,
    E_BRIGHTNESS = 4,
    E_FPS = 5,
    E_GAMMA_ENABLE = 6,
    E_MIDI_ENABLE = 7,
    E_M2P_ENABLE = 8,
    E_RETURN_ENABLE = 9,
    E_UNIPAD_MODE = 10,
    E_BOOTANIMATION = 11,
    E_DEBUG_ENABLE = 12,
    E_CURRENT_KEYMAP = 13,
    E_color_TEMPERTURE_1 = 14,
    E_color_TEMPERTURE_2 = 15,
    E_FN_HOLD = 16,
    E_STFU = 17,
    E_DESATURATED_MODE = 18,
    E_PRO_INPUT_MODE = 19,

    E_color_CORRECTION_1 = 100,
    E_color_CORRECTION_2 = 101,

  };
    //RESERVED 13~511



  enum EEPROM_PALETTE_MAP//16BIT*2
  {
    E_CUSTOM_PALETTE_1 = 0, //0~255
    E_CUSTOM_PALETTE_2 = 256, //256~511
  };

  enum EEPROM_KEYMAP_MAP //Offset of 128 1~4
  {
    E_CUSTOM_KEYMAP = 0,//32 0~31 //2x8
    E_CUSTOM_FN_KEYMAP = 32, //8 32~39
    E_CUSTOM_BOTTOM_KEYMAP = 40,//18 40~57
    E_CUSTOM_KEYMAP_COLOR = 58, //2 58~59
    E_CUSTOM_KEYMAP_COLOR_IDLE = 60, //32 60~91
    E_CUSTOM_KEYMAP_COLOR_ACTIVE = 92, //32 92~124
    //RESERVED 125~127
  };
#endif
