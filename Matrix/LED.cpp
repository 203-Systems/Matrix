#include "LED.h"

LED::LED()
{
  CRGB leds[NUM_LEDS];
  FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS);
};

void LED::NoteOn(uint8 pallette, uint8 note, uint8 velocity)
{
  //TODO
}
void LED::NoteOff(uint8 note)
{
  //TODO
}

void LED::Off(uint8 X, uint8 Y )
{
  //TODO
}

void LED::On(uint8 X, uint8 Y )
{
  //TODO
}

void LED::SetW(uint8 X, uint8 Y, uint8 w)
{
  //TODO
}

void LED::SetRGB(uint8 X, uint8 Y, uint8 R, uint8 G, uint8 B)
{
  //TODO
}

void LED::SetWRGB(uint8 X, uint8 Y, uint8 W, uint8 R, uint8 G, uint8 B)
{
  //TODO
}

void LED::SetHEX(uint8 X, uint8 Y, uint64 WRGB)
{
  //TODO
}

void LED::SetPallette(uint8 X, uint8 Y, uint8 w)
{
  //TODO
}
