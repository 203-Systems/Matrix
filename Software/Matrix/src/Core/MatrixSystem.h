#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include <EEPROM.h>
#include <libmaple/bkp.h>
#include <libmaple/nvic.h>
#include <USBComposite.h>
#include <USBMIDI.h>
#include <FastLED.h>
#include "../Protocol/USBmidi.h"
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"

struct XY
{
  u8 x;
  u8 y;
};

void bootDevice();

void setupUSB();
u16 setupEEPROM();

void variableLoad();
//load from EEPROM
void loadPalette();
void loadKeymap();

void initEEPROM();

//Sysex set
void reset();
void setDeviceID();
void setDeviceID(u8 id);
void enterBootloader();
void resetDevice();
void formatEEPROM();
void updatePaletteRGB();
void updatePaletteWRGB();
void resetPalette();
void setgamma(bool g);
void updateCustomKeymap();
void resetCustomKeymap();
void setBrightnesss(u8 b);
void setTouchSensitive(u8 s);

//Sysex get
void getDeviceInfo();
void getModuleCount();
void getModuleInfo();
void getDeviceID();
void getAllParameter();
void getPaletteRGB();
void getPaletteWRGB();
void getgammaState();
void getCustomKeymap();
void getBrightness();
void getTouchSensitive();

//special
void nextBrightnessState();
void rotationCW(u8 r);
void setRotation(u8 r);
//Math
u8 wrgbToHEX(u8 w, u8 r, u8 g, u8 b);
u8 xyToIndex(u8 xy);
u8 indexToXY(u8 index);
u8 indexRotation(int index);
u8 bottomLEDrotation(int index);
u8 xytoxy(u8 x, u8 y);
XY xytoxy(u8 xy);
u8 xyRotation(u8 xy);
u8 xyReverseRotation(u8 xy);
//u8 xyToIndex(u8 X,u8 Y);

#endif
