#ifndef MATRIX_VARIABLE
#define MATRIX_VARIABLE

#include <Arduino.h>
#include "../parameter/MatrixParameter.h"

//DeviceInfo
extern uint8_t device_id PROGMEM;

//LED setting
extern uint8_t brightness;
extern bool LEDwrite;
extern uint64_t colour_pallette[2][128] PROGMEM;

extern uint8_t bottomledmap [NUM_BOTTOM_LEDS];
extern uint8_t defaultbottomledmap [NUM_BOTTOM_LEDS] PROGMEM;

//KeyPad
extern uint8_t keymap [KEYPADY][KEYPADX];

extern uint8_t defaultkeymap [KEYPADY][KEYPADX] PROGMEM;

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
