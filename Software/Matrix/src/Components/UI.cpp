#include "UI.h"

#define DEBUG //CDC info

extern KeyPad KeyPad;
extern LED LED;
extern MIDI Midi;

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
    return;

    if(KeyPad.list[i].velocity == 0){
      if(xytoxy(KeyPad.list[i].xy).x > 5)
      {
        Midi.noteOff(0, fn_keymap[current_keymap][xytoxy(KeyPad.list[i].xy).y - 6][xytoxy(KeyPad.list[i].xy).x], 0);
      }
    }

    if(KeyPad.list[i].velocity != 0)
    {
      #ifdef DEBUG
      CompositeSerial.print("ReadKey ");
      CompositeSerial.println(KeyPad.list[i].xy, HEX);
      #endif
      if(xytoxy(KeyPad.list[i].xy).x > 5)
      {
        Midi.noteOn(0, fn_keymap[current_keymap][xytoxy(KeyPad.list[i].xy).y - 6][xytoxy(KeyPad.list[i].xy).x], 127);
      }
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

        case 0x00:
        case 0x01: //due to
        setCurrentKeyMap(0);
        break;
        case 0x10:
        case 0x11:
        setCurrentKeyMap(1);
        break;
        case 0x20:
        case 0x21:
        setCurrentKeyMap(2);
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

        case 0x60:
        LED.fill(0xFFFF00, true);
        LED.update();
        resetDevice();
        break;

        case 0x71:
        setDeviceID(UI::numSelector8bit(device_id, 0x00FFAA, true));
        break;

        case 0x61:
        LED.fill(0, true);
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


  //gamma enable
  if(gamma_enable)
  {
    LED.setXYHEX(0x76, 0x00FFFFFF, true, true);
  }
  else
  {
    LED.setXYHEX(0x76, LED.toBrightness(0x00FFFFFF, LOWSTATEBRIGHTNESS), true, true);
  }

  //Extra
  // LED.setXYHEX(0x77, 0x00FFFFFF, true); //Setting
  // LED.setXYHEX(0x07, 0x00FFFFFF, true); //AppLauncher
  // LED.setXYHEX(0x17, 0x00FFFFFF, true); //Text Selctor
  LED.setXYHEX(0x70, 0x00FF0000, true, true); //DFU
  LED.setXYHEX(0x71, 0x0000FFAA, true, true); //Device ID
  LED.setXYHEX(0x60, 0x00FFFF00, true, true); //reset device
  LED.setXYHEX(0x61, 0x0000FF66, true, true); //reboot

  LED.setXYHEX(0x00, LED.toBrightness(keymap_colour[0], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  LED.setXYHEX(0x10, LED.toBrightness(keymap_colour[1], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1
  LED.setXYHEX(0x20, LED.toBrightness(keymap_colour[2], LOWSTATEBRIGHTNESS), true, true); //Keymap selector 1

  switch(current_keymap)
  {
    case 0:
    LED.setXYHEX(0x00, keymap_colour[0], true, true);
    break;
    case 1:
    LED.setXYHEX(0x10, keymap_colour[1], true, true);
    break;
    case 2:
    LED.setXYHEX(0x20, keymap_colour[2], true, true);
    break;
    default:
    LED.setXYHEX(0x01, 0xFF0000, true, true);
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
    if(uiTimer.tick(1000/FPS))
    {
      if(KeyPad.scan())
      {
        LED.fill(0, true);
        currentNum = UI::binary8bitInput(currentNum, 7, colour, ignore_gamma);
        UI::renderHalfHeightNum(currentNum, 0x73, colour, ignore_gamma);
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

void UI::renderText(char ascii[], u8 xy, u8 speed, u32 colour, bool ignore_gamma /* = false */)
{
  u8 current = 0;
  u8 numOfChar;
  u8 space = 2;
  u8 firstX = font[ascii[0]][0] + XSIZE - 2;
  u8 lastX;

  while(current > sizeof(ascii))
  {
    if(ascii[current] < 32)
    {
      speed = ascii[current];
    }
    else
    {
      renderAscii(ascii[current], xytoxy(firstX, 7), colour, ignore_gamma);
    }

    lastX = firstX;
    numOfChar = 1;

    while(lastX < XSIZE - space - 2)
    {
      //lastX = lastX + space +
    }
  }
  firstX--;
  while(uiTimer.tick(speed*2));
}

void UI::renderAscii(char ascii, u8 xy, u32 colour, bool ignore_gamma /* = false */) //XY is the bottom right location
{
  XY nxy = xytoxy(xy);

  if(ascii < 32 || ascii > 127)
  return;

  for(u8 x = 0; x < font[ascii - 32][0]; x++)
  {
    if(nxy.x - x <= 0)
    {
      for(u8 y = 0; y < 8; y++)
      {
        if(nxy.y - y <= 0)
        {
          if(bitRead(font[ascii - 32][font[ascii - 32][0] - x], 7 - y))
          LED.setXYHEX(xytoxy(nxy.x - x, nxy.y - y), colour, true, ignore_gamma);
        }
      }
    }
  }
}

void UI::renderHalfHeightNum(u8 num, u8 xy, u32 colour, bool ignore_gamma /* = false */)
{
  //LED.fillRegionOff(0x00, 0x73, true);
  if(num > 99)
  UI::renderHalfHeightDigit(num / 100, 0x13, colour, ignore_gamma);

  if(num > 9)
  UI::renderHalfHeightDigit(num % 100 / 10 , 0x43, 0x00FFFFFF, ignore_gamma);

  UI::renderHalfHeightDigit(num % 10, 0x73, colour, ignore_gamma);
}

void UI::renderHalfHeightDigit(u8 num, u8 xy, u32 colour, bool ignore_gamma /* = false */) //XY is the bottom right location
{
  s8 x = (xy & 0xF0) >> 4;
  for(s8 xi = 2; xi >= 0; xi--)
  {
    if(x == -1 && x == XSIZE)
    break;
    s8 y = (xy & 0x0F);
    for(s8 yi = 0; yi < 4; yi++)
    {
      if(y == -1 && y == YSIZE)
      break;

      LED.setXYHEX(xytoxy(x, y), colour * bitRead(half_height_num_font[num][xi], yi), true, ignore_gamma);
      y--;
    }
    x--;
  }
}

u8 UI::binary8bitInput(u8 currentNum, u8 y, u32 colour, bool ignore_gamma /* = false */)
{
  for(int x = 0; x < 8; x++)
  {
    if(KeyPad.checkXY(x, y))
    bitWrite(currentNum, 7 - x, !bitRead(currentNum, 7 - x));
    if(bitRead(currentNum, 7 - x))
    {
      LED.setXYHEX(xytoxy(x, y), colour, true, ignore_gamma);
    }
    else
    {
      LED.setXYHEX(xytoxy(x, y), LED.toBrightness(colour, LOWSTATEBRIGHTNESS), true, ignore_gamma);
    }
  }
  return currentNum;
}

void UI::kBootAnimation() //8x8 only
{
  LED.enableOverlayMode();
  //StageOne
  u16 delay = 60;
  for(s8 y = 7; y >= 0; y--)
  {
    for(u8 x = 0; x < 8; x++)
    {
      while(!uiTimer.isLonger(delay))
      {
        KeyPad.scan();
        if(KeyPad.fnChanged)
        {
          if(!KeyPad.fn)
          {
            LED.disableOverlayMode();
            return;
          }
        }
      }
      uiTimer.recordCurrent();
      LED.onXY(xytoxy(x, y), true);
      LED.update();
    }
    delay *= 0.8;
  }

  // uiTimer.recordCurrent();
  // while(!uiTimer.isLonger(30))
  // {
  //   KeyPad.scan();
  //   if(KeyPad.fnChanged)
  //   {
  //     if(!KeyPad.fn)
  //     {
  //       LED.disableOverlayMode();
  //       return;
  //     }
  //   }
  // }

  //Stage2
  delay = 25;

  //shuffle the array
  u8 shuffle[NUM_LEDS];
  for(u8 i = 0; i < NUM_LEDS; i++)
  {
    shuffle[i] = i;
  }
  randomSeed(analogRead(PC3) * analogRead(PC4) * analogRead(PC5) );
  u8 n = sizeof(shuffle) / sizeof(shuffle[0]);
  for (u8 i = 0; i < n - 1; i++)
  {
    u8 j = random(0, n - i);
    u8 t = shuffle[i];
    shuffle[i] = shuffle[j];
    shuffle[j] = t;
  }

  for(int i = 0; i <NUM_LEDS+5; i++)
  {
    while(!uiTimer.isLonger(delay))
    {
      KeyPad.scan();
      if(KeyPad.fnChanged)
      {
        if(!KeyPad.fn)
        {
          LED.disableOverlayMode();
          return;
        }
      }
    }
    uiTimer.recordCurrent();
    if(i < NUM_LEDS)
    LED.setPalette(shuffle[i], 0, 44, true);
    if(i > 0 && i < NUM_LEDS + 1)
    LED.setPalette(shuffle[i-1], 0, 28, true);
    if(i > 1 && i < NUM_LEDS + 2)
    LED.setPalette(shuffle[i-2], 0, 12, true);
    if(i > 2 && i < NUM_LEDS + 3)
    LED.setPalette(shuffle[i-3], 0, 116, true);
    if(i > 3 && i < NUM_LEDS + 4)
    LED.setPalette(shuffle[i-4], 0, 102, true);
    if(i > 4 && i < NUM_LEDS + 5)
    LED.off(shuffle[i-5], true);
    LED.update();
  }
  //end
  LED.disableOverlayMode();
  return;
}
