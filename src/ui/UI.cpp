#include "UI.h"

extern KeyPad KeyPad;
extern LED LED;

UI::UI()
{

}

void UI::enterFNmenu()
{
  LED.enableOverlayMode();
  fnMenu();
}

void UI::fnMenu()
{
  while(1)
  {

    if(midi_enable);
    USBmidi.poll();
    // if (m2p_enable)
    // CDC.Poll();

    if(KeyPad.scan())
    {
      if(KeyPad.fnChanged)
      {
        if(KeyPad.timesFNpressed > 9)
          UI::easterEgg();

        if(KeyPad.fn)
        {
          UI::exitFNmenu();
          return;
        }
        else
        {
          if(KeyPad.fnTimer.isLonger(MULTITAP_THRESHOLD)) //if fn off and longer then threshold, will count as hold, release to back to main menu
          {
            UI::exitFNmenu();
            return;
          }
        }
      }
      fnKeyAction();
    }
  }

  if (uiTimer.tick(1000/FPS))
  {
    UI::fnRender();
  }
}

void UI::exitFNmenu()
{
  LED.disableOverlayMode();
}

void UI::fnKeyAction()
{
  for(int i = 0; i < MULTIPRESS; i++)
  {
    if(KeyPad.list[i].velocity > 128)
    return;
    switch(KeyPad.list[i].xy)
    {
      //Brightness
      case 0x33:
      case 0x34:
      case 0x43:
      case 0x44:
      nextBrightnessState();
      break;

      //rotation
      case 0x32:
      case 0x42:
      rotationCW(0); //Well, this dont do shit.
      break;
      case 0x53:
      case 0x54:
      rotationCW(1); //90
      break;
      case 0x23:
      case 0x24:
      rotationCW(2); //180
      break;
      case 0x35:
      case 0x45:
      rotationCW(3); //270
      break;

      //midi_enable
      case 0x00:
      midi_enable = !midi_enable;
      break;

      //m2p_enable
      case 0x01:
      m2p_enable = !m2p_enable;
      break;

      //powercord_enable
      case 0x67:
      powercord_enable = !powercord_enable;
      break;

      //gamma_enable
      case 0x76:
      gamma_enable = !gamma_enable;
      break;

    }
  }
}

void UI::fnRender()
{
  //brightness
  LED.setXYHEX(3, 3, 0xFFFFFFFF, true);
  LED.setXYHEX(3, 4, 0xFFFFFFFF, true);
  LED.setXYHEX(4, 3, 0xFFFFFFFF, true);
  LED.setXYHEX(4, 4, 0xFFFFFFFF, true);

  //rotation
  LED.setXYHEX(3, 2, 0x0000FF00, true);
  LED.setXYHEX(4, 2, 0x0000FF00, true);
  LED.setXYHEX(5, 3, 0x0000A000, true);
  LED.setXYHEX(5, 4, 0x0000A000, true);
  LED.setXYHEX(2, 3, 0x0000A000, true);
  LED.setXYHEX(2, 4, 0x0000A000, true);
  LED.setXYHEX(3, 5, 0x0000A000, true);
  LED.setXYHEX(4, 5, 0x0000A000, true);

  //Midi enable
  if(midi_enable)
  {
    LED.setXYHEX(0, 0, 0x00FFAA00, true);
  }
  else
  {
    LED.setXYHEX(0, 0, 0x00996500, true);
  }

  //M2P enable
  if(m2p_enable)
  {
    LED.setXYHEX(0, 1, 0x0000FF7F, true);
  }
  else
  {
    LED.setXYHEX(0, 1, 0x007F0099, true);
  }

  //Powercord enable
  if(powercord_enable)
  {
    LED.setXYHEX(6, 7, 0x00D400FF, true);
  }
  else
  {
    LED.setXYHEX(6, 7, 0x0000994C, true);
  }


  //gamma enable
  if(gamma_enable)
  {
    LED.setXYHEX(7, 6, 0x00FFFFFF, true);
  }
  else
  {
    LED.setXYHEX(7, 6, 0x00999999, true);
  }

  //Extra
  LED.setXYHEX(7, 7, 0x00FFFFFF, true); //Setting
  LED.setXYHEX(0, 7, 0x00FFFFFF, true); //AAppLauncher
  LED.setXYHEX(1, 7, 0x00FFFFFF, true); //Text Selctor
  LED.setXYHEX(7, 0, 0x00FFFFFF, true); //KeyMapSelector
}

void UI::showDeviceInfo()
{

}

void UI::showASCII(char* ascii)
{

}

void UI::playAnimation(char* animation)
{

}

void UI::easterEgg()
{

}
