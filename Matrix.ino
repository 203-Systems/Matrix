/*
Project Matrix
Copyright © 203 Industries 2017–2019. All rights reserved.

TODO
EEPROM load KeyMap
Play Animation
Play Midi
NexusRevamped while USB unreconized

*/

#include <Arduino.h>
#include <USBMIDI.h>
#include <USBComposite.h>
#include <FastLED.h>
#include "src/Parameter/MatrixVariable.h"
#include "src/Parameter/MatrixParameter.h"
#include "src/Core/MatrixSystem.h"
//#include "../Serials.h"
#include "src/Core/MatrixSystem.h"
#include "src/HAL/KeyPad.h"
#include "src/HAL/LED.h"
#include "src/HAL/Timer.h"
//#include "src/HAL/ADCTouch.h"
//#include "src/Protocol/USBmidi.h"
#include "src/Protocol/MIDI.h"
//#include "src/protocol/M2P.h"
#include "src/Components/UI.h"

UI UI;
//UIelement uielement;
MIDI Midi;
LED LED;
KeyPad KeyPad;
//ADCTouch TouchBar;
Timer mainTimer;
Timer keypadTimer;
MicroTimer microTimer;
//bool scanKeypad = true;
bool flag_leftFN = false;

void setup()
{
  setupUSB();
  loadDeviceConfig();
  setupEEPROM();
  variableLoad();
  setupHardware();
  specialBoot();

  #ifdef DEBUG
  CompositeSerial.println("Setup Complete");
  #endif

  mainTimer.recordCurrent();
  while(!USBComposite.isReady() && !KeyPad.fn.state == PRESSED)
  {
    KeyPad.scan();
    if (mainTimer.isLonger(9900000))
    {
      LED.setXYHEX(0x07,0xff0000); //NexusRevamped Entence point
      LED.update();
    }
    else
    {
      switch(bootAnimationSelector)
      {
        case 0:
        break;

        case 1:
        UI.kaskobiWaitAnimation();
        break;
      }
    }
  }

  if(!KeyPad.fn.velocity)
  {
    switch(bootAnimationSelector)
    {
      case 0:
      break;

      case 1:
      UI.kaskobiBootAnimation();
      break;
    }
  }

  LED.fill(0x000000);
  LED.update();

  #ifdef DEBUG
  CompositeSerial.println("Enter Main Program");
  #endif
}

void readKey()
{
  if (KeyPad.scan())
  {
    if(fn_hold)
    {
      if(KeyPad.fn.hold && !flag_leftFN)
      {
        Midi.sentNoteOff(0, keymap_fn[current_keymap]);
        UI.enterFNmenu();
        flag_leftFN = true; //Prevent back to FN
      }
      else if(KeyPad.fn.state == PRESSED)
      {
        Midi.sentNoteOn(0, keymap_fn[current_keymap]);
      }
      else if(KeyPad.fn.state == RELEASED)
      {
        Midi.sentNoteOff(0, keymap_fn[current_keymap]);
        flag_leftFN = false;
      }
    }
    else
    {
      if(KeyPad.fn.state == PRESSED)
      UI.enterFNmenu();
    }

    for(int i = 0; i < MULTIPRESS; i++)
    {
      if(KeyPad.changelist[i] == 0xFFFF)
      return;
      u8 x = xytox(KeyPad.changelist[i]);
      u8 y = xytoy(KeyPad.changelist[i]);
      if(KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
      {
        Midi.sentXYon(KeyPad.changelist[i], KeyPad.getKey(KeyPad.changelist[i]).velocity * 127);
      }
      else if(KeyPad.getKey(KeyPad.changelist[i]).state == RELEASED)
      {
        Midi.sentXYoff(KeyPad.changelist[i], 0);
      }
    }
  }
}
// void readTouch()
// {
//   if(TouchBar.scan())
//   {
//     for(u8 x = 0; x < 8; x++)
//     {
//       switch(TouchBar.changelist[x].kstate)
//       {
//         case IDLE:
//         return;
//
//         case PRESSED:
//         Midi.sentNoteOn(0, touch_keymap[current_keymap][x], 127);
//         break;
//
//         case RELEASED:
//         Midi.sentNoteOff(0, touch_keymap[current_keymap][x], 0);
//         break;
//       }
//     }
//   }
// }

// void factoryTest()
// {
//   u32 testcolor[] = {0xFFFFFF, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF};
//
//   for(int i = 0; i < 6; i ++)
//   {
//     LED.fill(testcolor[i]);
//     LED.update();
//     while(!KeyPad.scan()){}
//
//     while(KeyPad.fnChanged && KeyPad.fn)
//     {
//       if (mainTimer.tick(1000/fps))
//       {
//         KeyPad.scan();
//         for(int i = 0; i < MULTIPRESS; i++)
//         {
//           if(KeyPad.list[i].velocity > 128)
//           break;
//           if(KeyPad.list[i].velocity > 0)
//           {
//             if(LED.readXYLED(KeyPad.list[i].xy) != testcolor[i])
//             {
//               LED.setXYHEX(KeyPad.list[i].xy, testcolor[i]);
//             }
//             else
//             {
//               LED.offXY(KeyPad.list[i].xy);
//             }
//           }
//         }
//         LED.update();
//       }
//     }
//   }
// }

void loop()
{
  Midi.poll();

  // if(LED.changed)
  // {
  //   LED.update();
  //   LED.changed = false;
  // }

  // if (keypadTimer.tick(keypad_scanrate_micros))
  // {
  //   readKey();
  //   //readTouch();
  // }

  if (mainTimer.tick(fps_micros))
  {
    readKey();
    LED.update();
    LED.changed = false;
    Midi.offScan();
    // #ifdef DEBUG
    // microTimer.recordCurrent();
    // #endif
    //LED.update();
    // #ifdef DEBUG
    // CompositeSerial.println(microTimer.sinceLastTick());
    // #endif
  }
}

void specialBoot()
{
  if (KeyPad.scan())
  {
    if(KeyPad.checkXY(0, 5, true) && KeyPad.checkXY(0, 6, true) && KeyPad.checkXY(0, 7, true))
    {
      formatEEPROM();
      LED.fill(0xFF00FF);
    }

    if(KeyPad.checkXY(1, 1, true) && KeyPad.checkXY(0, 0, true))
    {
      factoryTest();
    }

    if(KeyPad.checkXY(7, 0, true))
    {
      setBrightness(16);
    }

    if(KeyPad.checkXY(7, 0, true) && KeyPad.checkXY(6, 1, true))
    {
      setBrightness(255);
    }

  }
}

void factoryTest()
{
  LED.setBrightness(64);
  LED.fill(0);
  LED.update();

  while(KeyPad.fn.state != PRESSED)
  {
    if (mainTimer.tick(1000/fps))
    {
      if(KeyPad.scan())
      {
        for(int i = 0; i < MULTIPRESS; i++)
        {
          u8 x = xytox(KeyPad.changelist[i]);
          u8 y = xytoy(KeyPad.changelist[i]);
          if(KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
          {
            if(LED.readLED(KeyPad.changelist[i]))
            {
              LED.offXY(KeyPad.changelist[i], true);
            }
            else
            {
              LED.setXYHEX(KeyPad.changelist[i], 0xFFFFFF, true, true);
            }
          }
        }
        LED.update();
      }
    }
  }
}
