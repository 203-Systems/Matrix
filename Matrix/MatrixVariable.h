#ifndef MATRIX_VARIABLE
#define MATRIX_VARIABLE

#include <Arduino.h>
#include <stdint.h>


//DeviceInfo
extern uint8 DeviceID; //0;

//LED
extern uint8 Brightness; //64;
extern uint64 colour[3][128]; //    //WRGB Colour Pallette

//KeyPad
extern uint8 KeyMap [8][8];

//TouchBar
extern uint8 TouchSensitive; //0;

//Sysex
extern bool MIDIEnable; //true;
extern bool CDCEnable; //true;
extern bool POWERCORD; //false;
extern bool RETURN; //false;

#endif
