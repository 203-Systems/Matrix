#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
#include "../core/MatrixSystem.h"
#include "../core/KeyPad.h"
//#include "../protocol/MIDI.h"
//#include <USBComposite.h>

struct Animation
{
  u8 Mode; //0 for full array are NUM_LEDS * FPS | 1 for xy mode XY+
  u8 AnimationFPS;
  char* AnimationData;
};

struct Key
{
  u8 Mode; //0 for full array are NUM_LEDS * FPS | 1 for xy mode XY+
  u8 AnimationFPS;
  char* AnimationData;
};

class UI
{
public:
  UI();
  void EnterFNmenu();
  void FNmenu();
  void ExitFNmenu();
  void FNkeyAction();
  void FNrender();
  void ShowDeviceInfo()
  void ShowASCII(char* ascii)
  void NexusRevamped()
  void PlayAnimation(Animation a)
  void EasterEgg()
private:
};

class
