#include "KeyPad.h"
#include <USBComposite.h>

// extern MIDI Midi;
//

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
  for (u8 x = 0; x < XSIZE; x++) //for 0 - 7 do
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


    for (s8 y = YSIZE-1; y >= 0; y--) //y could go negative so use int instead uint
    {
      digitalWrite(SI_CLOCK, LOW);

      if (digitalRead(SI_DATA) != bitRead(keypadState[x],y))
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
        bitWrite(keypadState[x], y, digitalRead(SI_DATA));
        bitWrite(keypadChanged[x], y, 1);
        // CompositeSerial.println(y * 0x10 + x);
        #ifdef DEBUG
        if(digitalRead(SI_DATA))
        {
          CompositeSerial.print("KeyPad On \t");
        }
        else
        {
          CompositeSerial.print("KeyPad Off \t");
        }
        CompositeSerial.print(x * 0x10 + y, HEX);
        CompositeSerial.print("\t");
        CompositeSerial.print(x);
        CompositeSerial.print("\t");
        CompositeSerial.println(y);
        #endif
      }
      else
      {
        bitWrite(keypadChanged[x], y, 0);
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
      if(fnTimer.isLonger(MULTITAP_THRESHOLD))
      {
        timesFNpressed ++;
      }
      else
      {
        timesFNpressed = 0;
      }

      //FNholded = millis() - lastFNpressed;
      fnTimer.recordCurrent();

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
  updateList();

  return changed;
}

void KeyPad::updateList()
{
  for(int i = 0; i < MULTIPRESS; i++)
  {
    list[i].velocity = -1;
  }

  int i = 0;
  for(int y = 0; y < YSIZE; y++)
  {
    for(int x = 0; x < XSIZE; x++)
    {
      if(i == MULTIPRESS)
      return;

      if(bitRead(keypadChanged[x], y) == true)
      {
        switch(rotation)
        {
          break;
          case 1:
          list[i].xy = y * 0x10 + (7 - x);
          break;
          case 2:
          list[i].xy = (7 - x) * 0x10 + (7 - y);
          break;
          case 3:
          list[i].xy = (7 - y) * 0x10 + x;
          break;
          default:
          list[i].xy = xytoxy(x, y);
        }

        if(bitRead(keypadState[x], y) == true)
        {
          list[i].velocity = 127;
        }
        else
        {
          list[i].velocity = 0;
        }
        i++;
        bitWrite(keypadChanged[x], y, 0);
      }
    }
  }
}

bool KeyPad::checkXY(u8 x, u8 y)
{
  return KeyPad::checkXY(xytoxy(x, y));
}

bool KeyPad::checkXY(u8 xy)
{
  u8 xyr = xyReverseRotation(xy);
  return bitRead(keypadState[(xyr & 0xF0) >> 4], xyr & 0x0F);
}

// void KeyPad::On(uint8 x, uint8 y)
// {
//   CompositeSerial.println(xyToIndex(x,y)*10+1);
//
//   switch (rotation)
//   {
//     case 1: //90
//     Midi.sentNoteOn(MIDIChannel, keymap[x][YSIZE - y - 1], 127);
//     break;
//     case 2: //180
//     Midi.sentNoteOn(MIDIChannel, keymap[YSIZE - y - 1][XSIZE - x - 1], 127);
//     break;
//     case 3: //270
//     Midi.sentNoteOn(MIDIChannel, keymap[XSIZE - x - 1][y], 127);
//     break;
//     default: //0
//     Midi.sentNoteOn(MIDIChannel, keymap[y][x], 127);
//   }
// }
//
// void KeyPad::Off(uint8 x, uint8 y)
// {
//   CompositeSerial.println(xyToIndex(x,y)*10);
//
//   switch (rotation)
//   {
//     case 1: //90
//     Midi.sentNoteOff(MIDIChannel, keymap[x][YSIZE - y - 1], 0);
//     break;
//     case 2: //180
//     Midi.sentNoteOff(MIDIChannel, keymap[YSIZE - y - 1][XSIZE - x - 1], 0);
//     break;
//     case 3: //270
//     Midi.sentNoteOff(MIDIChannel, keymap[XSIZE - x - 1][y], 0);
//     break;
//     default: //0
//     Midi.sentNoteOff(MIDIChannel, keymap[y][x], 0);
//   }
// }
