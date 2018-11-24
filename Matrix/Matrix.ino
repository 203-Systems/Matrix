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
  LED.Fill(0);
}

void loop()
{
  //usbmidi.poll();
  if (MIDIEnable);
  USBmidi.poll();
  // if (CDCEnable)
  // CDC.Poll();

  KeyPad.Scan();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 2000)
  {
    LED.Update();
    CompositeSerial.println("Running");
    previousMillis = currentMillis;
  }
}
