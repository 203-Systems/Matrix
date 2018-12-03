#include "UI.h"

extern KeyPad KeyPad;
extern LED LED;

UI::UI()
{

}

void UI::enterFNmenu()
{
  LED.enableOverlayMode();
  FNmenu();
}

void UI::fnMenu()
{
  while(1)
  {

    if (midi_enable);
    USBmidi.poll();
    // if (m2p_enable)
    // CDC.Poll();

    if(KeyPad.scan())
    {
      if(KeyPad.fnchanged)
      {

        if(KeyPad.timesfnpressed == 5)
        UI.ShowDeviceInfo();
        if(KeyPad.timesfnpressed == 10)
        UI.EasterEgg();

        if(KeyPad.fn)
        {
          UI::exitFNmenu();
          return;
        }
        else
        {
          if(millis() - KeyPad.lastfnpressed > MULTITAP_THRESHOLD)
          {
            UI::exitfnmenu();
            return;
          }
        }
      }
      fnKeyAction();
    }
  }

  u32 currentMillis = millis();
  if (currentMillis - previousMillis >= 1000/FPS)
  {
    UI::fnrender();
    previousMillis = currentMillis;
  }
}

void UI::exitFNmenu()
{
  LED.disableOverlayMode();
}

void UI::fnKeyAction()
{

}

void UI::fnRender()
{

}

void UI::showDeviceInfo()
{

}

void UI::showASCII(char* ascii)
{

}

void UI::playAnimation(Animation a)
{

}

void UI::easterEgg()
{

}
