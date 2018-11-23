#include <USBMIDI.h>
#include <FastLED.h>
#include "LED.h"
#include "CDC.h"
#include "MIDI.h"
#include "MatrixVariable.h"
#include "MatrixSystem.h"

extern MatrixSystem Matrix;
extern MIDI Midi;
extern LED LED;
extern CDC CDC;

void setup()
{
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
