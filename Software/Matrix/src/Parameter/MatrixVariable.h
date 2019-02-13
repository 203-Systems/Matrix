#ifndef MATRIX_VARIABLE
#define MATRIX_VARIABLE

#include <Arduino.h>
#include "../Parameter/MatrixParameter.h"

//DeviceInfo
extern u8 device_id; //0~255 0 for off
enum Modes {Normal, Fn, Animation, Boot, Ascii, App};
extern Modes mode;
extern u8 appID;

//LED setting
extern u8 brightness;
extern bool dynamic_brightness;
extern u8 brightness_level[5];

extern u32 palette[3][128];

extern u8 led_gamma[256];

extern u8 bottomLEDmap [NUM_BOTTOM_LEDS];

//KeyPad
extern u8 keymap [YSIZE][XSIZE];

//TouchBar
extern u8 touch_sensitive;

//Sysex
extern u8 rotation;
extern u8 midi_channel;
extern bool gamma_enable; //Wont effect colour palette
extern bool midi_enable;
extern bool m2p_enable;
extern bool powercord_enable;
extern bool massage_return;

extern u8 font[96][6];

extern u8 half_height_num_font[10][3];
#endif
