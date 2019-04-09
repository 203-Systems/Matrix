#include "UI.h"

//#define DEBUG //CDC info

extern KeyPad KeyPad;
extern LED LED;
extern MIDI Midi;
UIelement uielement;

u8 next_code = 0;

UI::UI()
{

}

void UI::enterFNmenu()
{
  next_code = 0;
  #ifdef DEBUG
  CompositeSerial.println("Enter FN");
  // CompositeSerial.println(BOOTLOADER_VERSION);
  // CompositeSerial.println(MATRIX_MODEL, HEX);
  // CompositeSerial.println(MATRIX_VERSION);
  // CompositeSerial.println(MATRIX_BATCH);
  // CompositeSerial.println(device_config);
  #endif

  LED.enableOverlayMode();
  hadAction = false;
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
    Midi.poll();
    // if (m2p_enable)
    // CDC.Poll();

    if(uiTimer.tick(1000/fps))
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
          else if(!KeyPad.fn && (KeyPad.fnTimer.isLonger(MULTITAP_THRESHOLD) || hadAction)) //if fn off and longer then threshold, will count as hold, release to back to main menu
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
  //flags
  bool flag_rotated = false;

  for(int i = 0; i < MULTIPRESS; i++)
  {
    if(KeyPad.list[i].velocity == -1)
    return;

    //hadAction = true;

    #ifdef DEBUG
    CompositeSerial.print("FN Key Action ");
    CompositeSerial.print(xytoxy(KeyPad.list[i].xy).y);
    CompositeSerial.print(" ");
    CompositeSerial.print(xytoxy(KeyPad.list[i].xy).x);
    #endif

    if(KeyPad.list[i].velocity == 0){
      if(xytoxy(KeyPad.list[i].xy).y > 5)
      {
        Midi.sentNoteOff(0, fn_keymap[current_keymap][xytoxy(KeyPad.list[i].xy).y - 6][xytoxy(KeyPad.list[i].xy).x], 0);
      }
    }

    if(KeyPad.list[i].velocity > 0)
    {
      #ifdef DEBUG
      CompositeSerial.print("ReadKey ");
      CompositeSerial.println(KeyPad.list[i].xy, HEX);
      #endif
      if(xytoxy(KeyPad.list[i].xy).y > 5)
      {
        Midi.sentNoteOn(0, fn_keymap[current_keymap][xytoxy(KeyPad.list[i].xy).y - 6][xytoxy(KeyPad.list[i].xy).x], 127);
      }
      switch(KeyPad.list[i].xy)
      {
        //Brightness
        case 0x33:
        case 0x34:
        case 0x43:
        case 0x44:
        if(!KeyPad.fn || KeyPad.fnTimer.isLonger(200))
        {
          nextBrightnessState();
          #ifdef DEBUG
          CompositeSerial.print("Brightness ");
          CompositeSerial.println(brightness);
          #endif
        }
        break;

        //rotation
        case 0x32:
        case 0x42:
        LED.fill(0); //Clean Canvas
        break;
        case 0x53:
        case 0x54:
        if(!flag_rotated)
        {
          LED.fill(0, true);
          rotationCW(1); //90
          flag_rotated = true;
        }
        break;
        case 0x35:
        case 0x45:
        if(!flag_rotated)
        {
          LED.fill(0, true);
          rotationCW(2); //190
          flag_rotated = true;
        }
        break;
        case 0x23:
        case 0x24:
        if(!flag_rotated)
        {
          LED.fill(0, true);
          rotationCW(3); //270
          flag_rotated = true;
        }
        break;

        case 0x10:
        setCurrentKeyMap(0);
        break;
        case 0x20:
        setCurrentKeyMap(1);
        break;
        case 0x30:
        setCurrentKeyMap(2);
        break;
        case 0x40:
        setCurrentKeyMap(3);
        break;
        case 0x50:
        setCurrentKeyMap(4);
        break;

        case 0x60:
        setUnipadMode(!unipad_mode);
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
        // case 0x75:
        // gamma_enable = !gamma_enable;
        // break;

        case 0x05: //DFU
        LED.fill(0xFF0000, true);
        LED.update();
        enterBootloader();
        break;

        // case 0x60:
        // LED.fill(0xFFFF00, true);
        // LED.update();
        // resetDevice();
        // reset();
        // break;

        case 0x75:
        setDeviceID(UI::numSelector8bit(device_id, 0x0000FFAA, true));
        break;

        case 0x74:
        setDeviceID(UI::numSelector8bit(device_id, 0x0000FFAA, true));
        break;

        // case 0x61: //RESET
        // LED.fill(0, true);
        // LED.update();
        // reset();
        // break;

        // case 0x75:   //ERROR CODE
        // CompositeSerial.print("Code N");
        // CompositeSerial.print(next_code);
        // CompositeSerial.print(" ");
        // CompositeSerial.println(report_code[next_code]);
        // UI::numSelector8bit(report_code[next_code],0x00FF0000, true);
        // next_code ++;
        // break;
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
  LED.setXYHEX(0x33, 0xFFFFFFFF, true, true);
  LED.setXYHEX(0x34, 0xFFFFFFFF, true, true);
  LED.setXYHEX(0x43, 0xFFFFFFFF, true, true);
  LED.setXYHEX(0x44, 0xFFFFFFFF, true, true);

  //rotation
  LED.setXYHEX(0x32, 0x0000FF00, true, true);
  LED.setXYHEX(0x42, 0x0000FF00, true, true);
  LED.setXYHEX(0x53, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);
  LED.setXYHEX(0x54, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);
  LED.setXYHEX(0x23, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);
  LED.setXYHEX(0x24, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);
  LED.setXYHEX(0x35, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);
  LED.setXYHEX(0x45, LED.toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);

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


  //Extra
  // LED.setXYHEX(0x77, 0x00FFFFFF, true); //Setting
  // LED.setXYHEX(0x07, 0x00FFFFFF, true); //AppLauncher
  // LED.setXYHEX(0x17, 0x00FFFFFF, true); //Text Selctor
  LED.setXYHEX(0x05, 0x00FF0000, true, true); //DFU
  LED.setXYHEX(0x74, 0x0000FFAA, true, true); //White
  LED.setXYHEX(0x75, 0x0000FFAA, true, true); //Device ID
  //LED.setXYHEX(0x60, 0x00FFFF00, true, true); //reset device
  //LED.setXYHEX(0x61, 0x0000FF66, true, true); //reboot

  LED.setXYHEX(0x10, LED.toBrightness(keymap_colour[0], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  LED.setXYHEX(0x20, LED.toBrightness(keymap_colour[1], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  LED.setXYHEX(0x30, LED.toBrightness(keymap_colour[2], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  LED.setXYHEX(0x40, LED.toBrightness(keymap_colour[3], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  LED.setXYHEX(0x50, LED.toBrightness(keymap_colour[4], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  if(unipad_mode)
  {
    LED.setXYHEX(0x60, 0xFFFF00, true, true);
  }
  else
  {
    LED.setXYHEX(0x60, LED.toBrightness(0xFFFF00, LOWSTATEBRIGHTNESS), true, true);
  }

  switch(current_keymap)
  {
    case 0:
    LED.setXYHEX(0x10, keymap_colour[0], true, true);
    break;
    case 1:
    LED.setXYHEX(0x20, keymap_colour[1], true, true);
    break;
    case 2:
    LED.setXYHEX(0x30, keymap_colour[2], true, true);
    break;
    case 3:
    LED.setXYHEX(0x40, keymap_colour[3], true, true);
    break;
    case 4:
    LED.setXYHEX(0x50, keymap_colour[4], true, true);
    break;
  }

  for(u8 y = 6; y < 8; y++)
  {
    for(u8 x = 0; x < 8; x++)
    {
      if(KeyPad.checkXY(x, y))
      {
        LED.setXYHEX(xytoxy(x, y), fn_keymap_active_color[current_keymap][y - 6][x], true, true);
      }
      else
      {
        LED.setXYHEX(xytoxy(x, y), fn_keymap_idle_color[current_keymap][y - 6][x], true, true);
      }
    }
  }
  // #ifdef DEBUG
  // CompositeSerial.println("End Render");
  // #endif

  LED.update();
}

u8 UI::numSelector8bit(u8 currentNum, u32 colour, bool ignore_gamma /* = false */)
{
  // LED.fill(0, true);
  while(!KeyPad.fnChanged)
  {
    if(uiTimer.tick(1000/fps))
    {
      if(KeyPad.scan())
      {
        LED.fill(0, true);
        currentNum = uielement.binary8bitInput(currentNum, 7, colour, ignore_gamma);
        uielement.renderHalfHeightNum(currentNum, 0x73, colour, ignore_gamma);
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

u8 UI::numSelector6bit(u8 currentNum, u32 colour, bool ignore_gamma /* = false */)
{

}

u32 UI::numSelectorRGB(u32 currentNum, u32 colour, bool ignore_gamma /* = false */)
{

  u8 R = (currentNum & 0xFF0000) >> 16;
  u8 G = (currentNum & 0xFF00) >> 8;
  u8 B = currentNum & 0xFF;
  while(!KeyPad.fnChanged)
  {
    if(uiTimer.tick(1000/fps))
    {
      if(KeyPad.scan())
      {
        LED.fill(0);

        if(R != uielement.binary8bitInput(R, 5, 0xFF0000, ignore_gamma))
        {
          R = uielement.binary8bitInput(R, 5, 0xFF0000, ignore_gamma);
          colour = R << 16 + colour & 0x00FFFF;
          uielement.renderHalfHeightNum(currentNum, 0x73, colour, ignore_gamma);
        }
        else if(G != uielement.binary8bitInput(G, 6, 0x00FF00, ignore_gamma))
        {
          G = uielement.binary8bitInput(G, 6, 0x00FF00, ignore_gamma);
          colour = G << 8 + colour & 0xFF00FF;
          uielement.renderHalfHeightNum(currentNum, 0x73, colour, ignore_gamma);
        }
        else if(B != uielement.binary8bitInput(B, 7, 0x0000FF, ignore_gamma))
        {
          B = uielement.binary8bitInput(B, 7, 0x0000FF, ignore_gamma);
          colour = B + colour & 0xFFFF00;
          uielement.renderHalfHeightNum(currentNum, 0x73, colour, ignore_gamma);
        }

        LED.update();
      }
    }
  }
  LED.fill(0, true);
  return currentNum;
}

u32 UI::numSelectorWRGB(u32 currentNum, u32 colour, bool ignore_gamma /* = false */)
{

}

void UI::showDeviceInfo()
{

}

void UI::showASCII(char ascii[], u32 colour, bool ignore_gamma /* = false */)
{

}

void UI::playAnimation(char animation[])
{

}

// void UI::scrollText(char ascii[], u8 xy, u8 speed, u32 colour, bool ignore_gamma /* = false */)
// {
//   u8 current = 0;
//   u8 numOfChar;
//   u8 space = 2;
//   u8 firstX = font[ascii[0]][0] + XSIZE - 2;
//   u8 lastX;
//
//   while(current > sizeof(ascii))
//   {
//     if(ascii[current] < 32)
//     {
//       speed = ascii[current];
//     }
//     else
//     {
//       UIe.renderAscii(ascii[current], xytoxy(firstX, 7), colour, ignore_gamma);
//     }
//
//     lastX = firstX;
//     numOfChar = 1;
//
//     while(lastX < XSIZE - space - 2)
//     {
//       //lastX = lastX + space +
//     }
//   }
//   firstX--;
//   while(uiTimer.tick(speed*2));
// }
