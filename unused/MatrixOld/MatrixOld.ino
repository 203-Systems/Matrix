#include <FastLED.h>
#include <USBMIDI.h>
#include <USBComposite.h>

CRGB leds[64];


int brightness = 16;

unsigned long previousMillis = 0;

uint8_t KeyMap [8][8] =
{ {64, 65, 66, 67, 96, 97, 98, 99},
  {60, 61, 62, 63, 92, 93, 94, 95},
  {56, 57, 58, 59, 88, 89, 90, 91},
  {52, 53, 54, 55, 84, 85, 86, 87},
  {48, 49, 50, 51, 80, 81, 82, 83},
  {44, 45, 46, 47, 76, 77, 78, 79},
  {40, 41, 42, 43, 72, 73, 74, 75},
  {36, 37, 38, 39, 68, 69, 70, 71}
};

uint32_t colour[128] =    //MatrixColorPallette WRGB
{
  0x00000000, //0
  0x001E1E1E, //1
  0x007F7F7F, //2
  0x004C4C4C, //3
  0x00FFFFFF, //4
  0x00FF0000, //5
  0x00590000, //6
  0x00190000, //7
  0x00FFBD6C, //8
  0x00FF5400, //9
  0x00591D00, //10
  0x00271B00, //11
  0x00FFFF4C, //12
  0x00FFFF00, //13
  0x00595900, //14
  0x00191900, //15
  0x0088FF4C, //16
  0x0054FF00, //17
  0x001D5900, //18
  0x00142B00, //19
  0x004CFF4C, //20
  0x0000FF00, //21
  0x00005900, //22
  0x00001900, //23
  0x004CFF5E, //24
  0x0000FF19, //25
  0x0000590D, //26
  0x00001902, //27
  0x004CFF88, //28
  0x0000FF55, //29
  0x0000591D, //30
  0x00001F12, //31
  0x004CFFB7, //32
  0x0000FF99, //33
  0x00005935, //34
  0x00001912, //35
  0x004CC3FF, //36
  0x0000A9FF, //37
  0x00004152, //38
  0x00001019, //39
  0x004C88FF, //40
  0x000055FF, //41
  0x00001D59, //42
  0x00000819, //43
  0x004C4CFF, //44
  0x000000FF, //45
  0x00000059, //46
  0x00000019, //47
  0x00874CFF, //48
  0x005400FF, //49
  0x00190064, //50
  0x000F0030, //51
  0x00FF4CFF, //52
  0x00FF00FF, //53
  0x00590059, //54
  0x00190019, //55
  0x00FF4C87, //56
  0x00FF0054, //57
  0x0059001D, //58
  0x00220013, //59
  0x00FF1500, //60
  0x00993500, //61
  0x00795100, //62
  0x00436400, //63
  0x00033900, //64
  0x00005735, //65
  0x0000547F, //66
  0x000000FF, //67
  0x0000454F, //68
  0x002500CC, //69
  0x007F7F7F, //70
  0x00202020, //71
  0x00FF0000, //72
  0x00BDFF2D, //73
  0x00AFED06, //74
  0x0064FF09, //75
  0x00108B00, //76
  0x0000FF87, //77
  0x0000A9FF, //78
  0x00002AFF, //79
  0x003F00FF, //80
  0x007A00FF, //81
  0x00B21A7D, //82
  0x00402100, //83
  0x00FF4A00, //84
  0x0088E106, //85
  0x0072FF15, //86
  0x0000FF00, //87
  0x003BFF26, //88
  0x0059FF71, //89
  0x0038FFCC, //90
  0x005B8AFF, //91
  0x003151C6, //92
  0x00877FE9, //93
  0x00D31DFF, //94
  0x00FF005D, //95
  0x00FF7F00, //96
  0x00B9B000, //97
  0x0090FF00, //98
  0x00835D07, //99
  0x00392B00, //100
  0x00144C10, //101
  0x000D5038, //102
  0x0015152A, //103
  0x0016205A, //104
  0x00693C1C, //105
  0x00A8000A, //106
  0x00DE513D, //107
  0x00D86A1C, //108
  0x00FFE126, //109
  0x009EE12F, //110
  0x0067B50F, //111
  0x001E1E30, //112
  0x00DCFF6B, //113
  0x0080FFBD, //114
  0x009A99FF, //115
  0x008E66FF, //116
  0x00404040, //117
  0x00757575, //118
  0x00E0FFFF, //119
  0x00A00000, //120
  0x00350000, //121
  0x001AD000, //122
  0x00074200, //123
  0x00B9B000, //124
  0x003F3100, //125
  0x00B35F00, //126
  0x004B1502  //127
};
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
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};



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
      leds[IndexInKeyMap(note)] = 0;
      //CompositeSerial.println(channel + " off " + note + " " + velocity);
    }

    virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity)
    {
      leds[IndexInKeyMap(note)] = colour[velocity];
      //CompositeSerial.println(channel + " on " + note + " " + velocity);
    }
};

usbmidi usbmidi;

void setup()
{
  FastLED.addLeds<NEOPIXEL, PB7>(leds, 64);
  usbmidi.registerComponent();
  USBComposite.setProductString("Matrix Prototype");
  USBComposite.setVendorId(0x203);
  USBComposite.setProductId(0x805);
  CompositeSerial.registerComponent();
  USBComposite.begin();
  FastLED.setBrightness(192);
}

void loop()
{
  usbmidi.poll();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000 / 100)
  {
    previousMillis = currentMillis;
    FastLED.show();
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
