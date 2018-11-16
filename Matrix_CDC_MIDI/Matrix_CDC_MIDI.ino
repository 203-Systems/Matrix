#include <USBMIDI.h>
#include <USBComposite.h>
#include "LED.h"
#include "MatrixVariable.h"
#include "MatrixSysex.h"

USBCompositeSerial CDC;

class usbmidi : public USBMidi {
    virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) {
      CDC.print(channel);
      CDC.print("\toff\t");
      CDC.print(note);
      CDC.print("\t");
      CDC.println(velocity);
    }

    virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) {
      CDC.print(channel);
      CDC.print("\ton\t");
      CDC.print(note);
      CDC.print("\t");
      CDC.println(velocity);
    }
};

usbmidi MIDI;

void setup()
{
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


