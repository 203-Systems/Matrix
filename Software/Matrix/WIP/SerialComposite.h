#ifndef SERIALCOMPOSITE_H
#define SERIALCOMPOSITE_H

#include <Arduino.h>
#include "../protocol/M2P.h"
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"
#include <USBComposite.h>

enum SERIALS { USBCDC, USBSB , SERIAL2, MATRIXMOD };

class SerialComposite
{
public:
  SerialComposite();
  void begin();
  bool isReady();
  u32 available(SERIALS selector);
  //u32 read(uint8 * buf, uint32 len, SERIALS selector);
  int peek(SERIALS selector);
  int read(SERIALS selector);
  int availableForWrite(SERIALS selector);
  void flush(SERIALS selector);

  size_t write(uint8 byte, SERIALS selector);
  size_t write(const char * str, SERIALS selector);
  // size_t write(const uint8 * buf, uint32 len, SERIALS selector);

private:
  //SERIALS CurrentSerial;
};
#endif
