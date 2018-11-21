#include <USBComposite.h>
#include <USBMIDI.h>
#include <FastLED.h>
//#include "LED.h"
//#include "MIDI.h"
#include "MatrixVariable.h"
//#include "MatrixSysex.h"


//USBCompositeSerial CDC;

void setup()
{
  //String Name = DeviceName + " " + DeviceID;
  //USBComposite.setProductString(Name);
  USBComposite.setProductString("Matrix");
  USBComposite.setVendorId(0x203);
  USBComposite.setProductId(0x101);

//  CDC.registerComponent();

  //MIDIsetup();
  LEDsetup();

  USBComposite.begin();
}

void loop()
{
  // if (MIDIEnable);
  // MIDIpoll();
  // if (CDCEnable);
  // CDCpoll();
}
