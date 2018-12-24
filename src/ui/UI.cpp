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

    if(uiTimer.tick(1000/FPS))
    UI::fnRender();

    if(midi_enable);
    USBmidi.poll();
    // if (m2p_enable)
    // CDC.Poll();

    if(KeyPad.scan())
    {
      if(KeyPad.fnChanged)
      {
        // if(KeyPad.timesFNpressed > 9)
        // UI::easterEgg();

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
    break;
    if(KeyPad.list[i].velocity != 0)
    {
      switch(KeyPad.list[i].xy)
      {
        //Brightness
        case 0x33:
        case 0x34:
        case 0x43:
        case 0x44:
        LED.nextBrightnessState();
        break;

        //rotation
        case 0x32:
        case 0x42:
        // LED.fill(0, true);
        // rotationCW(0); //Well, this dont do shit.
        break;
        case 0x53:
        case 0x54:
        LED.fill(0, true);
        rotationCW(1); //90
        break;
        case 0x35:
        case 0x45:
        LED.fill(0, true);
        rotationCW(2); //180
        break;
        case 0x23:
        case 0x24:
        LED.fill(0, true);
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

        case 0x70:
        LED.fill(0xFF0000, true);
        LED.update();
        reset();
        break;
      }
    }
  }
  fnRender();
}

void UI::fnRender()
{
  //brightness
  LED.setXYHEX(0x33, 0xFFFFFFFF, true);
  LED.setXYHEX(0x34, 0xFFFFFFFF, true);
  LED.setXYHEX(0x43, 0xFFFFFFFF, true);
  LED.setXYHEX(0x44, 0xFFFFFFFF, true);

  //rotation
  LED.setXYHEX(0x32, 0x0000FF00, true);
  LED.setXYHEX(0x42, 0x0000FF00, true);
  LED.setXYHEX(0x53, 0x00003000, true);
  LED.setXYHEX(0x54, 0x00003000, true);
  LED.setXYHEX(0x23, 0x00003000, true);
  LED.setXYHEX(0x24, 0x00003000, true);
  LED.setXYHEX(0x35, 0x00003000, true);
  LED.setXYHEX(0x45, 0x00003000, true);

  //Midi enable0x
  if(midi_enable)
  {
    LED.setXYHEX(0x00, 0x00FFAA00, true);
  }
  else
  {
    LED.setXYHEX(0x00, 0x00996500, true);
  }

  //M2P enable
  if(m2p_enable)
  {
    LED.setXYHEX(0x01, 0x0000FF7F, true);
  }
  else
  {
    LED.setXYHEX(0x01, 0x007F0099, true);
  }

  //Powercord enable
  if(powercord_enable)
  {
    LED.setXYHEX(0x67, 0x00D400FF, true);
  }
  else
  {
    LED.setXYHEX(0x67, 0x0000994C, true);
  }


  //gamma enable
  if(gamma_enable)
  {
    LED.setXYHEX(0x76, 0x00FFFFFF, true);
  }
  else
  {
    LED.setXYHEX(0x76, 0x00303030, true);
  }

  //Extra
  LED.setXYHEX(0x77, 0x00FFFFFF, true); //Setting
  LED.setXYHEX(0x07, 0x00FFFFFF, true); //AppLauncher
  LED.setXYHEX(0x17, 0x00FFFFFF, true); //Text Selctor
  LED.setXYHEX(0x70, 0x00FF0000, true); //reset

  LED.update();
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
