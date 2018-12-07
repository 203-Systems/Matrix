#include "Timer.h"

Timer::Timer()
{
  previous = millis();
}

boolean Timer::tick(u16 ms)
{
  if(Timer::isLonger(ms))
  {
    Timer::recordCurrent();
    return true;
  }
  return false;
}
boolean Timer::isLonger(u16 ms)
{
  return previous + ms <= millis();
}

u32 Timer::sinceLastTick()
{
  return millis() - previous;
}

u32 Timer::recordCurrent()
{
  previous = millis();
}
