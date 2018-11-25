#include "MatrixSystem.h"

MatrixSystem::MatrixSystem()
{
}

//Sysex Set
void MatrixSystem::Reset()
{
  digitalWrite(RESET_PIN,LOW);
}

void MatrixSystem::SetDeviceID()
{
  DeviceID = CompositeSerial.read();
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
  while(CompositeSerial.peek() != 255)
  {
    ColourPallette[3][CompositeSerial.read()] = MatrixSystem::WRGBtoHEX(0,CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read());
  }
}

void MatrixSystem::UpdateColourPaletteWRGB()
{
  while(CompositeSerial.peek() != 255)
  {
    ColourPallette[2][CompositeSerial.read()] = MatrixSystem::WRGBtoHEX(CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read(),CompositeSerial.read());
  }
}

void MatrixSystem::ResetColourPalette()
{
  for(int i = 0; i < sizeof(ColourPallette[0]); i++)
  {
    ColourPallette[2][i] = ColourPallette[0][i];
  }
}

void MatrixSystem::SetGamma(bool g)
{
  GammaEnable = g;
}

void MatrixSystem::UpdateCustomKeyMap()
{
  while(CompositeSerial.peek() != 255)
  {
    KeyMap[CompositeSerial.read()][CompositeSerial.read()] = CompositeSerial.read();
  }
}

void MatrixSystem::ResetCustomKeyMap()
{
  for(int x = 0; x < KEYPADX; x++)
  {
    for(int y = 0; y < KEYPADY; y++)
    {
      KeyMap[x][y] = DefaultKeyMap[x][y];
    }
  }
}

void MatrixSystem::SetBrightness(uint8_t b)
{
  Brightness = b;
}

void MatrixSystem::SetTouchSensitive(uint8_t s)
{
  TouchSensitive = s;
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

void MatrixSystem::GetDeviceID()
{
  CompositeSerial.write((uint8_t)0);
  CompositeSerial.write(14);
  CompositeSerial.write(3);
  CompositeSerial.write(DeviceID);
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

  for(uint8_t i = 0; i < sizeof(ColourPallette[3]); i++)
  {
    CompositeSerial.write(i);
    CompositeSerial.write(ColourPallette[i] && 0xFF0000);
    CompositeSerial.write(ColourPallette[i] && 0xFF00);
    CompositeSerial.write(ColourPallette[i] && 0xFF);
  }
  CompositeSerial.write(255);
}

void MatrixSystem::GetColorPaletteWRGB()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(21);

  for(uint8_t i = 0; i < sizeof(ColourPallette[3]); i++)
  {
    CompositeSerial.write(i);
    CompositeSerial.write(ColourPallette[i] && 0xFF000000);
    CompositeSerial.write(ColourPallette[i] && 0xFF0000);
    CompositeSerial.write(ColourPallette[i] && 0xFF00);
    CompositeSerial.write(ColourPallette[i] && 0xFF);
  }
  CompositeSerial.write(255);
}

void MatrixSystem::GetGammaState()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(24);
}

void MatrixSystem::GetCustomKeyMap()
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
}

void MatrixSystem::GetTouchSensitive()
{
  CompositeSerial.write((uint8_t)(0));
  CompositeSerial.write(14);
  CompositeSerial.write(31);
  CompositeSerial.write(TouchSensitive);
}

//Math
uint8_t MatrixSystem::WRGBtoHEX(uint8_t W, uint8_t R, uint8_t G, uint8_t B)
{
  return W*0x10000000+R*0x10000+G*0x100+B;
}

uint8_t MatrixSystem::XYtoIndex(uint8_t X, uint8_t Y)
{
  return X+Y*KEYPADX;
}
