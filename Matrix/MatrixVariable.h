#ifndef MATRIX_VARIABLE
#define MATRIX_VARIABLE

#include <Arduino.h>

//DeviceInfo
extern uint8_t DeviceID; //0;

//LED
extern uint8_t Brightness; //64;
extern uint64_t colour[3][128]; //    //WRGB Colour Pallette

//KeyPad
extern uint8_t KeyMap [8][8];

//TouchBar
extern uint8_t TouchSensitive; //0;

//Sysex
extern uint8_t MIDIChannel;
extern bool MIDIEnable; //true;
extern bool CDCEnable; //true;
extern bool POWERCORD; //false;
extern bool RETURN; //false;

#endif
