#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include <EEPROM.h>
#include <USBComposite.h>
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"

class MatrixSystem
{
public:
  MatrixSystem();

  void variableLoad();
  //Sysex set
  void reset();
  void setDeviceID();
  void EnterBootloader();
  void InitializeDevice();
  void updateColourPaletteRGB();
  void updateColourPaletteWRGB();
  void resetColourPalette();
  void setGamma(bool g);
  void updateCustomKeymap();
  void ResetCustomKeymap();
  void setBrightness(uint8_t b);
  void setTouchSensitive(uint8_t s);

  //Sysex get
  void getDeviceInfo();
  void getModuleCount();
  void getModuleInfo();
  void getdevice_id();
  void getAllParameter();
  void getColorPaletteRGB();
  void getColorPaletteWRGB();
  void getGammaState();
  void getCustomKeymap();
  void getBrightness();
  void getTouchSensitive();

  //Math
  uint8_t WRGBtoHEX(uint8_t W, uint8_t R, uint8_t G, uint8_t B);
  uint8_t XYtoIndex(uint8_t X, uint8_t Y);
  uint8_t bottomLEDrotation(int index);
  //uint8_t XYtoIndex(uint8_t X,uint8_t Y);
};

#endif
