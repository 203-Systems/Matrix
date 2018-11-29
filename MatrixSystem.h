#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include <EEPROM.h>
#include <USBComposite.h>
#include "MatrixVariable.h"
#include "MatrixParameter.h"

class MatrixSystem
{
public:
  MatrixSystem();

  void VariableLoad();
  //Sysex set
  void Reset();
  void Setdevice_id();
  void EnterBootloader();
  void InitializeDevice();
  void UpdateColourPaletteRGB();
  void UpdateColourPaletteWRGB();
  void ResetColourPalette();
  void SetGamma(bool g);
  void UpdateCustomKeymap();
  void ResetCustomKeymap();
  void SetBrightness(uint8_t b);
  void SetTouchSensitive(uint8_t s);

  //Sysex Get
  void GetDeviceInfo();
  void GetModuleCount();
  void GetModuleInfo();
  void Getdevice_id();
  void GetAllParameter();
  void GetColorPaletteRGB();
  void GetColorPaletteWRGB();
  void GetGammaState();
  void GetCustomKeymap();
  void GetBrightness();
  void GetTouchSensitive();

  //Math
  uint8_t WRGBtoHEX(uint8_t W, uint8_t R, uint8_t G, uint8_t B);
  uint8_t XYtoIndex(uint8_t X, uint8_t Y);
  uint8_t BottomLEDrotation(int index);
  //uint8_t XYtoIndex(uint8_t X,uint8_t Y);
};

#endif
