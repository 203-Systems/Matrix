#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"
#include "../Protocol/MIDI.h"
#include "../HAL/KeyPad.h"
#include "../HAL/LED.h"
#include "../HAL/Timer.h"
#include "../Components/UIelement.h"

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

  void enterBootAnimation();
  
  u8 numSelector8bit(u8 currentNum, u32 color, u32 sec_color);
  u8 numSelector6bit(u8 currentNum, u32 color, u32 sec_color);
  u32 numSelectorRGB(u32 color);
  //u32 numSelectorWRGB(u32 color);
  
  void scrollText(char ascii[], CRGB color, u8 speed = 10, bool loop = false, u8 length = 0);
  void clearEEPROM();
  void standbyMode();

private:
  void fnMenu();
  void exitFNmenu();
  void fnKeyAction();
  void fnRender();

  void enterSettingMenu();
  void settingMenu();
  void exitSettingMenu();
  void settingKeyAction();
  void settingRender();

  void kaskobiWaitAnimation();
  void kaskobiBootAnimation();

  Timer uiTimer;
  bool hadAction = false;
  u8 brightness_cache;
  u16 onPause = 0;
  u8 konami_progress = 0;
};

//extern UI UI;

#endif
