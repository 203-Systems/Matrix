#include <FastLED.h>
#include <USBMIDI.h>
#include <USBComposite.h>
#include "LED.h"
#include "MIDI.h"
#include "MatrixVariable.h"
#include "MatrixSysex.h"

#define NUM_LEDS 64

USBCompositeSerial CDC;

class usbmidi : public USBMidi {
    virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) {
      MIDIoff(channel, note, velocity);
    }

    virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) {
      MIDIon(channel, note, velocity);
    }
};

usbmidi MIDI;

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  //String Name = DeviceName + " " + DeviceID;
  //USBComposite.setProductString(Name);
  USBComposite.setProductString("Matrix Prototype");
  USBComposite.setVendorId(VID);
  USBComposite.setProductId(PID);
  CDC.registerComponent();
  MIDI.registerComponent();
  USBComposite.begin();
}

void loop()
{
  if (MIDIEnable);
  MIDI.poll();
  if (CDCEnable);
  CDCpoll();
}


