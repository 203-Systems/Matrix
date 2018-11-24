#include <Arduino.h>
#include <USBMIDI.h>
#include <USBComposite.h>
#include <FastLED.h>
#include "MatrixSystem.h"
#include "LED.h"
//#include "CDC.h"
#include "KeyPad.h"
#include "USBmidi.h"
#include "MIDI.h"
#include "MatrixVariable.h"

MIDI Midi;
//CDC CDC;
LED LED;
KeyPad KeyPad;
MatrixSystem Matrix;
usbmidi USBmidi;

unsigned long previousMillis = 0;


void setup()
{
  // LED();
  //+ Powercord(true);
  // Midi();
  // CDC();
  //String Name = DeviceName + " " + DeviceID;
  //USBComposite.setProductString(Name);
  USBmidi.registerComponent();
  CompositeSerial.registerComponent();
  USBComposite.setProductString(DEVICENAME);
  USBComposite.setVendorId(VID);
  USBComposite.setProductId(PID);
  //Midi.Begin();
  //usbmidi.registerComponent();
  //  CDC.registerComponent();

  //LEDsetup();
  //Midi.begin();
  USBComposite.begin();
  //SetBrightness(Brightness);
  FastLED.setBrightness(Brightness);
  LED.Fill(0);
}

void loop()
{
  //usbmidi.poll();
  if (MIDIEnable);
  USBmidi.poll();
  // if (CDCEnable)
  // CDC.Poll();


  unsigned long currentMillis = millis();
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
//     for(int i = 0; i < 2; i++)
//     {
//       for(int c = 0; c < 64; c++)
//       {
//         LED.SetPallette(0,c,c+n*64);
//       }
//       LED.Update();
//       delay(200);
//       while(KeyPad.Scan() == 0)
//       {
//
//       }
//       while(KeyPad.Scan() == 0)
//       {
//
//       }
//       GammaEnable = !GammaEnable;
//     }
//   }
// }
