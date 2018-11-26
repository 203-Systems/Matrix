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
#include "MatrixSystem.h"
#include "LED.h"
#include "M2P.h"
#include "KeyPad.h"
#include "USBmidi.h"
#include "MIDI.h"
#include "MatrixVariable.h"

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
  if(DeviceID != 0)
  {

      USBComposite.setProductString((DEVICENAME + String(DeviceID)).c_str());
      USBComposite.setVendorId(VID2);
      USBComposite.setProductId(PID2+DeviceID);
  }
  else
  {
      USBComposite.setProductString(DEVICENAME);
      USBComposite.setVendorId(VID);
      USBComposite.setProductId(PID);
  }

  USBComposite.setManufacturerString(MAUNFACTURERNAME);
  //USBComposite.setProductString(DEVICENAME);
  USBComposite.setSerialString("unsigned");

  USBmidi.registerComponent();
  CompositeSerial.registerComponent();
  USBComposite.begin();

  FastLED.setBrightness(Brightness);

  while(!USBComposite.isReady())
  {
      LED.Fill(CRGB::Red);
  }
          LED.Fill(CRGB::Black);
}

void loop()
{
  //usbmidi.poll();
  if (MIDIEnable);
  USBmidi.poll();
  // if (CDCEnable)
  // CDC.Poll();


  currentMillis = millis();
  if (currentMillis - previousMillis >= 1000/FPS)
  {
    KeyPad.Scan();
    LED.Update();
    //LED.Rainbow();
    CompositeSerial.println("Running");
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
//         LED.SetPallette(p,c,c+n*64);
//       }
//       LED.Update();
//       delay(1000);
//       while(KeyPad.Scan() == 0)
//       {
//
//       }
//       while(KeyPad.Scan() == 0)
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
//       LED.SetPallette(0,c,c+n*64);
//     }
//     LED.Update();
//     while(KeyPad.Scan() == 0)
//     {
//
//     }
//         delay(50);
//     while(KeyPad.Scan() == 0)
//     {
//
//     }
//     //   GammaEnable = !GammaEnable;
//     // }
//   }
//}
