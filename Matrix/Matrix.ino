#include <Arduino.h>
#include <USBMIDI.h>
#include <USBComposite.h>
#include <FastLED.h>
#include "MatrixSystem.h"
#include "LED.h"
//#include "CDC.h"
#include "USBmidi.h"
#include "MIDI.h"
#include "MatrixVariable.h"

MIDI Midi;
LED LED;
//CDC CDC;
MatrixSystem Matrix;
//usbmidi usbmidi;

void setup()
{
  // LED();
  //+ Powercord(true);
  // Midi();
  // CDC();
  //String Name = DeviceName + " " + DeviceID;
  //USBComposite.setProductString(Name);
  USBComposite.setProductString(DEVICENAME);
  USBComposite.setVendorId(VID);
  USBComposite.setProductId(PID);
  Midi.Begin();
  //usbmidi.registerComponent();
  //  CDC.registerComponent();

  //LEDsetup();
  //Midi.begin();
  USBComposite.begin();
}

void loop()
{
  //usbmidi.poll();
  if (MIDIEnable);
  Midi.Poll();
  // if (CDCEnable);
  // CDC.Poll();
}
