#ifndef MATRIX_VARIABLE
#define MATRIX_VARIABLE

#include <Arduino.h>
#include "../parameter/MatrixParameter.h"

//DeviceInfo
extern u8 device_id;

//LED setting
extern u8 brightness;
extern u64 palette[3][128];

extern u8 bottomLEDmap [NUM_BOTTOM_LEDS];

//KeyPad
extern u8 keymap[KEYPADY][KEYPADX];

//TouchBar
extern u8 touch_sensitive;

//Sysex
extern u8 rotation;

extern u8 midi_channel;
extern bool gamma_enable;
extern bool midi_enable;
extern bool m2p_enable;
extern bool powercord_enable;
extern bool massage_return;

extern u8 text_bitmap[96][6] PROGMEM;
#endif
