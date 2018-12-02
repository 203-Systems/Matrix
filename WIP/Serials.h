#ifndef SERIALCOMPOSITE_H
#define SERIALCOMPOSITE_H

#include <Arduino.h>
#include "../protocol/M2P.h"
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
#include "../core/MatrixSystem.h"
#include <USBComposite.h>

enum SERIALS { USBCDC, USBSB , SERIAL2, MATRIXMOD };

class Serials
{
public:
      Serials();
      void begin();
      bool isReady();
      uint32_t available(SERIALS selector);
      uint32_t read(uint8 * buf, uint32 len, SERIALS selector);
      int peek(SERIALS selector);
      int read(SERIALS selector);
      int availableForWrite(SERIALS selector);
      void flush(SERIALS selector);

      size_t write(uint8 byte, SERIALS selector);
      size_t write(const char * str, SERIALS selector);
      size_t write(const uint8 * buf, uint32 len, SERIALS selector);

private:
  //SERIALS CurrentSerial;
}
#endif
