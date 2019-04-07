#include "KeyPad.h"
#include <USBComposite.h>

// extern MIDI Midi;
//

KeyPad::KeyPad()
{

}

void KeyPad::init()
{
  pinMode(so_data, OUTPUT);
  pinMode(so_clock, OUTPUT);

  pinMode(si_scan, OUTPUT);
  pinMode(si_clock, OUTPUT);
  pinMode(si_data, INPUT_PULLDOWN);

  pinMode(fn_pin, INPUT_PULLDOWN);
}

bool KeyPad::scan()
{
  bool changed = false;
  for (u8 x = 0; x < XSIZE; x++) //for 0 - 7 do
  {
    //shiftOut(so_data, so_clock, MSBFIRST, 1 << x); // bit shift a logic high (1) value by i
    if( x == 0)
    {
      digitalWrite(so_data, HIGH);
    }

    digitalWrite(so_clock, HIGH);
    digitalWrite(so_data, LOW);
    digitalWrite(so_clock, LOW);

    digitalWrite(si_scan, LOW); //165's load Active at Low
    digitalWrite(si_scan, HIGH);


    for (s8 y = YSIZE-1; y >= 0; y--) //y could go negative so use int instead uint
    {
      digitalWrite(si_clock, LOW);

      if (digitalRead(si_data) != bitRead(keypadState[x],y))
      {
        // if (digitalRead(si_data))
        // {
        //   KeyPad::On(x,y);
        // }
        // else
        // {
        //   KeyPad::Off(x,y);
        // }
        changed = true;
        bitWrite(keypadState[x], y, digitalRead(si_data));
        bitWrite(keypadChanged[x], y, 1);
        // CompositeSerial.println(y * 0x10 + x);
        #ifdef DEBUG
        if(digitalRead(si_data))
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



      digitalWrite(si_clock, HIGH);
    }


  }

  if(digitalRead(fn_pin) != fnCache)
  {
    changed = true;
    fnChanged = true;
    fnCache = digitalRead(fn_pin);
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
    //list[i].xy = 0xFF;
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

bool KeyPad::checkXY(u8 x, u8 y, bool no_rotation)
{
  return KeyPad::checkXY(xytoxy(x, y), no_rotation);
}

bool KeyPad::checkXY(u8 xy, bool no_rotation)
{
  if(!no_rotation)
    xy = xyReverseRotation(xy);
  return bitRead(keypadState[(xy & 0xF0) >> 4], xy & 0x0F);
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
