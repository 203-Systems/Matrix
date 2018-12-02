#include "UI.h"

extern KeyPad KeyPad;
extern LED LED;

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

void NexusRevamped()
{
  struct NexusElement
  {
    uint8_t spawn; //location of spawn 0~8 top down, 
    uint8_t hue; //0~15 203pallette
    uint8_t ttl = 0; //time to live
  }

  uint32_t randertimer = 0;
  uint32_t spawntimer = 0;

  while (/*!Serials*/) {
    if(mills() - randertimer >= 1000/FPS)
    {

    }
  }

}

void UI::PlayAnimation(Animation a)
{

}

void UI::EasterEgg()
{

}
