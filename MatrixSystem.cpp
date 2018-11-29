#include "MatrixSystem.h"

MatrixSystem::MatrixSystem()
{
}

void MatrixSystem::VariableLoad()
{

}


//Sysex set
void MatrixSystem::Reset()
{
  digitalWrite(RESET_PIN,LOW);
}

void MatrixSystem::Setdevice_id()
{
  device_id = CompositeSerial.read();
  MatrixSystem::Reset();
}


void MatrixSystem::EnterBootloader()
{
  MatrixSystem::Reset();
}

void MatrixSystem::InitializeDevice()
{
  //TODO
}

void MatrixSystem::UpdateColourPaletteRGB()
{
  if(CompositeSerial.peek() < 128)
  {
    colour_pallette[2][CompositeSerial.read()] = MatrixSystem::WRGBtoHEX(0,CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read());
  }
  else if(CompositeSerial.peek() == 255)
  {
    return;
  }
}

void MatrixSystem::UpdateColourPaletteWRGB()
{
  if(CompositeSerial.peek() < 128)
  {
    colour_pallette[2][CompositeSerial.read()] = MatrixSystem::WRGBtoHEX(CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read());
  }
  else if(CompositeSerial.peek() == 255)
  {
    return;
  }
}

void MatrixSystem::ResetColourPalette()
{
  for(int i = 0; i < sizeof(colour_pallette[0]); i++)
  {
    colour_pallette[2][i] = colour_pallette[0][i];
  }
}

void MatrixSystem::SetGamma(bool g)
{
  gamma_enable = g;
}

void MatrixSystem::UpdateCustomKeymap()
{
  while(CompositeSerial.peek() != 255)
  {
    keymap[CompositeSerial.read()][CompositeSerial.read()] = CompositeSerial.read();
  }
}

void MatrixSystem::ResetCustomKeymap()
{
  for(int x = 0; x < KEYPADX; x++)
  {
    for(int y = 0; y < KEYPADY; y++)
    {
      keymap[x][y] = defaultkeymap[x][y];
    }
  }
}

void MatrixSystem::SetBrightness(uint8_t b)
{
  brightness = b;
  MatrixSystem::Reset();
}


void MatrixSystem::SetTouchSensitive(uint8_t s)
{
  touch_sensitive = s;
}

//Sysex Get
void MatrixSystem::GetDeviceInfo()
{
  //TODO
}

void MatrixSystem::GetModuleCount()
{
  //TODO
}

void MatrixSystem::GetModuleInfo()
{

}

void MatrixSystem::Getdevice_id()
{
  CompositeSerial.write((uint8_t)0);
  CompositeSerial.write(14);
  CompositeSerial.write(3);
  CompositeSerial.write(device_id);
}


void MatrixSystem::GetAllParameter()
{
  //TODO
}

void MatrixSystem::GetColorPaletteRGB()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(20);

  for(uint8_t i = 0; i < sizeof(colour_pallette[3]); i++)
  {
    CompositeSerial.write(i);
    CompositeSerial.write(colour_pallette[i] && 0xFF0000);
    CompositeSerial.write(colour_pallette[i] && 0xFF00);
    CompositeSerial.write(colour_pallette[i] && 0xFF);
  }
  CompositeSerial.write(255);
}

void MatrixSystem::GetColorPaletteWRGB()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(21);

  for(uint8_t i = 0; i < sizeof(colour_pallette[3]); i++)
  {
    CompositeSerial.write(i);
    CompositeSerial.write(colour_pallette[i] && 0xFF000000);
    CompositeSerial.write(colour_pallette[i] && 0xFF0000);
    CompositeSerial.write(colour_pallette[i] && 0xFF00);
    CompositeSerial.write(colour_pallette[i] && 0xFF);
  }
  CompositeSerial.write(255);
}

void MatrixSystem::GetGammaState()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(24);
}

void MatrixSystem::GetCustomKeymap()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(25);
}

void MatrixSystem::GetBrightness()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(25);
    CompositeSerial.write(brightness);
}

void MatrixSystem::GetTouchSensitive()
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

uint8_t BottomLEDrotation(int index)
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
