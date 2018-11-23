#include <USBMIDI.h>

#define SPEAKER_PIN PA0

class myMidi : public USBMidi {
 virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) {
  noTone(SPEAKER_PIN);
 }
 virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) {
   tone(SPEAKER_PIN, (midiNoteFrequency_10ths[note]+5)/10);
  }
  
};

myMidi midi;

void setup() {
    pinMode(SPEAKER_PIN, OUTPUT);
    midi.registerComponent();
    CompositeSerial.registerComponent();
    USBComposite.begin();
}

void loop() {
  midi.poll();
}

