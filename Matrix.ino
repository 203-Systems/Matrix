/*
Project Matrix
Copyright © 203 Industries 2016–2020. All rights reserved.
*/

#include <Arduino.h>
#include <USBComposite.h>
#include <FastLED.h>
#include "src/Parameter/MatrixVariable.h"
#include "src/Parameter/MatrixParameter.h"
#include "src/Core/MatrixSystem.h"
#include "src/Core/MatrixSystem.h"
#include "src/HAL/KeyPad.h"
#include "src/HAL/LED.h"
#include "src/HAL/Timer.h"
#include "src/Protocol/MIDI.h"
#include "src/Components/UI.h"

UI UI;
MIDI Midi;
LED LED;
KeyPad KeyPad;
Timer mainTimer;
MicroTimer microTimer;
USBCompositeSerial CompositeSerial;

bool flag_leftFN = false;

void setup()
{
  //loadDeviceSerialNumber();
  loadDeviceConfig();
  setupEEPROM();
  variableLoad();
  setupUSB();
  setupHardware();
  setupPalette();
  specialBoot();

  UI.enterBootAnimation();

#ifdef DEBUG
  CompositeSerial.println("Enter Main Program");
#endif
}

void readKey()
{
  if (KeyPad.scan())
  {
    if (fn_hold)
    {
      if (KeyPad.fn.hold && !flag_leftFN)
      {
        Midi.sendNoteOff(0, keymap_fn[current_keymap], 0);
        UI.enterFNmenu();
        flag_leftFN = true; //Prevent back to FN
      }
      else if (KeyPad.fn.state == PRESSED)
      {
        Midi.sendNoteOn(0, keymap_fn[current_keymap], 127);
      }
      else if (KeyPad.fn.state == RELEASED)
      {
        Midi.sendNoteOff(0, keymap_fn[current_keymap], 0);
        flag_leftFN = false;
      }
    }
    else
    {
      if (KeyPad.fn.state == PRESSED)
        UI.enterFNmenu();
    }

    for (int i = 0; i < MULTIPRESS; i++)
    {
      if (KeyPad.changelist[i] == 0xFFFF)
        return;
      u8 x = xytox(KeyPad.changelist[i]);
      u8 y = xytoy(KeyPad.changelist[i]);
      if (KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
      {
        Midi.sendXYon(KeyPad.changelist[i], KeyPad.getKey(KeyPad.changelist[i]).velocity * 127);
      }
      else if (KeyPad.getKey(KeyPad.changelist[i]).state == RELEASED)
      {
        Midi.sendXYoff(KeyPad.changelist[i], 0);
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
//         Midi.sendNoteOn(0, touch_keymap[current_keymap][x], 127);
//         break;
//
//         case RELEASED:
//         Midi.sendNoteOff(0, touch_keymap[current_keymap][x], 0);
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
//               LED.setXYCRGB(KeyPad.list[i].xy, testcolor[i]);
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
