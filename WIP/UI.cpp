#include "UI.h"

extern KeyPad KeyPad;

UI::UI()
{

}

void UI::EnterFNmenu()
{
  LEDwrite = false;
  FNmenu();
}

void UI::FNmenu()
{
  while(1)
  {

    if (midi_enable);
    USBmidi.poll();
    // if (m2p_enable)
    // CDC.Poll();

    if(KeyPad.Scan())
    {
      if(KeyPad.fnChanged)
      {

        if(KeyPad.timesFNpressed == 5)
        UI.ShowDeviceInfo();
        if(KeyPad.timesFNpressed == 10)
        UI.EasterEgg();

        if(KeyPad.FN)
        {
          UI::ExitFNmenu();
          return;
        }
        else
        {
          if(millis() - KeyPad.lastFNpressed > MULTITAP_THRESHOLD)
          {
            UI::ExitFNmenu();
            return;
          }
        }
      }
      FNkeyAction();
    }
  }

  uint32_t currentMillis = millis();
  if (currentMillis - previousMillis >= 1000/FPS)
  {
    UI::FNrender();
    previousMillis = currentMillis;
  }
}

void UI::ExitFNmenu()
{
  LEDwrite = true;
}

void UI::FNkeyAction()
{

}

void UI::FNrender()
{

}

void UI::ShowDeviceInfo()
{

}

void UI::ShowASCII(char* ascii)
{

}

void UI::PlayAnimation(Animation a)
{

}

void UI::EasterEgg()
{

}
