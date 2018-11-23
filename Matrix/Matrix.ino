#include <Arduino.h>
#include <USBMIDI.h>
#include <FastLED.h>
#include "MatrixSystem.h"
#include "LED.h"
#include "CDC.h"
#include "MIDI.h"
#include "MatrixVariable.h"

extern MIDI Midi;
extern LED LED;
extern CDC CDC;
extern MatrixSystem Matrix;

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

  //  CDC.registerComponent();

  //LEDsetup();
  //Midi.begin();
  USBComposite.begin();
}

void loop()
{
  if (MIDIEnable);
  Midi.Poll();
  if (CDCEnable);
  CDC.Poll();
}
