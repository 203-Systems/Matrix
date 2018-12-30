#include "UI.h"

#define DEBUG //CDC info

extern KeyPad KeyPad;
extern LED LED;

UI::UI()
{

}

void UI::enterFNmenu()
{
  #ifdef DEBUG
  CompositeSerial.println("Enter FN");
  #endif

  LED.enableOverlayMode();
  fnMenu();
}

void UI::fnMenu()
{
  #ifdef DEBUG
  CompositeSerial.println("FN");
  #endif
  while(1)
  {
    if(midi_enable);
    USBmidi.poll();
    // if (m2p_enable)
    // CDC.Poll();

    if(uiTimer.tick(1000/FPS))
    {
      UI::fnRender();

      if(KeyPad.scan())
      {
        #ifdef DEBUG
        CompositeSerial.println("FnMenuKeyScaned");
        #endif
        if(KeyPad.fnChanged)
        {
          // if(KeyPad.timesFNpressed > 9)
          // UI::easterEgg();

          if(KeyPad.fn)
          {
            UI::exitFNmenu();
            return;
          }
          else if(!KeyPad.fn && KeyPad.fnTimer.isLonger(MULTITAP_THRESHOLD)) //if fn off and longer then threshold, will count as hold, release to back to main menu
          {
            UI::exitFNmenu();
            return;
          }
        }
        fnKeyAction();
      }
    }
  }
}

void UI::exitFNmenu()
{
  #ifdef DEBUG
  CompositeSerial.println("Exit FN");
  #endif
  LED.disableOverlayMode();
}

void UI::fnKeyAction()
{
  for(int i = 0; i < MULTIPRESS; i++)
  {
    if(KeyPad.list[i].velocity == -1)
    break;
    if(KeyPad.list[i].velocity != 0)
    {
      #ifdef DEBUG
      CompositeSerial.print("ReadKey ");
      CompositeSerial.println(KeyPad.list[i].xy);
      #endif
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

        // //midi_enable
        // case 0x00:
        // midi_enable = !midi_enable;
        // break;
        //
        // //m2p_enable
        // case 0x01:
        // m2p_enable = !m2p_enable;
        // break;
        //
        // //powercord_enable
        // case 0x67:
        // powercord_enable = !powercord_enable;
        // break;

        //gamma_enable
        case 0x76:
        gamma_enable = !gamma_enable;
        break;

        case 0x70:
        LED.fill(0xFF0000, true);
        LED.update();
        enterBootloader();
        break;

        case 0x71:
        setDeviceID(UI::numSelector8bit(device_id, 0x00FFAA));
        break;
      }
    }
  }
  fnRender();
}

void UI::fnRender()
{
  // #ifdef DEBUG
  // CompositeSerial.println("Render");
  // #endif
  //brightness
  LED.setXYHEX(0x33, 0xFFFFFFFF, true);
  LED.setXYHEX(0x34, 0xFFFFFFFF, true);
  LED.setXYHEX(0x43, 0xFFFFFFFF, true);
  LED.setXYHEX(0x44, 0xFFFFFFFF, true);

  //rotation
  LED.setXYHEX(0x32, 0x0000FF00, true);
  LED.setXYHEX(0x42, 0x0000FF00, true);
  LED.setXYHEX(0x53, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true);
  LED.setXYHEX(0x54, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true);
  LED.setXYHEX(0x23, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true);
  LED.setXYHEX(0x24, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true);
  LED.setXYHEX(0x35, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true);
  LED.setXYHEX(0x45, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true);

  // //Midi enable0x
  // if(midi_enable)
  // {
  //   LED.setXYHEX(0x00, 0x00FFAA00, true);
  // }
  // else
  // {
  //   LED.setXYHEX(0x00, LED.toBrightness(0x00FFFFFF, LOWSTATEBRIGHTNESS), true);
  // }
  //
  // //M2P enable
  // if(m2p_enable)
  // {
  //   LED.setXYHEX(0x01, 0x0000FF7F, true);
  // }
  // else
  // {
  //   LED.setXYHEX(0x01, LED.toBrightness(0x0000FF7F, LOWSTATEBRIGHTNESS), true);
  // }
  //
  // //Powercord enable
  // if(powercord_enable)
  // {
  //   LED.setXYHEX(0x67, 0x00D400FF, true);
  // }
  // else
  // {
  //   LED.setXYHEX(0x67, LED.toBrightness(0x00D400FF, LOWSTATEBRIGHTNESS), true);
  // }


  //gamma enable
  if(gamma_enable)
  {
    LED.setXYHEX(0x76, 0x00FFFFFF, true);
  }
  else
  {
    LED.setXYHEX(0x76, LED.toBrightness(0x00FFFFFF, LOWSTATEBRIGHTNESS), true);
  }

  //Extra
  // LED.setXYHEX(0x77, 0x00FFFFFF, true); //Setting
  // LED.setXYHEX(0x07, 0x00FFFFFF, true); //AppLauncher
  // LED.setXYHEX(0x17, 0x00FFFFFF, true); //Text Selctor
  LED.setXYHEX(0x70, 0x00FF0000, true); //reset
  LED.setXYHEX(0x71, 0x0000FFAA, true); //reset

  // #ifdef DEBUG
  // CompositeSerial.println("End Render");
  // #endif

  LED.update();
}

u8 UI::numSelector8bit(u8 currentNum, u32 colour)
{
  // LED.fill(0, true);
  while(!KeyPad.fnChanged)
  {
    if(uiTimer.tick(1000/FPS))
    {
      if(KeyPad.scan())
      {
        LED.fill(0, true);
        currentNum = UI::binary8bitInput(currentNum, 7, colour);
        UI::renderHalfHeightNum(currentNum, 0x73, colour);
        #ifdef DEBUG
        CompositeSerial.print("numSelector\t");
        CompositeSerial.println(currentNum);
        #endif
        LED.update();
      }
    }
  }
  LED.fill(0, true);
  return currentNum;
}

u8 UI::numSelector6bit(u8 currentNum, u32 colour)
{

}

u32 UI::numSelectorRGB(u32 currentNum, u32 colour)
{

}

u32 UI::numSelectorWRGB(u32 currentNum, u32 colour)
{

}

void UI::showDeviceInfo()
{

}

void UI::showASCII(char ascii[])
{

}

void UI::playAnimation(char animation[])
{

}

void UI::renderText(char ascii[], u8 xy, u32 colour)
{

}

void UI::renderLetter(char ascii, u8 xy, u32 colour)
{

}

void UI::renderHalfHeightNum(u8 num, u8 xy, u32 colour)
{
  //LED.fillRegionOff(0x00, 0x73, true);
  if(num > 99)
  UI::renderHalfHeightDigit(num / 100, 0x13, colour);

  if(num > 9)
  UI::renderHalfHeightDigit(num % 100 / 10 , 0x43, 0x00FFFFFF);

  UI::renderHalfHeightDigit(num % 10, 0x73, colour);
}

void UI::renderHalfHeightDigit(u8 num, u8 xy, u32 colour) //XY is the bottom right location
{
  s8 x = (xy & 0xF0) >> 4;
  for(s8 xi = 2; xi >= 0; xi--)
  {
    if(x == -1 && x == KEYPADX)
    break;
    s8 y = (xy & 0x0F);
    for(s8 yi = 0; yi < 4; yi++)
    {
      if(y == -1 && y == KEYPADY)
      break;

      LED.setXYHEX(xytoxy(x, y), colour * bitRead(half_height_num_font[num][xi], yi), true);
      y--;
    }
    x--;
  }
}

u8 UI::binary8bitInput(u8 currentNum, u8 y, u32 colour)
{
  for(int x = 0; x < 8; x++)
  {
    if(KeyPad.checkXY(x, y))
    bitWrite(currentNum, 7 - x, !bitRead(currentNum, 7 - x));
    if(bitRead(currentNum, 7 - x))
    {
      LED.setXYHEX(xytoxy(x, y), colour, true);
    }
    else
    {
      LED.setXYHEX(xytoxy(x, y), LED.toBrightness(colour, LOWSTATEBRIGHTNESS), true);
    }
  }
  return currentNum;
}

void UI::easterEgg()
{

}
