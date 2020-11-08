#include "TOUCH.h"
#include <USBComposite.h>

#ifdef DEBUG
#include <USBComposite.h>
#endif

Touch::Touch()
{
}

void Touch::init()
{
  switch (touch_type)
  {
  case 1:
#ifdef DEBUG
    CompositeSerial.print("touch Mode 1 Initalized");
#endif
    return Touch::initType1();
  default:
    return;
  }
}

void Touch::initType1()
{
  pinMode(touch_pins[0], OUTPUT); //SO_CLOCK
  pinMode(touch_pins[1], INPUT);  //SO_INPUT
  digitalWrite(touch_pins[0], LOW);
  touchState[0].state = IDLE;
}

bool Touch::scan()
{
  Touch::cleanList();
  switch (touch_type)
  {
  case 1:
    return Touch::scanType1();
  default:
    return false;
  }
}

bool Touch::scanType1() //TTP229-BSD (16Keys merged to 8Keys)
{
  bool changed = false;

  u8 lut[] = {4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3};
  bool newInput[16];
  for (u8 x = 0; x < 16; x++)
  {
    digitalWrite(touch_pins[0], HIGH);

    bool reading = digitalRead(touch_pins[1]);
    
    changed |= rawInput[lut[x]] != reading;
    newInput[lut[x]] = reading;
    
    digitalWrite(touch_pins[0], LOW);
  }

  if(changed)
  {
    #ifdef DEBUG    
    // filler = 0;
    // CompositeSerial.print("filler: ");
    // CompositeSerial.println(filler);
    CompositeSerial.print("Touch Action Raw ");
    for (u8 x = 0; x < 16; x++)
    {
      CompositeSerial.print(newInput[x]);
      CompositeSerial.print(" ");
    }
    CompositeSerial.println();
    #endif

    for (u8 x = 0; x < 16; x+=2)
    {
      u8 index = x >> 1;
      // CompositeSerial.print(index);
      // CompositeSerial.print(" Input: ");
      // CompositeSerial.print(newInput[x] || newInput[x + 1]);
      // CompositeSerial.print(", state: ");
      // CompositeSerial.println(KeyStatesString[touchState[index].state]);
      
      touchState[index] = Touch::updateKey(touchState[index], newInput[x] || newInput[x + 1]);
      if(touchState[index].changed)
      { 
        if(!Touch::addtoList(index))
          return changed;
        #ifdef DEBUG
        CompositeSerial.print("Touch Action ");
        CompositeSerial.print(index);
        CompositeSerial.print(" ");
        CompositeSerial.print(KeyStatesString[touchState[index].state]);
        CompositeSerial.print(" ");
        CompositeSerial.println(touchState[index].velocity);
        #endif
      }
      else
      {     
            // CompositeSerial.print(index);
            // CompositeSerial.print(" ");
            // CompositeSerial.print(KeyStatesString[touchState[index].state]);
            // CompositeSerial.println(" No Change");
      }
      rawInput[x] = newInput[x];
      rawInput[x + 1] = newInput[x + 1];
    }
  }
  return changed;
}

void Touch::cleanList()
{
  for (u8 i = 0; i < 8; i++)
  {
    changelist[i] = 0xFFFF;
  }
  listUsed = 0;
}

bool Touch::addtoList(u16 id)
{
  if (listUsed < 8)
  {
    changelist[listUsed] = touchbarRotation(id);
    listUsed++;
    return true;
  }
  else
  {
    return false;
  }
}

KeyInfo Touch::updateKey(KeyInfo currentKey, float input) 
{
  // CompositeSerial.print("Update Key: ");
  // CompositeSerial.print(KeyStatesString[currentKey.state]);
  // CompositeSerial.print(" ");
  // CompositeSerial.print(input);
  // CompositeSerial.print(" - ");
  currentKey.changed = false;

  if(currentKey.state == PRESSED)
  {
    // CompositeSerial.print(0);
    CompositeSerial.print("+");
    currentKey.state = ACTIVED;
  }

  if(currentKey.state == RELEASED)
  {
    // CompositeSerial.print(1);
    CompositeSerial.print("+");
    currentKey.state = IDLE;
    currentKey.hold = false;
  }

  if(currentKey.state == IDLE && input /*&& millis() - currentKey.activeTime > debounce_threshold*/)
  {
    // CompositeSerial.println(2);
    currentKey.state = PRESSED;
    currentKey.velocity = input;
    currentKey.activeTime = millis();
    currentKey.changed = true;
    return currentKey;
  } 

  if(currentKey.state == ACTIVED && input == 0 && millis() - currentKey.activeTime > debounce_threshold)
  {
    // CompositeSerial.println(3);
    currentKey.state = RELEASED;
    currentKey.velocity = 0;
    currentKey.activeTime = millis();
    currentKey.changed = true;
    return currentKey;
  }

  if(currentKey.state == ACTIVED && !currentKey.hold && millis() - currentKey.activeTime > HOLD_THRESHOLD)
  {
      // CompositeSerial.println(4);
      currentKey.hold = true;
      currentKey.changed = true;
      return currentKey;
  }
  // CompositeSerial.println(5);
  return currentKey;
}

KeyInfo Touch::getKey(u8 index)
{
  return touchState[index];
}

float Touch::calculatePercentage()
{
  s8 longest_start = -1;
  s8 longest_length = -1;
  s8 local_start = -1;
  bool last_state = false;

  for (u8 i = 0; i < 16; i++)
  {
    if (!rawInput[i])
    {
      local_start -1;
      last_state = false;
      continue;
    }
    if (!last_state)
    {
      local_start = i;
      last_state = true;
    }
    s8 local_length = i - local_start;
    if (local_length > longest_length)
    {
      longest_length = local_length;
      longest_start = local_start;
    }
  }

  if (longest_start == -1)
    return -1;
    

  float value = (longest_start + (float)longest_length / 2.0f) / 15;
  // CompositeSerial.println(value);
  if (value == last_percentage)
    return -2;

  last_percentage = value;

  return value;
}
