/*
Project Matrix (c) 203 Industries

TODO
Load variable from flash
FN key menu
Play Animation
Play Text

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
#include "src/core/USBmidi.h"
#include "src/protocol/MIDI.h"
#include "src/protocol/M2P.h"
//#include "..UI.h"


MIDI Midi;
M2P M2P;
LED LED;
KeyPad KeyPad;
MatrixSystem Matrix;
usbmidi USBmidi;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

void setup()
{
  if(device_id != 0)
  {

    USBComposite.setProductString((DEVICENAME + String(' ' + device_id)).c_str());
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

  FastLED.setBrightness(brightness);

  while(!USBComposite.isReady())
  {
    LED.fill(0xff0000);
  }
  LED.fill(0x000000);
}

void ReadKey()
{
  if (KeyPad.scan())
  {
    // if(KeyPad.timesFNpressed == 5)
    // UI.ShowDeviceInfo();
    // if(KeyPad.timesFNpressed == 10)
    // UI.EasterEgg();
    // if(KeyPad.fn)
    // UI.EnterFNmenu();

    for(int i = 0; i < MULTIPRESS; i++)
    {
      if(KeyPad.list[i].velocity == 255)
      return;
      if(KeyPad.list[i].velocity > 0)
      {
        if(midi_enable)
        {
          Midi.sentXYon(KeyPad.list[i].xy && 0xF0, KeyPad.list[i].xy && 0xF0, KeyPad.list[i].velocity);
        }
        else
        {
          Midi.sentXYon(KeyPad.list[i].xy && 0xF0, KeyPad.list[i].xy && 0xF0, 0);
        }
      }
    }
  }
}

void loop()
{
  if (midi_enable);
  USBmidi.poll();
  // if (m2p_enable)
  // CDC.Poll();

  ReadKey();

  currentMillis = millis();
  if (currentMillis - previousMillis >= 1000/FPS)
  {
    LED.update();
    //LED.Rainbow();
    //CompositeSerial.println("Running");
    previousMillis = currentMillis;
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