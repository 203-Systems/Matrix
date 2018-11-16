#include <WS2812B.h>
#include <USBMIDI.h>
#include <USBComposite.h>


WS2812B LED = WS2812B(NUM_LEDS);


int brightness = 64;

unsigned long previousMillis = 0;

uint8_t KeyMap [8][8] =
{ {64, 65, 66, 67, 96, 97, 98, 99},
  {60, 61, 62, 63, 92, 93, 94, 95},
  {56, 57, 58, 59, 88, 89, 90, 91},
  {52, 53, 54, 55, 84, 85, 86, 87},
  {48, 49, 50, 51, 80, 81, 82, 83},
  {44, 45, 46, 47, 76, 77, 78, 79},
  {40, 41, 42, 43, 72, 73, 74, 75},
  {36, 37, 38, 39, 68, 69, 70, 71} };

uint8_t LEDGamma[] =
{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255};



int IndexInKeyMap(int num)
{
  for (int y = 0; y < sizeof(KeyMap); y++)
  {
    for (int x = 0; x < sizeof(KeyMap[0]); x++)
    {
      if (KeyMap[y][x] == num)
        return x + y * 8;
    }
  }
  return -1;
}

class usbmidi : public USBMidi
{
    virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity)
    {
      LED.setPixelColor(IndexInKeyMap(note), 0);
      //CompositeSerial.println(channel + " off " + note + " " + velocity);
    }

    virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity)
    {
      LED.setPixelColor(IndexInKeyMap(note), colour[velocity]);
      //CompositeSerial.println(channel + " on " + note + " " + velocity);
    }
};



void setup()
{
  usbmidi.registerComponent();
  USBComposite.setProductString("Matrix LED Proto");
  USBComposite.setVendorId(0x203);
  USBComposite.setProductId(0x801);
  CompositeSerial.registerComponent();
  USBComposite.begin();
  LED.begin();
  LED.show();
  LED.setBrightness(brightness);
}

void loop()
{
  usbmidi.poll();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000 / FPS)
  {
    previousMillis = currentMillis;
    LED.show();
  }
}

int WhereInKeyMap(int num)
{
  for (int y = 0; y < sizeof(KeyMap); y++)
  {
    for (int x = 0; x < sizeof(KeyMap[0]); x++)
    {
      if (KeyMap[y][x] == num)
        return x + y * 10;
    }
  }
  return -1;
}


int keyXYtoIndex(int x, int y)
{
  if (x == -1)
    return -1;
  return x + y * 8;
}

uint8_t red(uint32_t c)
{
  return (c >> 16);
}

uint8_t green(uint32_t c)
{
  return (c >> 8);
}

uint8_t blue(uint32_t c)
{
  return (c);
}
