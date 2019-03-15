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
MIDI Midi;
LED LED;
KeyPad KeyPad;
Timer mainTimer;

void setup()
{
  loadDeviceConfig();
  specialBoot();
  setupEEPROM();
  variableLoad();
  setupLED();
  setupUSB();

  #ifdef DEBUG
  CompositeSerial.println("Setup Complete");
  #endif

  mainTimer.recordCurrent();
  while(!USBComposite.isReady())
  {
    if (mainTimer.isLonger(3000))
    {
      LED.fill(0xff0000); //NexusRevamped Entence point
      LED.update();
    }
  }

  UI.kBootAnimation();
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
    if(KeyPad.fnChanged)
    {
      // if(KeyPad.timesFNpressed == 5)
      // UI.ShowDeviceInfo();
      // if(KeyPad.timesFNpressed == 10)
      // UI.EasterEgg();)
      if(KeyPad.fn)
      UI.enterFNmenu();
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


//
// int ttt = 63;
void loop()
{
  // if(USBmidi.available())
  // {
  //   LED.on(ttt);
  //   ttt--;
  // }

  if (midi_enable);
  Midi.poll();
  // if (m2p_enable)
  // CDC.Poll();

  if (mainTimer.tick(1000/fps))
  {
    readKey();
    LED.update();
    //LED.Rainbow();
    //CompositeSerial.println("Running");
  }
}

// test
// void loop()
// {
//   for(int p = 0; p < 2; p++)
//   {
//     for(int n = 0; n < 2; n++)
//     {
//       for(int c = 0; c < 64; c++)
//       {
//         LED.setPalette(p,c,c+n*64);
//       }
//       LED.update();
//       delay(1000);
//       while(KeyPad.scan() == 0)
//       {
//
//       }
//       while(KeyPad.scan() == 0)
//       {
//
//       }
//     }
//   }
// }
//
// void loop()
// {
//   for(int n = 0; n < 2; n++)
//   {
//     // for(int i = 0; i < 2; i++)
//     // {
//     for(int c = 0; c < 64; c++)
//     {
//       LED.setPalette(0,c,c+n*64);
//     }
//     LED.update();
//     while(KeyPad.scan() == 0)
//     {
//
//     }
//         delay(50);
//     while(KeyPad.scan() == 0)
//     {
//
//     }
//     //   gamma_enable = !gamma_enable;
//     // }
//   }
//}

void specialBoot()
{
  if (KeyPad.scan())
  {
    if(KeyPad.checkXY(1, 1) && KeyPad.checkXY(0, 0))
    {
      formatEEPROM();
      LED.fill(0xFF00FF);
    }

    if(KeyPad.checkXY(1, 1) && KeyPad.checkXY(0, 0))
    {
      factoryTest();
    }

    if(KeyPad.checkXY(0x00) && KeyPad.checkXY(0x02))
    {
      setDeviceID(203);
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
