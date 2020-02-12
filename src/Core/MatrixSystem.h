#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include <EEPROM.h>
#include <libmaple/bkp.h>
#include <libmaple/nvic.h>
#include <USBComposite.h>
#include <FastLED.h>
#include "../HAL/Keypad.h"
#include "../HAL/LED.h"
#include "../HAL/Timer.h"
#include "../Protocol/MIDI.h"
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Parameter/DeviceSelector.h"
#include "../Core/EEPROM.h"
#include "../Components/color.h"

// struct XY
// {
//   u8 x;
//   u8 y;
// };

extern Timer mainTimer;
extern MicroTimer microTimer;

void setupUSB();
void setupHardware();

void specialBoot();
void factoryTest();

//Sysex set
void reboot();
void setDeviceID();
void setDeviceID(u8 id);
void enterBootloader();
void resetDevice();
void compilePalette();
void updatePaletteRGB();
void updatePaletteWRGB();
void resetPalette();
void setgamma(bool g);
void updateCustomKeymap();
void resetCustomKeymap();
void nextBrightnessState();
void setBrightness(u8 b);
void setCurrentKeyMap(u8 m);
void setUnipadMode(bool u);
void setFnHold(bool h);
void setTouchThreshold(u16 t);
void setcolorCorrection(u32 c, bool temp = false);
void setSTFU(u16 v);
//void setTouchSensitive(u8 s);

//Sysex get
// void getDeviceInfo();
// void getModuleCount();
// void getModuleInfo();
// void getDeviceID();x
// void getAllParameter();
// void getPaletteRGB();
// void getPaletteWRGB();
// void getgammaState();
// void getCustomKeymap();
// void getBrightness();
//void getTouchSensitive();

//special
//void nextBrightnessState();
//void resetTouchBar();
void rotationCW(u8 r);
void setRotation(u8 r);

//Math
u8 wrgbToHEX(u8 w, u8 r, u8 g, u8 b);
u8 xyToIndex(u8 xy);
u8 indexToXY(u8 index);
u8 indexRotation(int index);
u8 bottomLEDrotation(int index);
u8 xytoxy(u8 x, u8 y);
//XY xytoxy(u8 xy);
u8 xytox(u8 xy);
u8 xytoy(u8 xy);
//u8 xyToIndex(u8 X,u8 Y);
u8 xyRotation(u8 xy);
u8 xyRotation(u8 xy, u8 r);
u8 xyReverseRotation(u8 xy);
u8 xyReverseRotation(u8 xy, u8 r);
u8 touchbarRotate(u8 id);
u32 toBrightness(u32 hex, float f, bool dont_write = false);
void recordReportCode(u8 code);
//u16 velocityCurve(u16 input);

u8 convert_6BitTo8Bit(u8 input);
u8 convert_7BitTo8Bit(u8 input);

#endif
