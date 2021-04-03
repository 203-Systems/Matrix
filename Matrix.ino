/*
Project Matrix
Copyright © 203 Industries 2016–2020. All rights reserved.
*/

#include <Arduino.h>
#include <USBComposite.h>
#include <FastLED.h>
#include "src/Parameter/MatrixVariable.h"
#include "src/Parameter/MatrixParameter.h"
#include "src/Core/MatrixSystem.h"
#include "src/HAL/KeyPad.h"p0
#include "src/HAL/Touch.h"
#include "src/HAL/LED.h"
#include "src/HAL/Timer.h"
#include "src/Protocol/MIDI.h"
#include "src/Components/UI.h"

UI UI;
MIDI Midi;
LED LED;
KeyPad KeyPad; 
Touch Touch;
Timer keypadTimer;
Timer ledTimer;
MicroTimer microTimer;
USBCompositeSerial CompositeSerial;

bool flag_leftFN = false;

void setup()
{
  //loadDeviceSerialNumber();
  loadDeviceConfig();
  setupEEPROM();
  variableLoad();
  setupUSB();
  setupHardware();
  setupPalette();
  specialBoot();

  if(midi_serial)
  {
    Serial4.begin(57600);
  }

  UI.enterBootAnimation();

#ifdef DEBUG
  CompositeSerial.println("Enter Main Program");
#endif
}

void readKey()
{
  if (KeyPad.scan())
  {
    if (fn_hold)
    {
      if (KeyPad.fn.hold && !flag_leftFN)
      {
        Midi.sendNoteOff(0, keymap_fn[current_keymap], 0);
        UI.enterFNmenu();
        flag_leftFN = true; //Prevent back to FN
      }
      else if (KeyPad.fn.state == PRESSED)
      {
        Midi.sendNoteOn(0, keymap_fn[current_keymap], 127);
      }
      else if (KeyPad.fn.state == RELEASED)
      {
        Midi.sendNoteOff(0, keymap_fn[current_keymap], 0);
        flag_leftFN = false;
      }
    }
    else
    {
      if (KeyPad.fn.state == PRESSED)
        UI.enterFNmenu();
    }

    for (u8 i = 0; i < MULTIPRESS; i++)
    {
      if (KeyPad.changelist[i] == 0xFFFF)
        break;
      u8 x = xytox(KeyPad.changelist[i]);
      u8 y = xytoy(KeyPad.changelist[i]);
      if (KeyPad.getKey(KeyPad.changelist[i]).state == PRESSED)
      {
        Midi.sendXYon(KeyPad.changelist[i], KeyPad.getKey(KeyPad.changelist[i]).velocity * 127);
      }
      else if (KeyPad.getKey(KeyPad.changelist[i]).state == RELEASED)
      {
        Midi.sendXYoff(KeyPad.changelist[i], 0);
      }
    }
  }
}
void readTouch()
{
if (Touch.scan())
  {
    switch(touch_mode)
    {
      case 0:
        for (u8 i = 0; i < 8; i++)
        {
          if (Touch.changelist[i] == 0xFFFF)
            break;
          if (Touch.getKey(Touch.changelist[i]).state == PRESSED)
          {
            #ifdef DEBUG
            CompositeSerial.print("Touch Key #");
            CompositeSerial.print(Touch.changelist[i]);
            CompositeSerial.println(" Pressed");
            #endif
            Midi.sendNoteOn(0, touch_keymap[current_keymap][Touch.changelist[i]], Touch.getKey(Touch.changelist[i]).velocity * 127);
          }
          else if (Touch.getKey(Touch.changelist[i]).state == RELEASED)
          {
            #ifdef DEBUG
            CompositeSerial.print("Touch Key #");
            CompositeSerial.print(Touch.changelist[i]);
            CompositeSerial.println(" Released");
            #endif
            Midi.sendNoteOff(0, touch_keymap[current_keymap][Touch.changelist[i]], 0);
          }
        }
        break;
      case 1:
        float value = Touch.calculatePercentage();
        if (value >= 0)
        {
          Midi.sendControlChange(0, 0, value * 127);
          // Midi.sendXYon((u8)(value * 7.99), 127);
        }
        break;
    }
  }
}

void loop()
{
  Midi.poll();

  // if(LED.changed)
  // {
  //   LED.update();
  //   LED.changed = false;
  // }

  if (keypadTimer.tick(keypad_scanrate_micros))
  {
    readKey();
    readTouch();
  }

  if (ledTimer.tick(fps_micros))
  {
    LED.update();
    LED.changed = false;
    Midi.offScan();
  }
}
