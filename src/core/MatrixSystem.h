#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include <EEPROM.h>
#include <USBComposite.h>
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"

// struct XY
// {
//   u8 x;
//   u8 y;
// }

void initEEPROM();
void variableLoad();
//load from EEPROM
void loadPalette();
void loadKeymap();

void resetEEPROM();

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
void setBrightness(u8 b);
void setTouchSensitive(u8 s);

//Sysex get
void getDeviceInfo();
void getModuleCount();
void getModuleInfo();
void getdevice_id();
void getAllParameter();
void getPaletteRGB();
void getPaletteWRGB();
void getgammaState();
void getCustomKeymap();
void getBrightness();
void getTouchSensitive();

//special
void nextBrightnessState();
void rotationCW(u8 v);
//Math
u8 wrgbToHEX(u8 w, u8 r, u8 g, u8 b);
u8 xyToIndex(u8 x, u8 y);
// XY indexToXY(u8 index);
u8 indexRotation(int index);
u8 bottomLEDrotation(int index);
//u8 xyToIndex(u8 X,u8 Y);

#endif
