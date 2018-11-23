#include "KeyPad.h"

extern MIDI Midi;
extern MatrixSystem Matrix;

KeyPad::KeyPad()
{
  pinMode(SO_DATA, OUTPUT);
  pinMode(SO_CLOCK, OUTPUT);

  pinMode(SI_SCAN, OUTPUT);
  pinMode(SI_CLOCK, OUTPUT);
  pinMode(SI_DATA, INPUT);
}

bool KeyPad::Scan()
{
  bool changed = false;
  for (uint8_t x = 0; x < KEYPADX; x++) //for 0 - 7 do
  {
    shiftOut(SO_DATA, SO_CLOCK, MSBFIRST, 1 << x); // bit shift a logic high (1) value by i
    digitalWrite(SI_SCAN, LOW);
    digitalWrite(SI_SCAN, HIGH);

    digitalWrite(SI_CLOCK, LOW);
    digitalWrite(SI_SCAN, LOW);
    digitalWrite(SI_SCAN, HIGH);

    for (uint8_t y = KEYPADY; y > 0; y--)
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
    //delay(200);
  }
  return changed;
}

void KeyPad::On(uint8_t x, uint8_t y)
{
  Midi.SentNoteOn(MIDIChannel,Matrix.XYtoIndex(x,y),127);
}

void KeyPad::Off(uint8_t x, uint8_t y)
{
  Midi.SentNoteOff(MIDIChannel,Matrix.XYtoIndex(x,y),0);
}
