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
  konami_progress = 0;

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
  UI::fnMenu();
}

void UI::fnMenu()
{
  #ifdef DEBUG
  CompositeSerial.println("FN");
  #endif
  UI::fnRender();
  while(1)
  {
    Midi.poll();

    if(uiTimer.tick(1000/fps))
    {
      //

      if(KeyPad.scan())
      {
        #ifdef DEBUG
        CompositeSerial.println("FnMenuKeyScaned");
        #endif
        if(KeyPad.fn.state == PRESSED)
        {
          UI::exitFNmenu();
          return;
        }
        else if(KeyPad.fn.state == RELEASED && !fn_hold && (KeyPad.fn.hold || hadAction )) //if fn off and longer then threshold, will count as hold, release to back to main menu
        {
          UI::exitFNmenu();
          return;
        }
        UI::fnKeyAction();
        UI::fnRender();
      }
      // CompositeSerial.print("FN Status: ");
      // CompositeSerial.print(KeyPad.fn.state);
      // CompositeSerial.print(" ");
      // CompositeSerial.print(KeyPad.fn.velocity);
      // CompositeSerial.print(" ");
      // CompositeSerial.print(KeyPad.fn.activeTime);
      // CompositeSerial.print(" ");
      // CompositeSerial.print(KeyPad.fn.hold);
      // CompositeSerial.print(" ");
      // CompositeSerial.println(KeyPad.fn.holdTime());
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
  bool konami = false;

  for(int i = 0; i < MULTIPRESS; i++)
  {
    if(KeyPad.changelist[i] == 0xFFFF)
    break;

    u8 x = xytox(KeyPad.changelist[i]);
    u8 y = xytoy(KeyPad.changelist[i]);

    //hadAction = true;

    #ifdef DEBUG
    CompositeSerial.print("FN Key Action ");
    CompositeSerial.print(KeyPad.changelist[i]);
    #endif

    if(KeyPad.getKey(KeyPad.changelist[i]).state == RELEASED){
      if(y > 5)
      {
        Midi.sentNoteOff(0, fn_keymap[current_keymap][y - 6][x], 0);
      }
      konami = true; //So off don't reset it.
    }

    if(KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
    {
      #ifdef DEBUG
      CompositeSerial.print("ReadKey ");
      CompositeSerial.println(KeyPad.changelist[i], HEX);
      #endif

      if(y > 5)
      {
        Midi.sentNoteOn(0, fn_keymap[current_keymap][y - 6][x], KeyPad.getKey(KeyPad.changelist[i]).velocity * 127);
        break;
      }

      switch(KeyPad.changelist[i])
      {
        //Brightness
        case 0x33:
        case 0x34:
        case 0x43:
        case 0x44:
        if(!KeyPad.fn.velocity || KeyPad.fn.hold)
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
        if(konami_progress < 2)
        {
          konami_progress++;
          konami = true;
        }
        break;
        case 0x53:
        case 0x54:
        if(konami_progress == 5 || konami_progress == 7)
        {
          konami_progress++;
          konami = true;
        }
        else if(!flag_rotated)
        {
          LED.fill(0, true);
          rotationCW(1); //90
          flag_rotated = true;
        }
        break;
        case 0x35:
        case 0x45:
        if(konami_progress == 2 || konami_progress == 3)
        {
          konami_progress++;
          konami = true;
        }
        else if(!flag_rotated)
        {
          LED.fill(0, true);
          rotationCW(2); //190
          flag_rotated = true;
        }
        break;
        case 0x23:
        case 0x24:
        if(konami_progress == 4 || konami_progress == 6)
        {
          konami_progress++;
          konami = true;
        }
        else if(!flag_rotated)
        {
          LED.fill(0, true);
          rotationCW(3); //270
          flag_rotated = true;
        }
        break;

        case 0x05:
        UI::enterSettingMenu();

        case 0x20:
        setCurrentKeyMap(0);
        break;
        case 0x30:
        setCurrentKeyMap(1);
        break;
        case 0x40:
        setCurrentKeyMap(2);
        break;
        // case 0x40:
        // setCurrentKeyMap(3);
        // break;
        // case 0x50:
        // setCurrentKeyMap(4);
        // break;

        case 0x50:
        setUnipadMode(!unipad_mode);
        if(unipad_mode)
        setCurrentKeyMap(1);
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

        // case 0x60:
        // LED.fill(0xFFFF00, true);
        // LED.update();
        // resetDevice();
        // reset();
        // break;

        case 0x75:
        setFnHold(!fn_hold);
        break;
      }

      if(konami_progress >= 8)
      {
        switch(KeyPad.changelist[i])
        {
          case 0x16:
          case 0x17:
          case 0x26:
          case 0x27:
          if(konami_progress == 9)
          {
            konami_progress = 0; //Tetris Entence Point
          }
          break;
          case 0x56:
          case 0x57:
          case 0x66:
          case 0x67:
          if(konami_progress == 8)
          {
            konami_progress++;
            konami = true;
          }
          break;
        }
      }
      else
      {
        switch(KeyPad.changelist[i])
        {


          // case 0x65:
          // setTouchThreshold(UI::numSelector8bit(touch_threshold, 0x004000AA, 0x00FFFFFF, true));
          // resetTouchBar();
          // break;
        }
      }


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

  if(konami == false)
  {
    konami_progress = 0;
  }

  #ifdef DEBUG
  CompositeSerial.print("Konami: ");
  CompositeSerial.println(konami_progress);
  #endif
}

void UI::fnRender()
{
  // #ifdef DEBUG
  // CompositeSerial.println("Render");
  // #endif
  LED.fill(0, true);

  //brightness
  LED.setXYHEX(0x33, 0xFFFFFFFF, true, true);
  LED.setXYHEX(0x34, 0xFFFFFFFF, true, true);
  LED.setXYHEX(0x43, 0xFFFFFFFF, true, true);
  LED.setXYHEX(0x44, 0xFFFFFFFF, true, true);

  //rotation
  LED.setXYHEX(0x32, 0x0000FF00, true, true);
  LED.setXYHEX(0x42, 0x0000FF00, true, true);
  LED.setXYHEX(0x53, toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);
  LED.setXYHEX(0x54, toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);
  LED.setXYHEX(0x23, toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);
  LED.setXYHEX(0x24, toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);
  LED.setXYHEX(0x35, toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);
  LED.setXYHEX(0x45, toBrightness(0x0000FF00, LOWSTATEBRIGHTNESS), true, true);

  //Menu
  LED.setXYHEX(0x05, 0xFFFFFFFF, true, true);

  // //Midi enable0x
  // if(midi_enable)
  // {
  //   LED.setXYHEX(0x00, 0x00FFAA00, true);
  // }
  // else
  // {
  //   LED.setXYHEX(0x00, toBrightness(0x00FFFFFF, LOWSTATEBRIGHTNESS), true);
  // }
  //
  // //M2P enable
  // if(m2p_enable)
  // {
  //   LED.setXYHEX(0x01, 0x0000FF7F, true);
  // }
  // else
  // {
  //   LED.setXYHEX(0x01, toBrightness(0x0000FF7F, LOWSTATEBRIGHTNESS), true);
  // }
  //
  // //Powercord enable
  // if(powercord_enable)
  // {
  //   LED.setXYHEX(0x67, 0x00D400FF, true);
  // }
  // else
  // {
  //   LED.setXYHEX(0x67, toBrightness(0x00D400FF, LOWSTATEBRIGHTNESS), true);
  // }


  //Extra
  // LED.setXYHEX(0x77, 0x00FFFFFF, true); //Setting
  // LED.setXYHEX(0x07, 0x00FFFFFF, true); //AppLauncher
  // LED.setXYHEX(0x17, 0x00FFFFFF, true); //Text Selctor
  //LED.setXYHEX(0x65, 0x004000FF, true, true); //TouchBar_threshold
  //LED.setXYHEX(0x60, 0x00FFFF00, true, true); //reset device
  //LED.setXYHEX(0x61, 0x0000FF66, true, true); //reboot

  LED.setXYHEX(0x20, toBrightness(keymap_colour[0], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  LED.setXYHEX(0x30, toBrightness(keymap_colour[1], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  LED.setXYHEX(0x40, toBrightness(keymap_colour[2], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  //LED.setXYHEX(0x40, toBrightness(keymap_colour[3], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  //LED.setXYHEX(0x50, toBrightness(keymap_colour[4], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  if(unipad_mode)
  {
    LED.setXYHEX(0x50, 0xFFFF00, true, true);
  }
  else
  {
    LED.setXYHEX(0x50, toBrightness(0xFFFF00, LOWSTATEBRIGHTNESS), true, true);
  }

  if(fn_hold)
  {
    LED.setXYHEX(0x75, 0xA0FF00, true, true);
  }
  else
  {
    LED.setXYHEX(0x75, toBrightness(0xA0FF00, LOWSTATEBRIGHTNESS), true, true);
  }

  switch(current_keymap)
  {
    case 0:
    LED.setXYHEX(0x20, keymap_colour[0], true, true);
    break;
    case 1:
    LED.setXYHEX(0x30, keymap_colour[1], true, true);
    break;
    case 2:
    LED.setXYHEX(0x40, keymap_colour[2], true, true);
    break;
    // case 3:
    // LED.setXYHEX(0x40, keymap_colour[3], true, true);
    // break;
    // case 4:
    // LED.setXYHEX(0x50, keymap_colour[4], true, true);
    // break;
  }

  if(konami_progress >= 8)
  {
    LED.setXYHEX(0x16, 0xFF0000, true, true);
    LED.setXYHEX(0x17, 0xFF0000, true, true);
    LED.setXYHEX(0x26, 0xFF0000, true, true);
    LED.setXYHEX(0x27, 0xFF0000, true, true);
    LED.setXYHEX(0x56, 0xFF0000, true, true);
    LED.setXYHEX(0x57, 0xFF0000, true, true);
    LED.setXYHEX(0x66, 0xFF0000, true, true);
    LED.setXYHEX(0x67, 0xFF0000, true, true);
  }
  else
  {
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
  }
  // #ifdef DEBUG
  // CompositeSerial.println("End Render");
  // #endif

  LED.update();
}

void UI::enterSettingMenu()
{
  LED.fill(0, true);
  LED.update();
  UI::settingMenu();
}

void UI::settingMenu()
{
  UI::settingRender();
  while(1)
  {
    Midi.poll();

    if(uiTimer.tick(1000/fps))
    {
      if(KeyPad.scan())
      {
        if(KeyPad.fn.state == PRESSED)
        {
          UI::exitSettingMenu();
          return;
        }
        UI::settingKeyAction();
        UI::settingRender();
      }
    }
  }
}

void UI::exitSettingMenu()
{
}


void UI::settingKeyAction()
{
  for(int i = 0; i < MULTIPRESS; i++)
  {
    if(KeyPad.changelist[i] == 0xFFFF)
    return;

    u8 x = xytox(KeyPad.changelist[i]);
    u8 y = xytoy(KeyPad.changelist[i]);

    if(KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
    {
      switch(KeyPad.changelist[i])
      {
        case 0x07: //DFU
        enterBootloader();
        break;
        // case 0x67:
        // LED.setColourCorrection(0xFFFFFF);
        // setLedCorrection(UI::numSelectorRGB(led_color_correction, true));
        // break;
        case 0x77:
        setDeviceID(UI::numSelector8bit(device_id, 0x0000FFAA, 0x00FFFFFF, true));
        break;
      }
    }
  }
}

void UI::settingRender()
{
  LED.setXYHEX(0x07, 0x00FF0000, true, true); //DFU
  //LED.setXYHEX(0x67, 0x00FFFFFF, true, true); //White
  LED.setXYHEX(0x77, 0x0000FFAA, true, true); //Device ID
  LED.update();
}


u8 UI::numSelector8bit(u8 currentNum, u32 colour, u32 sec_colour, bool ignore_gamma /* = false */)
{
  // LED.fill(0, true);
  while(!KeyPad.fn.state == PRESSED)
  {
    if(uiTimer.tick(1000/fps))
    {
      if(KeyPad.scan())
      {
        LED.fill(0, true);
        currentNum = uielement.binary8bitInput(currentNum, 7, colour, ignore_gamma);
        currentNum = uielement.simple8bitInput(currentNum, 6, colour, ignore_gamma);
        uielement.renderHalfHeightNum(currentNum, 0x73, colour, sec_colour, ignore_gamma);
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

u8 UI::numSelector6bit(u8 currentNum, u32 colour, u32 sec_colour, bool ignore_gamma /* = false */)
{
  return 0;
}

u32 UI::numSelectorRGB(u32 colour, bool ignore_gamma /* = false */)
{
  LED.fill(0, true);
  u8 R = (colour & 0xFF0000) >> 16;
  u8 G = (colour & 0xFF00) >> 8;
  u8 B = colour & 0xFF;
  uielement.renderHalfHeightNum(R, 0x73, colour, 0xFF0000, ignore_gamma);
  while(!KeyPad.fn.state == PRESSED)
  {
    if(KeyPad.scan())
    {
      if(R != uielement.simple8bitInput(R, 5, 0xFF0000, ignore_gamma))
      {
        LED.fill(0, true);
        R = uielement.simple8bitInput(R, 5, 0xFF0000, ignore_gamma);
        colour = (R << 16) + (colour & 0x00FFFF);
        uielement.renderHalfHeightNum(R, 0x73, colour, 0xFF0000, ignore_gamma);
      }
      else if(G != uielement.binary8bitInput(G, 6, 0x00FF00, ignore_gamma))
      {
        LED.fill(0, true);
        G = uielement.simple8bitInput(G, 6, 0x00FF00, ignore_gamma);
        colour = (G << 8) + (colour & 0xFF00FF);
        uielement.renderHalfHeightNum(G, 0x73, colour, 0x00FF00, ignore_gamma);
      }
      else if(B != uielement.binary8bitInput(B, 7, 0x0000FF, ignore_gamma))
      {
        LED.fill(0, true);
        B = uielement.simple8bitInput(B, 7, 0x0000FF, ignore_gamma);
        colour = B + (colour & 0xFFFF00);
        uielement.renderHalfHeightNum(B, 0x73, colour, 0x0000FF, ignore_gamma);
      }

      uielement.simple8bitInput(R, 5, 0xFF0000, ignore_gamma);
      uielement.simple8bitInput(G, 6, 0x00FF00, ignore_gamma);
      uielement.simple8bitInput(B, 7, 0x0000FF, ignore_gamma);

      LED.update();

      #ifdef DEBUG
      CompositeSerial.print("RGB Update");CompositeSerial.print(" ");
      CompositeSerial.print(R);CompositeSerial.print(" ");
      CompositeSerial.print(G);CompositeSerial.print(" ");
      CompositeSerial.print(B);CompositeSerial.print(" ");
      CompositeSerial.print(colour, HEX);CompositeSerial.println(" ");
      #endif
    }
  }
  LED.fill(0, true);
  return colour;
}

// u32 UI::numSelectorWRGB(u32 colour, bool ignore_gamma /* = false */)
// {
//
// }
//
// void UI::showDeviceInfo()
// {
//
// }
//
// void UI::showASCII(char ascii[], u32 colour, bool ignore_gamma /* = false */)
// {
//
// }
//
// void UI::playAnimation(char animation[])
// {
//
// }

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
