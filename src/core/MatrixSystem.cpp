#include "MatrixSystem.h"

MatrixSystem::MatrixSystem()
{
}

void MatrixSystem::variableLoad()
{

}


//Sysex set
void MatrixSystem::reset()
{
  digitalWrite(REset_PIN,LOW);
}

void MatrixSystem::setDeviceID()
{
  device_id = CompositeSerial.read();
  MatrixSystem::Reset();
}


void MatrixSystem::enterBootloader()
{
  MatrixSystem::Reset();
}

void MatrixSystem::initializeDevice()
{
  //TODO
}

void MatrixSystem::updateColourPaletteRGB()
{
  if(CompositeSerial.peek() < 128)
  {
    palette[2][CompositeSerial.read()] = MatrixSystem::WRGBtoHEX(0,CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read());
  }
  else if(CompositeSerial.peek() == 255)
  {
    return;
  }
}

void MatrixSystem::updateColourPaletteWRGB()
{
  if(CompositeSerial.peek() < 128)
  {
    palette[2][CompositeSerial.read()] = MatrixSystem::WRGBtoHEX(CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read());
  }
  else if(CompositeSerial.peek() == 255)
  {
    return;
  }
}

void MatrixSystem::resetColourPalette()
{
  for(int i = 0; i < sizeof(palette[0]); i++)
  {
    palette[2][i] = palette[0][i];
  }
}

void MatrixSystem::setGamma(bool g)
{
  gamma_enable = g;
}

void MatrixSystem::updateCustomKeymap()
{
  while(CompositeSerial.peek() != 255)
  {
    keymap[CompositeSerial.read()][CompositeSerial.read()] = CompositeSerial.read();
  }
}

void MatrixSystem::resetCustomKeymap()
{
  for(int x = 0; x < KEYPADX; x++)
  {
    for(int y = 0; y < KEYPADY; y++)
    {
      keymap[x][y] = defaultKeymap[x][y];
    }
  }
}

void MatrixSystem::setBrightness(uint8_t b)
{
  brightness = b;
  MatrixSystem::reset();
}


void MatrixSystem::setTouchSensitive(uint8_t s)
{
  touch_sensitive = s;
}

//Sysex get
void MatrixSystem::getDeviceInfo()
{
  //TODO
}

void MatrixSystem::getModuleCount()
{
  //TODO
}

void MatrixSystem::getModuleInfo()
{

}

void MatrixSystem::getdevice_id()
{
  CompositeSerial.write((uint8_t)0);
  CompositeSerial.write(14);
  CompositeSerial.write(3);
  CompositeSerial.write(device_id);
}


void MatrixSystem::getAllParameter()
{
  //TODO
}

void MatrixSystem::getColorPaletteRGB()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(20);

  for(uint8_t i = 0; i < sizeof(palette[3]); i++)
  {
    CompositeSerial.write(i);
    CompositeSerial.write(palette[i] && 0xFF0000);
    CompositeSerial.write(palette[i] && 0xFF00);
    CompositeSerial.write(palette[i] && 0xFF);
  }
  CompositeSerial.write(255);
}

void MatrixSystem::getColorPaletteWRGB()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(21);

  for(uint8_t i = 0; i < sizeof(palette[3]); i++)
  {
    CompositeSerial.write(i);
    CompositeSerial.write(palette[i] && 0xFF000000);
    CompositeSerial.write(palette[i] && 0xFF0000);
    CompositeSerial.write(palette[i] && 0xFF00);
    CompositeSerial.write(palette[i] && 0xFF);
  }
  CompositeSerial.write(255);
}

void MatrixSystem::getGammaState()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(24);
}

void MatrixSystem::getCustomKeymap()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(25);
}

void MatrixSystem::getBrightness()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(25);
    CompositeSerial.write(brightness);
}

void MatrixSystem::getTouchSensitive()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(31);
  CompositeSerial.write(touch_sensitive);
}

//Math
uint8_t MatrixSystem::WRGBtoHEX(uint8_t W, uint8_t R, uint8_t G, uint8_t B)
{
  return W*0x10000000+R*0x10000+G*0x100+B;
}

uint8_t MatrixSystem::XYtoIndex(uint8_t X, uint8_t Y)
{

  switch (rotation)
  {
    case 1: //90
    return (KEYPADY - Y - 1) + X * KEYPADX;
    case 2: //180
    return (KEYPADX - X - 1) + (KEYPADY - Y - 1) * KEYPADY;
    case 3: //270
    return Y + (KEYPADX - X - 1) * KEYPADX;
    default:
    return X+Y*KEYPADX;
  }
}

uint8_t bottomLEDrotation(int index)
{
  switch (rotation)
  {
    case 1: //90
    if(index >= NUM_BOTTOM_LEDS/4 * 3 - 1)
    {
      return index - NUM_BOTTOM_LEDS/4 * 3;
    }
    return index + NUM_BOTTOM_LEDS/4 * 1;
    case 2: //180
    if(index >= NUM_BOTTOM_LEDS/4 * 2 - 1)
    {
      return index - NUM_BOTTOM_LEDS/4 * 2;
    }
    return index + NUM_BOTTOM_LEDS/4 * 2;
    case 3: //270
    if(index >= NUM_BOTTOM_LEDS/4 * 1 - 1)
    {
      return index - NUM_BOTTOM_LEDS/4 * 1;
    }
    return index + NUM_BOTTOM_LEDS/4 * 3;
    default:
    return index;
  }
}
