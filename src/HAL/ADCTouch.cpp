#include "ADCTouch.h"

//#define DEBUG

ADCTouchSensor touchbar_buttons[8] =
{
  ADCTouchSensor(analog0, analog8),
  ADCTouchSensor(analog1, analog8),
  ADCTouchSensor(analog2, analog8),
  ADCTouchSensor(analog3, analog8),
  ADCTouchSensor(analog4, analog8),
  ADCTouchSensor(analog5, analog8),
  ADCTouchSensor(analog6, analog8),
  ADCTouchSensor(analog7, analog8)
};

ADCTouch::ADCTouch()
{

}

void ADCTouch::init()
{
  for(u8 i = 0; i < 8; i++)
  {
    touchbar_buttons[i].begin();
  }
}

bool ADCTouch::scan()
{
  bool changed = false;

  ADCTouch::cleanList();

  for(u8 x = 0; x < 8; x++)
  {
    int keyReading = touchbar_buttons[x].read();
    bool keyState = keyReading > touch_threshold || keyReading < touch_threshold * -1 ;

    #ifdef DEBUG
    CompositeSerial.print(touchbar_buttons[x].read());
    CompositeSerial.print("\t");
    #endif

    if(keyState && (touchState[x].kstate == IDLE || touchState[x].kstate == RELEASED))
    {
      if(ADCTouch::addtoList(x, PRESSED))
      {
        touchState[x].kstate = PRESSED;
        touchState[x].activeTime = millis();
        changed = true;
      }
    }
    else if(!keyState && (touchState[x].kstate == PRESSED || touchState[x].kstate == HOLD))
    {
      if(ADCTouch::addtoList(x, RELEASED))
      {
        touchState[x].kstate = RELEASED;
        touchState[x].activeTime = 0xFFFFFFFF;
        changed = true;
      }
    }
    else
    {
      switch(touchState[x].kstate )
      {
        case RELEASED:
        touchState[x].kstate = IDLE;
        break;
        case PRESSED:
        if(millis() - touchState[x].activeTime > HOLD_THRESHOLD)
        {
          if(ADCTouch::addtoList(x, HOLD))
          {
            touchState[x].kstate = HOLD;
            changed = true;
          }
        }
        break;
      }
    }
  }
  #ifdef DEBUG
  CompositeSerial.println();
  #endif
  return changed;
}

void ADCTouch::cleanList()
{
  for(u8 i = 0; i < 8; i++)
  {
    changelist[i].id = 0xFFFF;
    changelist[i].kstate = IDLE;
    listUsed = 0;
  }
}

bool ADCTouch::addtoList(u8 id, KeyStates keyState)
{
  if(listUsed == 8)
  return false;

  changelist[listUsed].id = touchbarRotate(id);
  changelist[listUsed].kstate = keyState;
  listUsed++;
}
