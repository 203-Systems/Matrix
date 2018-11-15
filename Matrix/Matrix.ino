#include <WS2812B.h>
#include <USBMIDI.h>
#include <USBComposite.h>


#define LEDPIN 6
#define NUM_LEDS 64
#define FPS 60

WS2812B LED = WS2812B(NUM_LEDS);

const uint32_t colour[128] = {0, 1973790, 8355711, 16731212, 16777215, 16711680, 5832704, 1638400, 16760172, 16733184, 5840128, 2562816, 16777036, 16776960, 5855488, 1644800, 8978252, 5570304,
                              1923328, 1321728, 5046092, 65280, 22784, 6400, 5046110, 65305, 22797, 6402, 5046152, 65365, 22813, 7954, 5046199, 65433, 22837, 6418, 5030911, 43519, 16722, 4121, 5015807, 22015, 7513,
                              2073, 5000447, 255, 89, 25, 8867071, 5505279, 1638500, 983088, 16731391, 16711935, 5832793, 1638425, 16731271, 16711764, 5832733, 2228243, 16717056, 10040576, 7950592, 4416512, 211200,
                              22325, 21631, 255, 17743, 2425036, 8355711, 2105376, 16711680, 12451629, 11529478, 6618889, 1084160, 65415, 43519, 11007, 4129023, 7995647, 11672189, 4202752, 16730624, 8970502, 7536405,
                              65280, 3931942, 5898097, 3735500, 5999359, 3232198, 8880105, 13835775, 16711773, 16744192, 12169216, 9502464, 8609031, 3746560, 1330192, 872504, 1381674, 1450074, 6896668, 11010058,
                              14569789, 14182940, 16769318, 10412335, 6796559, 1973808, 14483307, 8454077, 10131967, 9332479, 4210752, 7697781, 14745599, 10485760, 3473408, 1757184, 475648, 12169216, 4141312, 11755264, 4920578
                             };

int brightness = 64;

unsigned long previousMillis = 0;

uint8_t KeyMap [8][8] = {
  {64, 65, 66, 67, 96, 97, 98, 99},
  {60, 61, 62, 63, 92, 93, 94, 95},
  {56, 57, 58, 59, 88, 89, 90, 91},
  {52, 53, 54, 55, 84, 85, 86, 87},
  {48, 49, 50, 51, 80, 81, 82, 83},
  {44, 45, 46, 47, 76, 77, 78, 79},
  {40, 41, 42, 43, 72, 73, 74, 75},
  {36, 37, 38, 39, 68, 69, 70, 71}
};

uint8_t LEDGamma[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
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



int IndexInKeyMap(int num) {
  for (int y = 0; y < sizeof(KeyMap); y++) {
    for (int x = 0; x < sizeof(KeyMap[0]); x++) {
      if (KeyMap[y][x] == num)
        return x + y * 8;
    }
  }
  return -1;
}

class usbmidi : public USBMidi {
    virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) {
      LED.setPixelColor(IndexInKeyMap(note), 0);
      //CompositeSerial.println(channel + " off " + note + " " + velocity);
    }
    virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) {
      LED.setPixelColor(IndexInKeyMap(note), colour[velocity]);
      //CompositeSerial.println(channel + " on " + note + " " + velocity);
    }
};



void setup() {
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

void loop() {
  usbmidi.poll();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000 / FPS) {
    previousMillis = currentMillis;
    LED.show();
  }
}

int WhereInKeyMap(int num) {
  for (int y = 0; y < sizeof(KeyMap); y++) {
    for (int x = 0; x < sizeof(KeyMap[0]); x++) {
      if (KeyMap[y][x] == num)
        return x + y * 10;
    }
  }
  return -1;
}


int keyXYtoIndex(int x, int y) {
  if (x == -1)
    return -1;
  return x + y * 8;
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}
