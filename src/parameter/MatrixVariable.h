#ifndef MATRIX_VARIABLE
#define MATRIX_VARIABLE

#include <Arduino.h>
#include "../parameter/MatrixParameter.h"

//DeviceInfo
extern uint8_t device_id;

//LED setting
extern uint8_t brightness;
extern uint64_t palette[3][128];

extern uint8_t bottomLEDmap [NUM_BOTTOM_LEDS];

//KeyPad
extern uint8_t Keymap [KEYPADY][KEYPADX] PROGMEM;

//TouchBar
extern uint8_t touch_sensitive;

//Sysex
extern uint8_t rotation;

extern uint8_t midi_channel;
extern bool gamma_enable;
extern bool midi_enable;
extern bool m2p_enable;
extern bool powercord_enable;
extern bool massage_return;

#endif
