#include "KeyPad.h"
#include <USBComposite.h>

// extern MIDI Midi;
//

KeyPad::KeyPad()
{


}

void KeyPad::init()
{
  switch(keypad_type)
  {
    case 1:
    return Keypad::initType1();
    case 2:
    return Keypad::initType2();
    case 3:
    return Keypad::initType3();
  }
}

void KeyPad::initType1()
{
  pinMode(KEYPAD_SO_DATA, OUTPUT);
  pinMode(KEYPAD_SO_CLOCK, OUTPUT);

  pinMode(KEYPAD_SI_LATCH, OUTPUT);
  pinMode(KEYPAD_SI_CLOCK, OUTPUT);
  pinMode(KEYPAD_SI_DATA, INPUT_PULLDOWN);

  pinMode(fn_pin, INPUT_PULLDOWN);
}

void KeyPad::initType2()
{
  for(u8 x = 0; x < XSIZE; x ++)
  {
    pinMode(keyPins(x), OUTPUT);
    digitalWrite(keyPins(x), LOW);
  }
  for(u8 y = 0; y < YSIZE; y ++)
  {
    pinMode(keyPins(Y + XSIZE), INPUT_PULLDOWN);
  }
}

void KeyPad::initType3()
{
  for(u8 x = 0; x < XSIZE; x ++)
  {
    pinMode(keyPins(x), OUTPUT);
    digitalWrite(keyPins(x), LOW);
  }
  for(u8 y = 0; y < YSIZE; y ++)
  {
    pinMode(keyPins(Y + XSIZE), INPUT_PULLDOWN);
  }
}


bool KeyPad::scan()
{
  switch(keypad_type)
  {
    case 1:
    return Keypad::scanType1();
    case 2:
    return Keypad::scanType2();
    case 2:
    return Keypad::scanType3();
  }
}

bool KeyPad::scanType1() //1.x 165/164 solution
{
  bool changed = false;

  change = change || scanFN();

  for (u8 x = 0; x < XSIZE; x++) //for 0 - 7 do
  {
    //shiftOut(KEYPAD_SO_DATA, KEYPAD_SO_CLOCK, MSBFIRST, 1 << x); // bit shift a logic high (1) value by i
    if( x == 0)
    {
      digitalWrite(KEYPAD_SO_DATA, HIGH);
    }

    digitalWrite(KEYPAD_SO_CLOCK, HIGH);
    digitalWrite(KEYPAD_SO_DATA, LOW);
    digitalWrite(KEYPAD_SO_CLOCK, LOW);

    digitalWrite(KEYPAD_SI_LATCH, LOW); //165's load Active at Low
    digitalWrite(KEYPAD_SI_LATCH, HIGH);


    for (s8 y = YSIZE-1; y >= 0; y--) //y could go negative so use int instead uint
    {
      digitalWrite(KEYPAD_SI_CLOCK, LOW);

      keypadState[x][y] = KeyPad::updateKey(keypadState[x][y], digitalRead(KEYPAD_SI_DATA));
      if(keypadState[x][y].changed)
      {
        changed = true;
        if(!KeyPad::addtoList(xytoxy(x,y)))
        return changed;
      }

      digitalWrite(KEYPAD_SI_CLOCK, HIGH);
    }
  }

  if(changed)
  updateList();

  return changed;
}

bool KeyPad::scanType2()
{
  bool changed = false;

  changed = changed || scanFN();

  for(u8 x = 0; x < XSIZE; x ++)
  {
    digitalWrite(x, HIGH);
    for(u8 y = 0; y < YSIZE; y ++)
    {
      keypadState[x][y] = KeyPad::updateKey(keypadState[x][y], digitalRead(y + 8));
      if(keypadState[x][y].changed)
      {
        changed = true;
        if(!KeyPad::addtoList(xytoxy(x,y)))
        return changed;
      }
    }
    digitalWrite(x, LOW);
  }

  return changed;
}

bool KeyPad::scanType3()
{
  bool changed = false;

  changed = changed || scanFN();

  for(u8 x = 0; x < XSIZE; x ++)
  {
    digitalWrite(x, HIGH);
    for(u8 y = 0; y < YSIZE; y ++)
    {
      keypadState[x][y] = KeyPad::updateKey(keypadState[x][y], velocityCurve(digitalRead(y + 8));
      if(keypadState[x][y].changed)
      {
        changed = true;
        if(!KeyPad::addtoList(xytoxy(x,y)))
        return changed;
      }
    }
    digitalWrite(x, LOW);
  }

  return changed;
}

bool KeyPad::scanFN()
{
  fn = updateKey(fn, digitalRead(fn_pin))
  return fn.changed;
}

/*
Action Checklist:
Nothing (All)
Active (Idle, Release)
Release(Pressed, Active, Hold, Hold Actived)
To Long Term State(Pressed, Hold, Release)
Hold Timer Threshold reached (Actived)
Aftertouch (Pressed, Actived, Hold, Hold Actived)
*/

Key KeyPad::updateKey(key currentKey, u16 input)
{
  currentKey.changed = false;
  switch(currentKey.keyState)
  {
    case IDLE:
    case RELEASED:
    if(input)
    {
      currentKey.keyState = PRESSED;
      currentKey.velocity = input;
      currentKey.activeTime = millis();
      currentKey.changed = true;
      break;
    }

    case PRESSED:
    case ACTIVED:
    case HOLD:
    case HOLD_ACTIVATED:
    if(!input)
    {
      currentKey.keyState = RELEASED;
      currentKey.velocity = 0;
      currentKey.changed = true;
      break;
    }

    case PRESSED:
    currentKey.keyState = ACTIVED;
    case HOLD:
    currentKey.keyState = HOLD_ACTIVED;
    case RELEASED:
    currentKey.keyState = IDLE;

    case ACTIVED:
    if(mills() - currentKey.activeTime > HOLD_THRESHOLD)
    {
      currentKey.keyState = HOLD;
      currentKey.changed = true;
    }


    case PRESSED:
    case ACTIVED:
    case HOLD:
    case HOLD_ACTIVATED:
    if(abs(currentKey.velocity - input) > AFTERTOUCH_THRESHOLD)
    {
      currentKey.velocity = input;
      currentKey.changed = true;
    }
  }
  return currentKey;
}

void KeyPad::cleanList()
{
  for(u8 i = 0; i < MULTIPRESS; i++)
  {
    changelist[i].state = -1;
  }
  listUsed = 0;
}

bool KeyPad::addtoList(u16 id)
{
  if(listUsed < MULTIPRESS)
  {
    changelist[listUsed] = id;
    listUsed ++;
  }
  else
  {
    return false;
  }
  return true;
}

//
// void KeyPad::updateList()
// {
//   for(int i = 0; i < MULTIPRESS; i++)
//   {
//     list[i].state = -1;
//     //list[i].xy = 0xFF;
//   }
//
//   int i = 0;
//   for(int y = 0; y < YSIZE; y++)
//   {
//     for(int x = 0; x < XSIZE; x++)
//     {
//       if(i == MULTIPRESS)
//       return;
//
//       if(bitRead(keypadChanged[x], y) == true)
//       {
//         switch(rotation)
//         {
//           break;
//           case 1:
//           list[i].id = y * 0x10 + (7 - x);
//           break;
//           case 2:
//           list[i].id = (7 - x) * 0x10 + (7 - y);
//           break;
//           case 3:
//           list[i].id = (7 - y) * 0x10 + x;
//           break;
//           default:
//           list[i].id = xytoxy(x, y);
//         }
//
//         if(keypadVelocity[x][y])
//         {
//           list[i].velocity = keypadVelocity[x][y];
//         }
//         else
//         {
//           list[i].velocity = 0;
//         }
//         i++;
//         bitWrite(keypadChanged[x], y, 0);
//       }
//     }
//   }
// }

u16 KeyPad::checkXY(u8 x, u8 y, bool no_rotation)
{
  return KeyPad::checkXY(xytoxy(x, y), no_rotation);
}

u16 KeyPad::checkXY(u8 xy, bool no_rotation)
{
  if(!no_rotation)
  xy = xyReverseRotation(xy);
  return keypadVelocity[(xy & 0xF0) >> 4][xy & 0x0F];
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
