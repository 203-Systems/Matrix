void CDCSysexSet() {
  switch (CompositeSerial.read() & 0x0F) {
    case 8:
      reset();
      break;
    case 9:
      EnterBootloader();
      break;
    case 10:
      InitializeDevice();
      break;
    case 20:
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
  switch(CompositeSerial.read() & 0x0F){

  }
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
    int device = CompositeSerial.peek() >> 4;
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
