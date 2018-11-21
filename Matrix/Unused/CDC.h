#ifndef CDC_h
#define CDC_h

class CDC
{
public:
  void poll();
  void Decode();
  void CDCMIDI();
}

extern CDC CDC;

#endif
