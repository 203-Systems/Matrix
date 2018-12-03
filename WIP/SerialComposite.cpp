#include "SerialComposite.h"

void begin()
{
  CompositeSerial.begin();
  Serial1.begin(115200);
  //Serial2.begin(115200); Serial2 is unused
  Serial3.begin(115200);
}
u32 available(SERIALS selector = USBCDC)
{
  switch (selector)
  {
    case USBCDC:
    return CompositeSerial.available();
    case USBSB:
    if(!powercord_enable)
    return Serial1.available();
    // case SERIAL2:
    // return Serial2.available();
    case MATRIXMOD:
    return Serial3.available();
  }
}
// u32 read(uint8 * buf, uint32 len, SERIALS selector = USBCDC)
// {
//   switch (selector)
//   {
//     case USBCDC:
//     return CompositeSerial.read(buf, len);
//     case USBSB:
//     if(!powercord_enable)
//     return Serial1.read(buf, len);
//     // case SERIAL2:
//     // return Serial2.read(buf, len);
//     case MATRIXMOD:
//     return Serial3.read(buf, len);
//   }
// }

int peek(SERIALS selector = USBCDC)
{
  switch (selector)
  {
    case USBCDC:
    return CompositeSerial.peek();
    case USBSB:
    if(!powercord_enable)
    return Serial1.peek();
    // case SERIAL2:
    // return Serial2.peek();
    case MATRIXMOD:
    return Serial3.peek();
  }
}

int read(SERIALS selector = USBCDC)
{
  switch (selector)
  {
    case USBCDC:
    return CompositeSerial.read();
    case USBSB:
    if(!powercord_enable)
    return Serial1.read();
    // case SERIAL2:
    // return Serial2.read();
    case MATRIXMOD:
    return Serial3.read();
  }
}

int availableForWrite(SERIALS selector = USBCDC)
{
  switch (selector)
  {
    case USBCDC:
    return CompositeSerial.availableForWrite();
    case USBSB:
    if(!powercord_enable)
    return Serial1.availableForWrite();
    // case SERIAL2:
    // return Serial2.availableForWrite();
    case MATRIXMOD:
    return Serial3.availableForWrite();
  }
}

void flush(SERIALS selector = USBCDC)
{
  switch (selector)
  {
    case USBCDC:
    return CompositeSerial.flush();
    case USBSB:
    if(!powercord_enable)
    return Serial1.flush();
    // case SERIAL2:
    // return Serial2.flush();
    case MATRIXMOD:
    return Serial3.flush();
  }
}

size_t write(uint8 byte, SERIALS selector = USBCDC)
{
  switch (selector)
  {
    case USBCDC:
    return CompositeSerial.write(byte);
    case USBSB:
    if(!powercord_enable)
    return Serial1.write(byte);
    // case SERIAL2:
    // return Serial2.write(byte);
    case MATRIXMOD:
    return Serial3.write(byte);
  }
}

size_t write(const char *str, SERIALS selector = USBCDC)
{
  switch (selector)
  {
    case USBCDC:
    return CompositeSerial.write(*str);
    case USBSB:
    if(!powercord_enable)
    return Serial1.write(*str);
    // case SERIAL2:
    // return Serial2.write(*str);
    case MATRIXMOD:
    return Serial3.write(*str);
  }
}

// size_t write(const uint8 * buf, uint32 len, SERIALS selector = USBCDC)
// {
//   switch (selector)
//   {
//     case USBCDC:
//     return CompositeSerial.write(buf, len);
//     case USBSB:
//     if(!powercord_enable)
//     return Serial1.write(buf, len);
//     // case SERIAL2:
//     // return Serial2.write(byte, len);
//     case MATRIXMOD:
//     return Serial3.write(buf, len);
//   }
// }
