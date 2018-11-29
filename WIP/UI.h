#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include "MatrixVariable.h"
#include "MatrixParameter.h"
#include "MatrixSystem.h"
#include "KeyPad.h"
//#include "MIDI.h"
//#include <USBComposite.h>

struct Animation
{
  uint8_t Mode; //0 for full array are NUM_LEDS * FPS | 1 for xy mode XY+
  uint8_t AnimationFPS;
  char* AnimationData;
};

class UI
{
public:
  UI();
  void FN();
  void ShowDeviceInfo()
  void ShowASCII(char* ascii)
  void PlayAnimation(Animation a)
  void EasterEgg()
private:
}
