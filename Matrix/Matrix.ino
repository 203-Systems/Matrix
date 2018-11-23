#include <Arduino.h>
#include <USBMIDI.h>
#include <USBComposite.h>
#include <FastLED.h>
#include "MatrixSystem.h"
#include "LED.h"
//#include "CDC.h"
//#include "USBmidi.h"
#include "MIDI.h"
#include "MatrixVariable.h"

MIDI Midi;

class usbmidi : public USBMidi
{
  virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity)
  {
    Midi.NoteOff(channel,note,velocity);
    //USBMIDI.sendNoteOff(channel,note,velocity);
    //leds[IndexInKeyMap(note)] = 0;
    //CompositeSerial.println(channel + " off " + note + " " + velocity);
  }

  virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity)
  {
    Midi.NoteOn(channel,note,velocity);
    //USBMIDI.sendNoteOn(channel,note,velocity);
    //leds[IndexInKeyMap(note)] = colour[channel][velocity];
  }
};

LED LED;
//CDC CDC;
MatrixSystem Matrix;
//usbmidi usbmidi;
usbmidi USBmidi;

void setup()
{
  // LED();
  //+ Powercord(true);
  // Midi();
  // CDC();
  //String Name = DeviceName + " " + DeviceID;
  //USBComposite.setProductString(Name);
  USBmidi.registerComponent();
  USBComposite.setProductString(DEVICENAME);
  USBComposite.setVendorId(VID);
  USBComposite.setProductId(PID);
  //Midi.Begin();
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
  USBmidi.poll();
  // if (CDCEnable);
  // CDC.Poll();
}
