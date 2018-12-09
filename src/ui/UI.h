#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
#include "../core/MatrixSystem.h"
#include "../core/USBmidi.h"
#include "../core/KeyPad.h"
#include "../core/LED.h"
#include "../core/Timer.h"
//#include "../protocol/MIDI.h"
//#include <USBComposite.h>

// struct Animation
// {
//   u8 Mode; //0 for full array are NUM_LEDS * FPS | 1 for xy mode XY+
//   u8 AnimationFPS;
//   char* AnimationData;
// };



class UI
{
public:
  UI();
  void enterFNmenu();
  void fnMenu();
  void exitFNmenu();
  void fnKeyAction();
  void fnRender();
  void showDeviceInfo();
  void showASCII(char* ascii);
  void playAnimation(Animation a);
  void easterEgg();
private:
  Timer uiTimer;
};

#endif
