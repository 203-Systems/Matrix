/*
Project Matrix
Copyright © 203 Industries 2017–2019. All rights reserved.

TODO
EEPROM load KeyMap
EEPROM sys stuff
microsecond timer
Play Animation
Play Midi
Play Text
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
//#include "src/Protocol/USBmidi.h"
#include "src/Protocol/MIDI.h"
//#include "src/protocol/M2P.h"
#include "src/Components/UI.h"

UI UI;
//UIelement uielement;
MIDI Midi;
LED LED;
KeyPad KeyPad;
Timer mainTimer;
Timer keypadTimer;

void setup()
{
  digitalWrite(led_pin,LOW);
  loadDeviceConfig();
  setupEEPROM();
  variableLoad();
  setupHardware();
  specialBoot();
  setupUSB();

  #ifdef DEBUG
  CompositeSerial.println("Setup Complete");
  #endif

  mainTimer.recordCurrent();
  while(!USBComposite.isReady() && !KeyPad.fn)
  {
    KeyPad.scan();
    if (mainTimer.isLonger(9900))
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

  if(!KeyPad.fn)
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
    if(!fn_hold)
    {
      if(KeyPad.fnChanged)
      {
        if(KeyPad.fn)
        UI.enterFNmenu();
      }
    }

    for(int i = 0; i < MULTIPRESS; i++)
    {
      if(KeyPad.list[i].velocity== -1)
      return;
      if(KeyPad.list[i].velocity > 0)
      {
        if(midi_enable)
        {
          Midi.sentXYon(KeyPad.list[i].xy, KeyPad.list[i].velocity);
        }
      }
      else
      {
        Midi.sentXYoff(KeyPad.list[i].xy, 0);
      }
    }
  }

  if(KeyPad.fn && fn_hold)
  {
    if(KeyPad.fnTimer.isLonger(200))
    {
      UI.enterFNmenu();
      KeyPad.fnTimer.recordCurrent();
    }
  }
}



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

  if (keypadTimer.tick(8))
  {
    readKey();
  }

  if (mainTimer.tick(16))
  {
    Midi.offScan();
    LED.update();
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
  //LED.setBrightness(16);
  LED.fill(0);
  LED.update();

  while(!KeyPad.fn)
  {
    if (mainTimer.tick(1000/fps))
    {
      if(KeyPad.scan())
      {
        for(int i = 0; i < MULTIPRESS; i++)
        {
          // if(KeyPad.list[i].velocity== -1)
          // break;

          if(KeyPad.list[i].velocity > 0)
          {
            LED.setXYHEX(KeyPad.list[i].xy, 0xFFFFFF, true, true);
          }
        }
        LED.update();
      }
    }
  }
}
