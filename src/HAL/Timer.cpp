#include "Timer.h"

Timer::Timer()
{
  Timer::recordCurrent();
}

boolean Timer::tick(u32 ms)
{
  if(millis() < previous)
    previous = 0;

  if(Timer::isLonger(ms))
  {
    Timer::recordCurrent();
    return true;
  }
  return false;
}

boolean Timer::isLonger(u32 ms)
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

MicroTimer::MicroTimer()
{
  MicroTimer::recordCurrent();
}

boolean MicroTimer::tick(u32 ms)
{
  if(micros() < previous)
    previous = 0;

  if(MicroTimer::isLonger(ms))
  {
    MicroTimer::recordCurrent();
    return true;
  }
  return false;
}

boolean MicroTimer::isLonger(u32 ms)
{
  return (previous + ms) <= micros();
}

u32 MicroTimer::sinceLastTick()
{
  return micros() - previous;
}

void MicroTimer::recordCurrent()
{
  previous = micros();
}
