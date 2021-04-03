#include "KeyPad.h"
#include <USBComposite.h>

#ifdef DEBUG
#include <USBComposite.h>
#endif

KeyPad::KeyPad()
{


}

void KeyPad::init()
{
  if(fn_press_state)
  {
    pinMode(fn_pin, INPUT_PULLDOWN);
  }
  else
  {
    pinMode(fn_pin, INPUT_PULLUP);
  }
  switch(keypad_type)
  {
    case 1:
    #ifdef DEBUG
    CompositeSerial.print("KeyPad Mode 1 Initalized");
    #endif
    return KeyPad::initType1();
    case 2:
    #ifdef DEBUG
    CompositeSerial.print("KeyPad Mode 2 Initalized");
    #endif
    return KeyPad::initType2();
    // case 3:
    // #ifdef DEBUG
    // CompositeSerial.print("KeyPad Mode 3 Initalized");
    // #endif
    //return KeyPad::initType3();
  }
}

void KeyPad::initType1()
{
  pinMode(keypad_pins[0], OUTPUT); //SO_DATA
  pinMode(keypad_pins[1], OUTPUT); //SO_CLOCK

  pinMode(keypad_pins[4], OUTPUT); //SI_LATCH
  pinMode(keypad_pins[3], OUTPUT); //SI_CLOCK
  pinMode(keypad_pins[2], INPUT_PULLDOWN); //SI_DATA
}

void KeyPad::initType2()
{
  for(u8 x = 0; x < XSIZE; x ++)
  {
    pinMode(keypad_pins[x], OUTPUT);
    digitalWrite(keypad_pins[x], LOW);
  }
  for(u8 y = 0; y < YSIZE; y ++)
  {
    pinMode(keypad_pins[y + XSIZE], INPUT_PULLDOWN);
  }

}

/*void KeyPad::initType3()
{
  for(u8 x = 0; x < XSIZE; x ++)
  {
    pinMode(keypad_pins[x], OUTPUT);
    digitalWrite(keypad_pins[x], LOW);
  }
  for(u8 y = 0; y < YSIZE; y ++)
  {
    pinMode(keypad_pins[y + XSIZE], INPUT_PULLDOWN);
  }

}
*/

bool KeyPad::scan()
{
  KeyPad::cleanList();
  switch(keypad_type)
  {
    case 1:
    return KeyPad::scanType1();
    case 2:
    return KeyPad::scanType2();
    //case 3:
    //return KeyPad::scanType3();
  }
}

bool KeyPad::scanType1() //1.x 165/164 solution
{
  bool changed = false;

  changed = changed || scanFN();

  for (u8 x = 0; x < XSIZE; x++) //for 0 - 7 do
  {
    //shiftOut(keypad_pins[0], keypad_pins[1], MSBFIRST, 1 << x); // bit shift a logic high (1) value by i
    if( x == 0)
    {
      digitalWrite(keypad_pins[0], HIGH);
    }

    digitalWrite(keypad_pins[1], HIGH);
    digitalWrite(keypad_pins[0], LOW);
    digitalWrite(keypad_pins[1], LOW);

    digitalWrite(keypad_pins[4], LOW); //165's load Active at Low
    digitalWrite(keypad_pins[4], HIGH);


    for (s8 y = YSIZE-1; y >= 0; y--) //y could go negative so use int instead uint
    {
      digitalWrite(keypad_pins[3], LOW);

      keypadState[x][y] = KeyPad::updateKey(keypadState[x][y], digitalRead(keypad_pins[2]));
      if(keypadState[x][y].changed)
      {
        changed = true;
        if(!KeyPad::addtoList(xytoxy(x,y)))
        return changed;
        #ifdef DEBUG
        CompositeSerial.print("Key Action ");
        CompositeSerial.print(xytoxy(x,y), HEX);
        CompositeSerial.print(" ");
        CompositeSerial.print(KeyStatesString[keypadState[x][y].state]);
        CompositeSerial.print(" ");
        CompositeSerial.println(keypadState[x][y].velocity);
        #endif
      }

      digitalWrite(keypad_pins[3], HIGH);
    }
  }

  return changed;
}

bool KeyPad::scanType2()
{
  bool changed = false;

  changed = changed || scanFN();

  for(u8 x = 0; x < XSIZE; x ++)
  {
    digitalWrite(keypad_pins[x], HIGH);
    for(u8 y = 0; y < YSIZE; y ++)
    {
      keypadState[x][y] = KeyPad::updateKey(keypadState[x][y], digitalRead(keypad_pins[y+8]));
      if(keypadState[x][y].changed)
      {
        changed = true;
        #ifdef DEBUG
        CompositeSerial.print("Key Action ");
        CompositeSerial.print(xytoxy(x,y), HEX);
        CompositeSerial.print(" ");
        CompositeSerial.print(keypadState[x][y].state);
        CompositeSerial.print(" ");
        CompositeSerial.println(keypadState[x][y].velocity);
        #endif
        if(!KeyPad::addtoList(xytoxy(x,y)))
        return changed;
      }
    }
    digitalWrite(keypad_pins[x], LOW);
    delayMicroseconds(10); // To make the Keypad Matrix happy
  }

  return changed;
}
/*
bool KeyPad::scanType3()
{
  bool changed = false;

  changed = changed || scanFN();

  for(u8 x = 0; x < XSIZE; x ++)
  {
    digitalWrite(x, HIGH);
    for(u8 y = 0; y < YSIZE; y ++)
    {
      keypadState[x][y] = KeyPad::updateKey(keypadState[x][y], velocityCurve((float)4095 /analogRead(y + 8)));
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
*/
bool KeyPad::scanFN()
{
  if(fn_press_state)
  {
    fn = updateKey(fn, digitalRead(fn_pin));
  }
  else
  {
  fn = updateKey(fn, !digitalRead(fn_pin));
  }
  #ifdef DEBUG
  if(fn.changed)
  {
    CompositeSerial.print("FN Action ");
    CompositeSerial.print(fn.velocity);
    CompositeSerial.print(" ");
    CompositeSerial.print(fn.hold);
    CompositeSerial.print(" ");
    CompositeSerial.println(fn.holdTime());
  }
  #endif
  return fn.changed;
}

/*
Action Checklist:
Nothing (All)
To Long Term State(Pressed, Hold, Release)
Active (Idle, Release)
Release(Pressed, Active, Hold, Hold Actived)
Aftertouch (Pressed, Actived, Hold, Hold Actived)
*/

KeyInfo KeyPad::updateKey(KeyInfo currentKey, float input)
{
  currentKey.changed = false;

  if(currentKey.state == PRESSED)
  {
    currentKey.state = ACTIVED;
  }

  if(currentKey.state == RELEASED)
  {
    currentKey.state = IDLE;
    currentKey.hold = false;
  }

  if(currentKey.state == IDLE && input && millis() - currentKey.activeTime > debounce_threshold)
  {
    currentKey.state = PRESSED;
    currentKey.velocity = input;
    currentKey.activeTime = millis();
    currentKey.changed = true;
    return currentKey;
  }

  if(currentKey.state == ACTIVED && input == 0 && millis() - currentKey.activeTime > debounce_threshold)
  {
    currentKey.state = RELEASED;
    currentKey.velocity = 0;
    currentKey.activeTime = millis();
    currentKey.changed = true;
    return currentKey;
  }

  if(currentKey.state == ACTIVED && !currentKey.hold)
  {
    if(millis() - currentKey.activeTime > HOLD_THRESHOLD)
    {
      currentKey.hold = true;
      currentKey.changed = true;
      return currentKey;
    }
  }

  /*
  if(currentKey.state == ACTIVED)
  {
  if(abs(currentKey.velocity - input) > AFTERTOUCH_THRESHOLD)
  {
  currentKey.velocity = input;
  currentKey.changed = true;
  return currentKey;
}
}
*/

return currentKey;
}

void KeyPad::cleanList()
{
  for(u8 i = 0; i < MULTIPRESS; i++)
  {
    changelist[i] = 0xFFFF;
  }
  listUsed = 0;
}

bool KeyPad::addtoList(u16 id)
{
  if(listUsed < MULTIPRESS)
  {
    if(id < 0x10000)
    {
      changelist[listUsed] = xyRotation(id);
    }
    else
    {
      changelist[listUsed] = id;
    }
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
  return keypadState[xytox(xy)][xytoy(xy)].velocity;
}

KeyInfo KeyPad::getKey(u8 x, u8 y)
{
  return KeyPad::getKey(xytoxy(x,y));
}

KeyInfo KeyPad::getKey(u8 xy)
{
  xy = xyReverseRotation(xy);
  return keypadState[xytox(xy)][xytoy(xy)];
}


// void KeyPad::On(uint8 x, uint8 y)
// {
//   CompositeSerial.println(xyToIndex(x,y)*10+1);
//
//   switch (rotation)
//   {
//     case 1: //90
//     Midi.sendNoteOn(MIDIChannel, keymap[x][YSIZE - y - 1], 127);
//     break;
//     case 2: //180
//     Midi.sendNoteOn(MIDIChannel, keymap[YSIZE - y - 1][XSIZE - x - 1], 127);
//     break;
//     case 3: //270
//     Midi.sendNoteOn(MIDIChannel, keymap[XSIZE - x - 1][y], 127);
//     break;
//     default: //0
//     Midi.sendNoteOn(MIDIChannel, keymap[y][x], 127);
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
//     Midi.sendNoteOff(MIDIChannel, keymap[x][YSIZE - y - 1], 0);
//     break;
//     case 2: //180
//     Midi.sendNoteOff(MIDIChannel, keymap[YSIZE - y - 1][XSIZE - x - 1], 0);
//     break;
//     case 3: //270
//     Midi.sendNoteOff(MIDIChannel, keymap[XSIZE - x - 1][y], 0);
//     break;
//     default: //0
//     Midi.sendNoteOff(MIDIChannel, keymap[y][x], 0);
//   }
// }
