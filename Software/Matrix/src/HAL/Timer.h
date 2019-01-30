#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include "../Parameter/MatrixParameter.h"

class Timer
{
public:
  Timer();
  bool tick(u16 ms);
  bool isLonger(u16 ms);
  u32 sinceLastTick();
  void recordCurrent();
private:
  u32 previous = 0;
};

#endif
