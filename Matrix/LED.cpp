#include "LED.h"

LED::LED()
{
  CRGB leds[NUM_TOTAL_LEDS];
  FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_TOTAL_LEDS);
  // if(POWERCORD)
  //{
  //   CRGB pc_leds[NUM_POWERCORD_LEDS];
  //   FastLED.addLeds<WS2812B, POWERCORD_PIN>(pc_leds, NUM_POWERCORD_LEDS);
  // }
};


void LED::NoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{

  // if(POWERCORD)
  // {
  //
  // }
}
void LED::NoteOff(uint8_t note)
{
  //TODO
}

void LED::Off(uint8_t index)
{
  //TODO
}

void LED::On(uint8_t index)
{
  //TODO
}

void LED::SetW(uint8_t index, uint8_t w)
{
  //TODO
}

void LED::SetRGB(uint8_t index, uint8_t R, uint8_t G, uint8_t B)
{
  //TODO
}

void LED::SetWRGB(uint8_t index, uint8_t W, uint8_t R, uint8_t G, uint8_t B)
{
  //TODO
}

void LED::SetHEX(uint8_t index, uint64_t WRGB)
{
  //TODO
}

void LED::SetPallette(uint8_t index, uint8_t pallette, uint8_t colour)
{
  //TODO
}
