/*
Project Matrix (c) 203 Industries

TODO
Play Animation
Play Text
BootAnimation
NexusRevamped while USB unreconized

*/

#include <Arduino.h>
#include <USBMIDI.h>
#include <USBComposite.h>
#include <FastLED.h>
#include "src/parameter/MatrixVariable.h"
#include "src/parameter/MatrixParameter.h"
//#include "../Serials.h"
#include "src/core/MatrixSystem.h"
#include "src/core/KeyPad.h"
#include "src/core/LED.h"
#include "src/core/Timer.h"
#include "src/core/USBmidi.h"
#include "src/protocol/MIDI.h"
//#include "src/protocol/M2P.h"
#include "src/ui/UI.h"

UI UI;
MIDI Midi;
//M2P M2P;
LED LED;
KeyPad KeyPad;
usbmidi USBmidi;
Timer mainTimer;

void setup()
{
  // rotation = *(volatile u8*)0x801F000;

  // initEEPROM();
  // resetEEPROM();
  // variableLoad();

  setupUSB();
  setupHardware();

  FastLED.setBrightness(brightness);

  #ifdef DEBUG
  CompositeSerial.println("Setup Complete");
  #endif

  specialBoot();

  mainTimer.recordCurrent();
  while(!USBComposite.isReady())
  {
    if (mainTimer.isLonger(1000))
    {

      //NexusRevamped nexus = new NexusRevamped();
      while(!USBComposite.isReady())
      {
        LED.fill(0xff0000); //NexusRevamped Entence point
        LED.update();
      }
      //delete nexus;
      break;
    }
  }
  LED.fill(0x000000);
  LED.update();

  #ifdef DEBUG
  CompositeSerial.println("Enter Main Program");
  #endif
}

void setupUSB()
{

  if(device_id != 0)
  {

    USBComposite.setProductString((DEVICENAME + String(' ') + String(device_id)).c_str());
    USBComposite.setVendorId(VID2);
    USBComposite.setProductId(PID2+device_id);
  }
  else
  {
    USBComposite.setProductString(DEVICENAME);
    USBComposite.setVendorId(VID);
    USBComposite.setProductId(PID);
  }

  USBComposite.setManufacturerString(MAUNFACTURERNAME);
  //USBComposite.setProductString(DEVICENAME);
  USBComposite.setSerialString(SERIALSTRING);

  USBmidi.registerComponent();
  CompositeSerial.registerComponent();
  USBComposite.begin();

}

void setupHardware()
{

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
      // UI.EasterEgg();
      if(KeyPad.fn)
      UI.enterFNmenu();
    }

    for(int i = 0; i < MULTIPRESS; i++)
    {
      if(KeyPad.list[i].velocity > 128)
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

void specialBoot()
{
  if (KeyPad.scan())
  {
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
//       if (mainTimer.tick(1000/FPS))
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

void factoryTest()
{
  LED.fill(0xFFFFFF);

  while(!KeyPad.fn)
  {
    if (mainTimer.tick(1000/FPS))
    {
      KeyPad.scan();

      for(int i = 0; i < MULTIPRESS; i++)
      {
        if(KeyPad.list[i].velocity > 128)
        break;

        if(KeyPad.list[i].velocity > 0)
        {
          if(LED.readXYLED(KeyPad.list[i].xy) != 0xFFFFFF)
          {
            LED.setXYHEX(KeyPad.list[i].xy, 0xFFFFFF);
          }
          else
          {
            LED.offXY(KeyPad.list[i].xy);
          }
        }
      }
      LED.update();
    }
  }
}



void loop()
{
  if (midi_enable);
  USBmidi.poll();
  // if (m2p_enable)
  // CDC.Poll();

  if (mainTimer.tick(1000/FPS))
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
