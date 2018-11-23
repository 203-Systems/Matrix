#include "LED.h"

LED::LED()
{
  CRGB leds[NUM_TOTAL_LEDS];
  FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_TOTAL_LEDS);
  // if(POWERCORD){
  //   CRGB pc_leds[NUM_POWERCORD_LEDS];
  //   FastLED.addLeds<WS2812B, POWERCORD_PIN>(pc_leds, NUM_POWERCORD_LEDS);
  // }
};


void LED::NoteOn(uint8 channel, uint8 note, uint8 velocity)
{

  // if(POWERCORD)
  // {
  //
  // }
}
void LED::NoteOff(uint8 note)
{
  //TODO
}

void LED::Off(uint8 index)
{
  //TODO
}

void LED::On(uint8 index)
{
  //TODO
}

void LED::SetW(uint8 index, uint8 w)
{
  //TODO
}

void LED::SetRGB(uint8 index, uint8 R, uint8 G, uint8 B)
{
  //TODO
}

void LED::SetWRGB(uint8 index, uint8 W, uint8 R, uint8 G, uint8 B)
{
  //TODO
}

void LED::SetHEX(uint8 index, uint64 WRGB)
{
  //TODO
}

void LED::SetPallette(uint8 index, uint8 pallette, uint8 colour)
{
  //TODO
}
