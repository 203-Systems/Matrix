#include "MatrixVariable.h"
#include "MIDI.h"
#include "LED.h"

LED::LED()
{
  FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS);
};

LED:: LEDonNote(int pallette, int note, int velocity);
LED:: LEDoffNote(int note);

LED:: LEDoff(int X, int Y );
LED:: LEDon(int X, int Y );
LED:: LEDonW(int X, int Y, int w);
LED:: LEDonRGB(int X, int Y, int R, int G, int B);
LED:: LEDonWRGB(int X, int Y, int W, int R, int G, int B);
LED:: LEDonHEX(int X, int Y, uint32_t WRGB)
{

}
LED:: LEDsetPallette(int X, int Y, int w);
