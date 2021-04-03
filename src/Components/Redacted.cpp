#include "Redacted.h"

extern KeyPad KeyPad;
extern LED LED;
extern Timer keypadTimer;
extern MicroTimer microTimer;

void Redacted::run()
{
  // LED.enableOverlayMode();
  LED.fill(0, true);
  LED.update();
  u32 progress = 0;
  u32 length = sizeof(data);
  while(1)
  {
    if (keypadTimer.tick(20))
    {
      if (KeyPad.scan() && KeyPad.fn.state == RELEASED)
      {
        break;
      }
    }
    if (microTimer.tick(33333))
    {
      u8 bufferOffset = 1;
      for(u8 x = 0; x < 8; x ++)
      {
        if((data[progress] >> x) & 0x01)
        {
          for(u8 y = 0; y < 8; y++)
          {
            LED.setXYW(xytoxy(x, y), ((data[progress + bufferOffset] >> y) & 0x01) * 255, true);
          }
          bufferOffset ++;
        }
      }
      LED.update();
      progress += bufferOffset;
      if(progress > length)
        break;
    }
  }
  LED.fill(0, true);
  LED.update();
}