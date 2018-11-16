#include <USBMIDI.h>
#include <USBComposite.h>
#include <CDC.h>
#include <LED.h>
#include <MatrixVariable.h>


class usbmidi : public USBMidi {
    virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) {
      CompositeSerial.print(channel);
      CompositeSerial.print("\toff\t");
      CompositeSerial.print(note);
      CompositeSerial.print("\t");
      CompositeSerial.println(velocity);
    }

    virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) {
      CompositeSerial.print(channel);
      CompositeSerial.print("\ton\t");
      CompositeSerial.print(note);
      CompositeSerial.print("\t");
      CompositeSerial.println(velocity);
    }
};

usbmidi midi;

void setup() {
  USBComposite.setProductString("Matrix CDC Proto");
  USBComposite.setVendorId(0x203);
  USBComposite.setProductId(0x802);
  midi.registerComponent();
  CompositeSerial.registerComponent();
  USBComposite.begin();
}

void loop() {
  if (MIDIEnable);
  midi.poll();
  if (CDCEnable);
  CDCpull();
}
