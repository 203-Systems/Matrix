#include "KeyPad.h"

extern MIDI Midi;
extern MatrixSystem Matrix;

KeyPad::KeyPad()
{
  pinMode(SO_DATA, OUTPUT);
  pinMode(SO_CLOCK, OUTPUT);

  pinMode(SI_SCAN, OUTPUT);
  pinMode(SI_CLOCK, OUTPUT);
  pinMode(SI_DATA, INPUT_PULLDOWN);
}

bool KeyPad::Scan()
{
  bool changed = false;
  for (uint8_t x = 0; x < KEYPADX; x++) //for 0 - 7 do
  {
    //shiftOut(SO_DATA, SO_CLOCK, MSBFIRST, 1 << x); // bit shift a logic high (1) value by i
    if( x == 0)
    {
      digitalWrite(SO_DATA, HIGH);
    }

    digitalWrite(SO_CLOCK, HIGH);
    digitalWrite(SO_DATA, LOW);
    digitalWrite(SO_CLOCK, LOW);

    digitalWrite(SI_SCAN, LOW); //165's load Active at Low
    digitalWrite(SI_SCAN, HIGH);


    for (int8_t y = KEYPADY-1; y >= 0; y--) //y could go negative so use int instead uint
    {
      digitalWrite(SI_CLOCK, LOW);

      if (digitalRead(SI_DATA) != KeyPadStats[x][y])
      {
        if (digitalRead(SI_DATA))
        {
          KeyPad::On(x,y);
        }
        else
        {
          KeyPad::Off(x,y);
        }
        changed = true;
        KeyPadStats[x][y] = digitalRead(SI_DATA);
      }

      digitalWrite(SI_CLOCK, HIGH);
    }
  }
  return changed;
}

void KeyPad::On(uint8 x, uint8 y)
{
  CompositeSerial.println(Matrix.XYtoIndex(x,y)*10+1);

  switch (Rotation)
  {
    case 1: //90
    Midi.SentNoteOn(MIDIChannel, KeyMap[x][KEYPADY - y - 1], 127);
    break;
    case 2: //180
    Midi.SentNoteOn(MIDIChannel, KeyMap[KEYPADY - y - 1][KEYPADX - x - 1], 127);
    break;
    case 3: //270
    Midi.SentNoteOn(MIDIChannel, KeyMap[KEYPADX - x - 1][y], 127);
    break;
    default: //0
    Midi.SentNoteOn(MIDIChannel, KeyMap[y][x], 127);
  }
}

void KeyPad::Off(uint8 x, uint8 y)
{
  CompositeSerial.println(Matrix.XYtoIndex(x,y)*10);

  switch (Rotation)
  {
    case 1: //90
    Midi.SentNoteOff(MIDIChannel, KeyMap[x][KEYPADY - y - 1], 0);
    break;
    case 2: //180
    Midi.SentNoteOff(MIDIChannel, KeyMap[KEYPADY - y - 1][KEYPADX - x - 1], 0);
    break;
    case 3: //270
    Midi.SentNoteOff(MIDIChannel, KeyMap[KEYPADX - x - 1][y], 0);
    break;
    default: //0
    Midi.SentNoteOff(MIDIChannel, KeyMap[y][x], 0);
  }
}
