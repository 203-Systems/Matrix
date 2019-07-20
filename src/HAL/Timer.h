#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include "../Parameter/MatrixParameter.h"

class Timer
{
public:
  Timer();
  bool tick(u32 ms);
  bool isLonger(u32 ms);
  u32 sinceLastTick();
  void recordCurrent();
private:
  u32 previous = 0;
};

class MicroTimer
{
public:
  MicroTimer();
  bool tick(u32 ms);
  bool isLonger(u32 ms);
  u32 sinceLastTick();
  void recordCurrent();
private:
  u32 previous = 0;
};

#endif
