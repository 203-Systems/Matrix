#include "KeyPad.h"

// extern MIDI Midi;
// extern MatrixSystem Matrix;

KeyPad::KeyPad()
{
  pinMode(SO_DATA, OUTPUT);
  pinMode(SO_CLOCK, OUTPUT);

  pinMode(SI_SCAN, OUTPUT);
  pinMode(SI_CLOCK, OUTPUT);
  pinMode(SI_DATA, INPUT_PULLDOWN);

  pinMode(FN_PIN, INPUT_PULLDOWN);
}

bool KeyPad::scan()
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

      if (digitalRead(SI_DATA) != bitRead(keypadStats[y],x))
      {
        // if (digitalRead(SI_DATA))
        // {
        //   KeyPad::On(x,y);
        // }
        // else
        // {
        //   KeyPad::Off(x,y);
        // }
        changed = true;
        bitWrite(keypadStats[y], x, digitalRead(SI_DATA));
        bitWrite(keypadChanged[y], x, 1);
      }
      else
      {
        bitWrite(keypadChanged[y], x, 0);
      }
      digitalWrite(SI_CLOCK, HIGH);
    }


  }

  if(digitalRead(FN_PIN) != fnCache)
  {
    changed = true;
    fnChanged = true;
    fnCache = digitalRead(FN_PIN);
    if(fnCache)
    {
      // if(lastFNpressed == 0)
      // lastFNpressed = millis();
      if(millis() - lastFNpressed <= MULTITAP_THRESHOLD)
      {
        timesFNpressed ++;
      }
      else
      {
        timesFNpressed = 0;
      }

      //FNholded = millis() - lastFNpressed;
      lastFNpressed = millis();

      fn = true;
    }
    else
    {
      fn = false;
    }
  }
  else
  {
    fnChanged = false;
  }
  if(changed)
  UpdateList();

  return changed;
}

void KeyPad::updateList()
{
  for(int i = 0; i < MULTIPRESS; i++)
  {
    list[i].velocity = 255;
  }

  int i = 0;
  for(int y = 0; y < KEYPADY; y++)
  {
    for(int x = 0; x < KEYPADX; x++)
    {
      if(i == MULTIPRESS)
      return;
      if(bitRead(keypadChanged[x], y) == true)
      {
        if(bitRead(keypadStats[x], y) == true)
        {
          list[i].xy = x << 4 + y;
          list[i].velocity = 127;
          i++;
        }
        else
        {
          list[i].xy = x << 4 + y;
          list[i].velocity = 0;
          i++;
        }
        bitWrite(keypadChanged[x], y, 0);
      }
    }
  }
}

// void KeyPad::On(uint8 x, uint8 y)
// {
//   CompositeSerial.println(Matrix.XYtoIndex(x,y)*10+1);
//
//   switch (rotation)
//   {
//     case 1: //90
//     Midi.SentNoteOn(MIDIChannel, keymap[x][KEYPADY - y - 1], 127);
//     break;
//     case 2: //180
//     Midi.SentNoteOn(MIDIChannel, keymap[KEYPADY - y - 1][KEYPADX - x - 1], 127);
//     break;
//     case 3: //270
//     Midi.SentNoteOn(MIDIChannel, keymap[KEYPADX - x - 1][y], 127);
//     break;
//     default: //0
//     Midi.SentNoteOn(MIDIChannel, keymap[y][x], 127);
//   }
// }
//
// void KeyPad::Off(uint8 x, uint8 y)
// {
//   CompositeSerial.println(Matrix.XYtoIndex(x,y)*10);
//
//   switch (rotation)
//   {
//     case 1: //90
//     Midi.SentNoteOff(MIDIChannel, keymap[x][KEYPADY - y - 1], 0);
//     break;
//     case 2: //180
//     Midi.SentNoteOff(MIDIChannel, keymap[KEYPADY - y - 1][KEYPADX - x - 1], 0);
//     break;
//     case 3: //270
//     Midi.SentNoteOff(MIDIChannel, keymap[KEYPADX - x - 1][y], 0);
//     break;
//     default: //0
//     Midi.SentNoteOff(MIDIChannel, keymap[y][x], 0);
//   }
// }
