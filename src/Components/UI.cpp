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
  while (1)
  {
    Midi.poll();

    if (uiTimer.tick(ui_fps_micros))
    {
      if (KeyPad.scan())
      {
#ifdef DEBUG
        CompositeSerial.println("FnMenuKeyScaned");
#endif
        if (KeyPad.fn.state == PRESSED)
        {
          UI::exitFNmenu();
          return;
        }
        else if (KeyPad.fn.state == RELEASED && !fn_hold && (KeyPad.fn.hold || hadAction)) //if fn off and longer then threshold, will count as hold, release to back to main menu
        {
          UI::exitFNmenu();
          return;
        }
        UI::fnKeyAction();
      }
      UI::fnRender();
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

  for (int i = 0; i < MULTIPRESS; i++)
  {
    if (KeyPad.changelist[i] == 0xFFFF)
      break;

    u8 x = xytox(KeyPad.changelist[i]);
    u8 y = xytoy(KeyPad.changelist[i]);

    if (KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED &&
        KeyPad.changelist[i] != 0x33 && //Because it's easy to hit them by accident
        KeyPad.changelist[i] != 0x34 &&
        KeyPad.changelist[i] != 0x43 &&
        KeyPad.changelist[i] != 0x44)
    {
      hadAction = true;
    }

    if (y > 5)
    {
      if (konami_progress >= 8)
      {
        if (KeyPad.getKey(KeyPad.changelist[i]).state == RELEASED)
        {
          switch (KeyPad.changelist[i])
          {
          case 0x16:
          case 0x17:
          case 0x26:
          case 0x27:
            if (konami_progress == 9)
            {
              konami_progress = 0; //Easter egg Entence Point
              // UI::scrollText("Hello there", 0x00FFFF);
              Redacted::run();
            }
            break;
          case 0x56:
          case 0x57:
          case 0x66:
          case 0x67:
            if (konami_progress == 8)
            {
              konami_progress++;
              konami = true;
            }
            break;
          }
        }
        else
        {
          konami = true;
        }
      }
      if (KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
      {
        Midi.sendNoteOn(0, fn_keymap[current_keymap][y - 6][x], KeyPad.getKey(KeyPad.changelist[i]).velocity * 127);
      }
      else if (KeyPad.getKey(KeyPad.changelist[i]).state == RELEASED)
      {
        Midi.sendNoteOff(0, fn_keymap[current_keymap][y - 6][x], 0);
      }
    }
    else
    {
#ifdef DEBUG
      CompositeSerial.print("FN Key Action ");
      CompositeSerial.print(KeyPad.changelist[i]);
#endif
      if (KeyPad.getKey(KeyPad.changelist[i]).state == RELEASED)
      {
        // }
        //
        // if(KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
        // {
        //   #ifdef DEBUG
        //   CompositeSerial.print("ReadKey ");
        //   CompositeSerial.println(KeyPad.changelist[i], HEX);
        //   #endif
        //
        //   if(y > 5)
        //   {
        //     Midi.sendNoteOn(0, fn_keymap[current_keymap][y - 6][x], KeyPad.getKey(KeyPad.changelist[i]).velocity * 127);
        //     break;
        //   }

        switch (KeyPad.changelist[i])
        {
        //Brightness
        case 0x33:
        case 0x34:
        case 0x43:
        case 0x44:
          if (!KeyPad.fn.velocity || KeyPad.fn.hold)
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
          if (konami_progress < 2)
          {
            konami_progress++;
            konami = true;
          }
          break;
        case 0x53:
        case 0x54:
          if (konami_progress == 5 || konami_progress == 7)
          {
            konami_progress++;
            konami = true;
          }
          else if (!flag_rotated)
          {
            LED.fill(0, true);
            rotationCW(1); //90
            flag_rotated = true;
          }
          break;
        case 0x35:
        case 0x45:
          if (konami_progress == 2 || konami_progress == 3)
          {
            konami_progress++;
            konami = true;
          }
          else if (!flag_rotated)
          {
            LED.fill(0, true);
            rotationCW(2); //190
            flag_rotated = true;
          }
          break;
        case 0x23:
        case 0x24:
          if (konami_progress == 4 || konami_progress == 6)
          {
            konami_progress++;
            konami = true;
          }
          else if (!flag_rotated)
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
          if (unipad_mode)
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
      else if (KeyPad.getKey(KeyPad.changelist[i]).state == ACTIVED && KeyPad.getKey(KeyPad.changelist[i]).hold)
      {
        switch (KeyPad.changelist[i])
        {
        //Brightness
        case 0x33:
        case 0x34:
        case 0x43:
        case 0x44:
          // UI::scrollText("Brightness Setting", 0xFFFFFF);
          UI::brightnessControl();
          break;

        //rotation
        case 0x32:
        case 0x42:
          UI::scrollText("Clean Canvas", 0x0000FF00);
          break;

        case 0x53:
        case 0x54:
        case 0x35:
        case 0x45:
        case 0x23:
        case 0x24:
          UI::scrollText("Rotate to this side up", 0x0000FF00);
          break;

        case 0x05:
          UI::scrollText("Setting Menu", 0xFFFFFFFF);
          break;
        case 0x20:
          UI::scrollText("Key Map 1", keymap_color[0]);
          break;
        case 0x30:
          UI::scrollText("Key Map 2", keymap_color[1]);
          break;
        case 0x40:
          UI::scrollText("Custom Key Map (Not available yet)", keymap_color[2]);
          break;
        case 0x50:
          UI::scrollText("Unipad Mode", 0x00FFFF00);
          break;
        case 0x75:
          UI::scrollText("Action Menu Hold Mode", 0x00A0FF00);
          break;
        default:
          UI::scrollText("Action Menu", 0x0000FFAA);
          break;
        }
      }
      else if (KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
      {
        konami = true; //So on don't reset it.
      }
    }
    if (konami == false)
    {
      konami_progress = 0;
    }
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
  LED.setXYCRGB(0x33, 0xFFFFFFFF, true);
  LED.setXYCRGB(0x34, 0xFFFFFFFF, true);
  LED.setXYCRGB(0x43, 0xFFFFFFFF, true);
  LED.setXYCRGB(0x44, 0xFFFFFFFF, true);

  //rotation
  LED.setXYCRGB(0x32, 0x0000FF00, true);
  LED.setXYCRGB(0x42, 0x0000FF00, true);
  LED.setXYCRGB(0x53, toLowBrightness(0x0000FF00), true);
  LED.setXYCRGB(0x54, toLowBrightness(0x0000FF00), true);
  LED.setXYCRGB(0x23, toLowBrightness(0x0000FF00), true);
  LED.setXYCRGB(0x24, toLowBrightness(0x0000FF00), true);
  LED.setXYCRGB(0x35, toLowBrightness(0x0000FF00), true);
  LED.setXYCRGB(0x45, toLowBrightness(0x0000FF00), true);

  //Menu
  LED.setXYCRGB(0x05, 0xFFFFFFFF, true);
#ifdef DEBUG
  LED.setXYCRGB(0x05, 0x00FFA500, true);
#endif

  LED.setXYCRGB(0x20, toLowBrightness(keymap_color[0]), true); //Keymap selector 1
  LED.setXYCRGB(0x30, toLowBrightness(keymap_color[1]), true); //Keymap selector 1
  LED.setXYCRGB(0x40, toLowBrightness(keymap_color[2]), true); //Keymap selector 1
  LED.setXYCRGB(0x50, toLowBrightness(0xFFFF00, unipad_mode), true);

  LED.setXYCRGB(0x75, toLowBrightness(0xA0FF00, fn_hold), true);

  switch (current_keymap)
  {
  case 0:
    LED.setXYCRGB(0x20, keymap_color[0], true);
    break;
  case 1:
    LED.setXYCRGB(0x30, keymap_color[1], true);
    break;
  case 2:
    LED.setXYCRGB(0x40, keymap_color[2], true);
    break;
  }

  if (konami_progress >= 8)
  {
    LED.setXYCRGB(0x16, 0xFF0000, true);
    LED.setXYCRGB(0x17, 0xFF0000, true);
    LED.setXYCRGB(0x26, 0xFF0000, true);
    LED.setXYCRGB(0x27, 0xFF0000, true);
    LED.setXYCRGB(0x56, 0xFF0000, true);
    LED.setXYCRGB(0x57, 0xFF0000, true);
    LED.setXYCRGB(0x66, 0xFF0000, true);
    LED.setXYCRGB(0x67, 0xFF0000, true);
  }
  else
  {
    for (u8 y = 6; y < 8; y++)
    {
      for (u8 x = 0; x < 8; x++)
      {
        if (KeyPad.checkXY(x, y))
        {
          LED.setXYCRGB(xytoxy(x, y), fn_keymap_active_color[current_keymap][y - 6][x], true);
        }
        else
        {
          LED.setXYCRGB(xytoxy(x, y), fn_keymap_idle_color[current_keymap][y - 6][x], true);
        }
      }
    }
  }
#ifdef DEBUG
  CompositeSerial.println("End Fn Render");
#endif

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
  while (1)
  {
    Midi.poll();

    if (uiTimer.tick(ui_fps_micros))
    {
      if (KeyPad.scan())
      {
        if (KeyPad.fn.state == RELEASED)
        {
          UI::exitSettingMenu();
          return;
        }
        UI::settingKeyAction();
      }
      UI::settingRender();
    }
  }
}

void UI::exitSettingMenu()
{
}

void UI::settingKeyAction()
{
  for (int i = 0; i < MULTIPRESS; i++)
  {
    if (KeyPad.changelist[i] == 0xFFFF)
      return;

    u8 x = xytox(KeyPad.changelist[i]);
    u8 y = xytoy(KeyPad.changelist[i]);

    char char_buffer[64];

    if (KeyPad.getKey(KeyPad.changelist[i]).state == RELEASED)
    {
      switch (KeyPad.changelist[i])
      {
      case 0x00:
        switch (stfu)
        {
        case 0:
          setSTFU(1);
          break;
        case 1:
          setSTFU(2);
          break;
        case 2:
        default:
          setSTFU(0);
          break;
        }
        break;
      case 0x10:
        setDesaturatedMode(!desaturated_mode);
        break;
      case 0x20:
        setProInputMode(!pro_input_mode);
        break;
      case 0x01:
        setTouchEnable(!touch_enable);
        break;
      case 0x06:
        UI::clearEEPROM();
        break;
      case 0x07: //DFU
        enterBootloader();
        break;
      case 0x17:
      {
        String fw_str = "Matrix OS V" + String(FWVERSION_STRING);
        fw_str.toCharArray(char_buffer, 64);
        UI::scrollText(char_buffer, 0x00FF30);
        break;
      }
      case 0x27:
      {
        u32 bl_ver = BOOTLOADER_VERSION;
        String bl_str = "Matrix Bootloader V" + (String)(bl_ver / 100) + '.' + (String)((bl_ver / 10) % 10) + '.' + (String)(bl_ver % 10);
        bl_str.toCharArray(char_buffer, 64);
        UI::scrollText(char_buffer, 0x00FF30);
        break;
      }
      case 0x37:
      {
        device_name.toCharArray(char_buffer, 64);
        UI::scrollText(char_buffer, 0x00FF30);
        break;
      }
      case 0x67:
      {
        u32 origonal_color_correction = led_color_correction;
        bool origonal_desaturated_mode = desaturated_mode;
        desaturated_mode = false; //use setDesaturatedMode() will cause setupPalette() to be called, it will be called in setColorCorrection()
        setColorCorrection(0xFFFFFF, true);

        u32 new_color_correction = UI::numSelectorRGB(origonal_color_correction);

        if (new_color_correction != origonal_color_correction)
        {
          LED.fill(0, true);
          LED.update();
          desaturated_mode = origonal_desaturated_mode;
          setColorCorrection(new_color_correction);
        }
        else
        {
          desaturated_mode = origonal_desaturated_mode;
          setColorCorrection(origonal_color_correction, true);
        }
        break;
      }
      case 0x77:
        setDeviceID(UI::numSelector8bit(device_id, 0x0000FFAA, 0x00FFFFFF));
        break;
      }
    }
    else if (KeyPad.getKey(KeyPad.changelist[i]).state == ACTIVED && KeyPad.getKey(KeyPad.changelist[i]).hold)
    {
      switch (KeyPad.changelist[i])
      {
      case 0x00:
        switch (stfu)
        {
        case 0:
          UI::scrollText("Flicker Optimization Off", 0xA0A0A0);
          break;
        case 1:
          UI::scrollText("Flicker Optimization Level 1", 0xAAFF00);
          break;
        case 2:
          UI::scrollText("Flicker Optimization Level 2", 0xAAFF00);
          break;
        defalut:
          UI::scrollText("Flicker Optimization Level ???", 0xFF0000);
          break;
        }
        break;

      case 0x10:
        UI::scrollText("Desaturated Mode", 0x33FFBD);
        break;
      case 0x20:
        UI::scrollText("Pro Input Mode", 0x00FF00);
        break;
      case 0x01:
        if(touch_enable)
        {
          UI::scrollText("Touchbar Enabled", 0x7957FB);
        }
        else
        {
          UI::scrollText("Touchbar Disabled", 0x7957FB);
        }
        break;
      case 0x06:
        UI::scrollText("Clear Device Config", 0xFF00FF);
        break;
      case 0x07: //DFU
        UI::scrollText("Enter DFU Mode", 0xFF0000);
        break;
      case 0x17:
        UI::scrollText("Device Firmware Version", 0x00FF30);
        break;
      case 0x27:
        UI::scrollText("Device Bootloader Version", 0x00FF30);
        break;
      case 0x37:
        UI::scrollText("Device Name", 0x00FF30);
        break;
      case 0x67:
        UI::scrollText("color Correction", 0xFFFFFF);
        break;
      case 0x77:
        UI::scrollText("Device ID", 0x00FFAA);
        break;
      default:
        UI::scrollText("Setting Menu", 0x00FFFFFF);
        break;
      }
    }
  }
}

void UI::settingRender()
{
  switch (stfu)
  {
  case 0:
    LED.setXYCRGB(0x00, 0x00202020, true); //STFU Off
    break;
  case 1:
    LED.setXYCRGB(0x00, toLowBrightness(0x00AAFF00), true); //STFU 1
    break;
  case 2:
    LED.setXYCRGB(0x00, 0x00AAFF00, true); //STFU 2
    break;
  default:
    LED.setXYCRGB(0x00, 0x00FF0000, true); //STFU ???
  }

  LED.setXYCRGB(0x10, 0x0033FFBD, true);                                  //Desaturated Mode
  LED.setXYCRGB(0x20, toLowBrightness(0x0000FF00, pro_input_mode), true); //Pro Input Mode
  LED.setXYCRGB(0x06, 0x00FF00FF, true);                                  //Reset EEPROM
  LED.setXYCRGB(0x07, 0x00FF0000, true);                                  //DFU

  LED.setXYCRGB(0x01, toLowBrightness(0x007957FB, touch_enable), true); //Pro Input Mode


  if (BUILD_VER == 0)
  {
    LED.setXYCRGB(0x17, 0x0000FF30, true); //OS Version
  }
  else
  {
    LED.setXYCRGB(0x17, 0x00FFA500, true); //OS Version color change with Beta version is installed
  }

  LED.setXYCRGB(0x27, 0x0000FF30, true); //Bootloader Info
  LED.setXYCRGB(0x37, 0x0000FF30, true); //Device Name
  LED.setXYCRGB(0x67, 0x00FFFFFF, true); //color Correction
  LED.setXYCRGB(0x77, 0x0000FFAA, true); //Device ID
  LED.update();
}

u8 UI::numSelector8bit(u8 currentNum, u32 color, u32 sec_color)
{
  LED.fill(0, true);

  auto target8bitInput = &UIelement::simple8bitInput;
  if (pro_input_mode)
  {
    target8bitInput = &UIelement::binary8bitInput;
  }

  bool initalized = false;
  while (true)
  {
    if (uiTimer.tick(ui_fps_micros) && KeyPad.scan() || !initalized)
    {
      if (!initalized)
        initalized = true;
      if (KeyPad.fn.state == RELEASED)
      {
        LED.fill(0, true);
        return currentNum;
      }
      
      if(currentNum != (&uielement->*target8bitInput)(currentNum, 7, color))
      {
        LED.fill(0, true);
        currentNum = (&uielement->*target8bitInput)(currentNum, 7, color);
        uielement.renderHalfHeightNum(currentNum, 0x73, color, sec_color);
#ifdef DEBUG
        CompositeSerial.print("numSelector\t");
        CompositeSerial.println(currentNum);
#endif
        LED.update();
      }
    }
  }
}

u8 UI::numSelector6bit(u8 currentNum, u32 color, u32 sec_color)
{
  return 0;
}

u32 UI::numSelectorRGB(u32 color)
{
#ifdef DEBUG
  CompositeSerial.println("RGB Input mode");
#endif
  bool initalized = false;
  LED.fill(0, true);
  u8 R = (color & 0xFF0000) >> 16;
  u8 G = (color & 0xFF00) >> 8;
  u8 B = color & 0xFF;
  uielement.renderHalfHeightNum(R, 0x73, color, 0xFF0000);

  auto target8bitInput = &UIelement::simple8bitInput;
  if (pro_input_mode)
  {
    target8bitInput = &UIelement::binary8bitInput;
  }
  
  while (true)
  {
    if (uiTimer.tick(ui_fps_micros) && KeyPad.scan() || !initalized)
    {
      if (!initalized)
        initalized = true;
      if (KeyPad.fn.state == RELEASED)
      {
        LED.fill(0, true);
        return color;
      }
      if (R != (&uielement->*target8bitInput)(R, 5, 0xFF0000))
      {
        LED.fill(0, true);
        R = (&uielement->*target8bitInput)(R, 5, 0xFF0000);
        color = (R << 16) + (color & 0x00FFFF);
        uielement.renderHalfHeightNum(R, 0x73, color, 0xFF0000);
      }
      else if (G != (&uielement->*target8bitInput)(G, 6, 0x00FF00))
      {
        LED.fill(0, true);
        G = (&uielement->*target8bitInput)(G, 6, 0x00FF00);
        color = (G << 8) + (color & 0xFF00FF);
        uielement.renderHalfHeightNum(G, 0x73, color, 0x00FF00);
      }
      else if (B != (&uielement->*target8bitInput)(B, 7, 0x0000FF))
      {
        LED.fill(0, true);
        B = (&uielement->*target8bitInput)(B, 7, 0x0000FF);
        color = B + (color & 0xFFFF00);
        uielement.renderHalfHeightNum(B, 0x73, color, 0x0000FF);
      }

      //Rerender Input
      (&uielement->*target8bitInput)(R, 5, 0xFF0000);
      (&uielement->*target8bitInput)(G, 6, 0x00FF00);
      (&uielement->*target8bitInput)(B, 7, 0x0000FF);

      LED.update();

#ifdef DEBUG
      CompositeSerial.print("RGB Update");
      CompositeSerial.print(" ");
      CompositeSerial.print(R);
      CompositeSerial.print(" ");
      CompositeSerial.print(G);
      CompositeSerial.print(" ");
      CompositeSerial.print(B);
      CompositeSerial.print(" ");
      CompositeSerial.print(color, HEX);
      CompositeSerial.println(" ");
#endif
    }
  }
}

// u32 UI::numSelectorWRGB(u32 color, bool ignore_gamma /* = false */)
// {
//
// }
//
// void UI::showDeviceInfo()
// {
//
// }
//
// void UI::showASCII(char ascii[], u32 color, bool ignore_gamma /* = false */)
// {
//
// }
//
// void UI::playAnimation(char animation[])
// {
//
// }

void UI::scrollText(char ascii[], CRGB color, u8 speed /* = 10 */, bool loop /* = false */, u8 len /* = 0 */)
{

  speed = 1000 / speed;
  u8 spacing = 2;
  u8 spacing_remaining = 0;
  LED.fill(0, true);
  LED.update();
#ifdef DEBUG
  CompositeSerial.print("Text scroll: ");
  CompositeSerial.println(ascii);
  CompositeSerial.print("Text Size: ");
  CompositeSerial.println(strlen(ascii));
#endif

  if (!len)
    len = strlen(ascii);

  do
  {
    u8 current_char = 0;
    while (current_char < len)
    {
      // CompositeSerial.print("Print Char: ");
      // CompositeSerial.println(ascii[current_char]);
      u8 current_char_progress = 0;
      if (ascii[current_char] < 128)
      {
        if (ascii[current_char] < 32)
        {
          speed = ascii[current_char] * 10 + 10;
          // CompositeSerial.print("Speed changed: ");
          // CompositeSerial.println(speed);
          break;
        }
        else
        {
          while (current_char_progress < font[ascii[current_char] - 32][0])
          {
            while (!uiTimer.tick(speed))
            {
              if (KeyPad.scan())
              {
                if (KeyPad.fn.state == PRESSED)
                {
                  LED.fill(0, true);
                  return;
                }
              }
            }
            LED.shift(left, 1);
            if (spacing_remaining)
            {
              spacing_remaining--;
              LED.update();
            }
            else
            {
              for (u8 y = 0; y < 8; y++)
              {
                if (bitRead(font[ascii[current_char] - 32][current_char_progress + 1], 7 - y))
                  LED.setXYCRGB(xytoxy(7, y), color, true);
              }
              LED.update();
              current_char_progress++;
            }
          }
        }
      }
      current_char++;
      spacing_remaining = spacing;
    }
    for (u8 c = 0; c < 8; c++)
    {
      while (!uiTimer.tick(speed))
      {
        if (KeyPad.scan())
        {
          if (KeyPad.fn.state == PRESSED)
          {
            LED.fill(0, true);
            return;
          }
        }
      }
      LED.shift(left, 1);
      LED.update();
    }
  } while (loop);
  LED.fill(0, true);
}

void UI::enterBootAnimation()
{
  uiTimer.recordCurrent();
  while (!USBComposite.isReady() && !KeyPad.fn.hold)
  {
    KeyPad.scan();
    if (uiTimer.isLonger(9900000))
    {
      LED.setXYCRGB(0x07, 0xff0000); //NexusRevamped Entence point
      LED.update();
    }
    else
    {
      switch (bootAnimationSelector)
      {
      case 0:
        break;

      case 1:
        UI::kaskobiWaitAnimation();
        break;
      }
    }
  }

  if (!KeyPad.fn.velocity)
  {
    switch (bootAnimationSelector)
    {
    case 0:
      break;

    case 1:
      UI::kaskobiBootAnimation();
      break;
    }
  }

  LED.fill(0x000000);
  LED.update();
}

void UI::clearEEPROM()
{
  LED.fill(0, true);

  CRGB color = 0x00FF00FF;
  //C
  LED.setXYCRGB(0x00, color, true);
  LED.setXYCRGB(0x10, color, true);
  LED.setXYCRGB(0x20, color, true);
  LED.setXYCRGB(0x01, color, true);
  LED.setXYCRGB(0x02, color, true);
  LED.setXYCRGB(0x03, color, true);
  LED.setXYCRGB(0x13, color, true);
  LED.setXYCRGB(0x23, color, true);

  //L
  LED.onXY(0x30, true);
  LED.onXY(0x31, true);
  LED.onXY(0x32, true);
  LED.onXY(0x33, true);
  LED.onXY(0x43, true);
  //R
  LED.setXYCRGB(0x50, color, true);
  LED.setXYCRGB(0x60, color, true);
  LED.setXYCRGB(0x70, color, true);
  LED.setXYCRGB(0x51, color, true);
  LED.setXYCRGB(0x71, color, true);
  LED.setXYCRGB(0x52, color, true);
  LED.setXYCRGB(0x62, color, true);
  LED.setXYCRGB(0x53, color, true);
  LED.setXYCRGB(0x73, color, true);

  //No Button
  LED.setXYCRGB(0x15, 0xFF0000, true);
  LED.setXYCRGB(0x16, 0xFF0000, true);
  LED.setXYCRGB(0x25, 0xFF0000, true);
  LED.setXYCRGB(0x26, 0xFF0000, true);

  //Yes Button
  LED.setXYCRGB(0x55, 0x00FF00, true);
  LED.setXYCRGB(0x56, 0x00FF00, true);
  LED.setXYCRGB(0x65, 0x00FF00, true);
  LED.setXYCRGB(0x66, 0x00FF00, true);

  LED.update();

  while (true)
  {
    if (uiTimer.tick(ui_fps_micros) && KeyPad.scan())
    {
      if (KeyPad.fn.state == RELEASED)
      {
        LED.fill(0, true);
        return;
      }
      for (int i = 0; i < MULTIPRESS; i++)
      {
        if (KeyPad.changelist[i] == 0xFFFF)
          break;
        if (KeyPad.getKey(KeyPad.changelist[i]).state == RELEASED)
        {
          switch (KeyPad.changelist[i])
          {
          case 0x15:
          case 0x16:
          case 0x25:
          case 0x26:
            LED.fill(0, true);
            return;
          case 0x55:
          case 0x56:
          case 0x65:
          case 0x66:
            formatEEPROM();
            delay(500);
            reboot();
          }
        }
        else if (KeyPad.getKey(KeyPad.changelist[i]).state == ACTIVED && KeyPad.getKey(KeyPad.changelist[i]).hold)
        {
          switch (KeyPad.changelist[i])
          {
          case 0x15:
          case 0x16:
          case 0x25:
          case 0x26:
            UI::scrollText("Cancel", 0xFF0000);
            break;
          case 0x55:
          case 0x56:
          case 0x65:
          case 0x66:
            UI::scrollText("Yes", 0x00FF00);
            break;
          default:
            UI::scrollText("Clear Device Config?", color);
            break;
          }
        }
      }
    }
  }
}

void UI::standbyMode()
{
  bool overlay = LED.getOverlayMode();
  if (!overlay)
    LED.enableOverlayMode();
  LED.fill(0, true);
  LED.update();
  bool keyReleased = false;
  while (!Midi.available() && !keyReleased)
  {
    if (KeyPad.scan())
    {
      for (int i = 0; i < MULTIPRESS; i++)
      {
        if (KeyPad.changelist[i] == 0xFFFF)
          break;
        if (KeyPad.getKey(KeyPad.changelist[i]).state == RELEASED)
        {
          keyReleased = true;
        }
      }
    }
  }
  if (!overlay)
    LED.disableOverlayMode();
  LED.update();
  return;
}

void UI::brightnessControl()
{
  LED.fill(0, true);
  u8 unsafe = 168;
  u8 brightnessList[] = {4, 8, 14, 20, 28, 38, 50, 63, 79, 98, 119, 142, 169, 198, 231, 255}; //Length has to be multiples of 8
  u8 height = sizeof(brightnessList) / 8;// + ((sizeof(brightnessList)) % 8 > 0);
  u8 offset = 8 - height;
  while(true)
  {
    //Text Render
    u32 accent_color = brightness < unsafe ? 0x00FF00 : 0xFF0000;
    //L
    LED.setXYCRGB(0x00, accent_color, true);
    LED.setXYCRGB(0x01, accent_color, true);
    LED.setXYCRGB(0x02, accent_color, true);
    LED.setXYCRGB(0x03, accent_color, true);
    LED.setXYCRGB(0x13, accent_color, true);
    //E
    LED.onXY(0x20, true);
    LED.onXY(0x21, true);
    LED.onXY(0x22, true);
    LED.onXY(0x23, true);
    LED.onXY(0x30, true);
    LED.onXY(0x31, true);
    LED.onXY(0x33, true);
    LED.onXY(0x40, true);
    LED.onXY(0x43, true);
    //D
    LED.setXYCRGB(0x50, accent_color, true);
    LED.setXYCRGB(0x51, accent_color, true);
    LED.setXYCRGB(0x52, accent_color, true);
    LED.setXYCRGB(0x53, accent_color, true);
    LED.setXYCRGB(0x60, accent_color, true);
    LED.setXYCRGB(0x63, accent_color, true);
    LED.setXYCRGB(0x71, accent_color, true);
    LED.setXYCRGB(0x72, accent_color, true);

    //Control Render
      for(u8 y = 0; y < height; y++)
      {
        for(u8 x = 0; x < 8; x++)
        {
          u8 i = y * 8 + x;

          u32 color = 0;
          if(brightnessList[i] >= unsafe)
          {
            color = 0xFF0000;
          }
          else
          {
            color = 0xFFFFFF;
          }
          
          LED.setXYCRGB(xytoxy(x, y + offset), toLowBrightness(color, brightness >= brightnessList[i]), true);
        }
      }
    LED.update();
    //Keypad
    while (true)
    {
      if (uiTimer.tick(ui_fps_micros) && KeyPad.scan())
      {
        if (KeyPad.fn.state == RELEASED)
        {
          LED.fill(0, true);
          return;
        }
        u8 newBrightness = 0;
        for (int i = 0; i < MULTIPRESS; i++)
        {
          if (KeyPad.changelist[i] == 0xFFFF)
            break;
          if (KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
          {
            u8 x = xytox(KeyPad.changelist[i]);
            u8 y = xytoy(KeyPad.changelist[i]);
            if(y >= offset)
            {
              u8 brightnessID = (y-offset) * 8 + x;
              newBrightness = brightnessList[brightnessID];
            }
          }
        }
        if(newBrightness != 0)
        {
          setBrightness(newBrightness);
          break;
        }
      }
    }
  }
}