#include "Timer.h"

Timer::Timer()
{
  Timer::recordCurrent();
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
  return (previous + ms) <= millis();
}

u32 Timer::sinceLastTick()
{
  return millis() - previous;
}

void Timer::recordCurrent()
{
  previous = millis();
}
