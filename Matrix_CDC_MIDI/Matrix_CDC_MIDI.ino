#include <USBMIDI.h>
#include <USBComposite.h>


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

bool MIDIEnable = true;
bool CDCEnable = true;

int TouchSensitive = 0;
int Brightness = 64;


void setup() {
  USBComposite.setProductString("Matrix CDC Proto");
  USBComposite.setVendorId(0x203);
  USBComposite.setProductId(0x802);
  midi.registerComponent();
  CompositeSerial.registerComponent();
  USBComposite.begin();

}

//LED releated
void LEDoff(int X, int Y );
void LEDon(int X, int Y );
void LEDon(int X, int Y, int w);
void LEDon(int X, int Y, int R, int G, int B) ;
void LEDon(int X, int Y, int R, int G, int B, int W);
void LEDsetPallette(int X, int Y, int w);

//Sysex Set
void reset();
void EnterBootloader();
void InitializeDevice();
void UpdateColourPaletteRGB();
void UpdateColourPaletteRGBW();
void ResetColourPalette();
void setGamma(boolean state)
void UpdateCustomKeyMap();
void ResetCustomKeyMap();
void setBrightness(int brightness);
void SetTouchSensitive();

//Sysex Get
void GetDeviceInfo();
void GetModuleCount();
void GetModuleInfo();
void GetAllParameter()
void GetColorPaletteRGB();
void GetColorPaletteRGBW();
void GetGammaState();
void GetCustomKeyMap();
void GetBrightness();
void GetTouchSensitive();

void CDCSysexSet() {
  switch (CompositeSerial.read() & 0x0F) {
    case 8;
      reset():
      break;
    case 9;
      EnterBootloader():
      break;
    case 10;
      InitializeDevice();
      break;
    case 20;
      UpdateColourPaletteRGB();
      break;
    case 21:
      UpdateColourPaletteRGBW();
      break;
    case 22:
      ResetColourPalette();
      break;
    case 25:
      UpdateCustomKeyMap();
      break;
    case 26:
      ResetCustomKeyMap();
      break;
    case 30:
      SetBrightness(CompositeSerial.read());
      break;
    case 31:
      SetTouchSensitive(CompositeSerial.read());
      break;
  }
}

void CDCSysexGet() {
  switch(CompositeSerial.read() & 0x0F)
}

void CDCMIDI() {
  int Mode = CompositeSerial.peek() >> 4;
  int Channel = CompositeSerial.read() & 0x0F;
  int Note = CompositeSerial.read();
  int Velocity = CompositeSerial.read();
  //  switch (Mode) {
  //    case 8:
  //      midi.handleNoteOff(Channel, Note, Velocity);
  //    case 9:
  //      midi.handleNoteOff(Channel, Note, Velocity);
  //  }
}

void CDCDecode() {
  switch (CompositeSerial.read()) {
    case 0x00://0
      LEDoff(CompositeSerial.read(), CompositeSerial.read());
      break;
    case 0x01://1
      LEDon(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYRGB
      break;
    case 0x02://2
      LEDon(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYRGBW
      break;
    case 0x03://3
      LEDon(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYW
      break;
    case 0x04://4
      LEDon(CompositeSerial.read(), CompositeSerial.read()); //XY
      break;
    case 0x05://5
      LEDsetPallette(CompositeSerial.read(), CompositeSerial.read(), CompositeSerial.read()); //XYP
      break;
    case 0x0D://14
      CDCSysexSet();
      break;
    case 0x0E://14
      CDCSysexGet();
      break;
    case 0x0F://15
      CDCMIDI();
      break;
  }
}

void CDCpull() {
  if (CompositeSerial.available() > 0) {
    int device = CompositeSerial.peek() >> 4);
    if (device == 0) {
    CDCDecode();
    }
    if (device > 0 && device < 8) {
    CDCDecode();
    } else
    {

    }
  }
}
void loop() {
  if (MIDIEnable);
  midi.poll();
  if (CDCEnable);
  CDCpull();
}
