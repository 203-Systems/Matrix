#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "../parameter/MatrixVariable.h"
#include "../parameter/MatrixParameter.h"
#include "../core/MatrixSystem.h"
#include <FastLED.h>

// enum LEDMoDE{ on, off, w, rgb, wrgb, hex, palette};
// enum INDEXMoDE{ INDEX, XY };

class LED
{
public:
  LED();
  void setBrightness(uint8_t b);
  void fill(uint64_t WRGB, bool overlay = false);

  // void setLED(INDEXMoDE indexmode, LEDMoDE ledmode, uint8_t x1, uint8_t y1, uint64_t p1, uint8_t p2, uint8_t p3, uint8_t p4);

  //XY
  void off(uint8_t x, uint8_t y, bool overlay = false);
  void on(uint8_t x, uint8_t y, bool overlay = false);
  void setW(uint8_t x, uint8_t y, uint8_t w, bool overlay = false);
  void setRGB(uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B, bool overlay = false);
  void setWRGB(uint8_t x, uint8_t y, uint8_t W, uint8_t R, uint8_t G, uint8_t B, bool overlay = false);
  void setHEX(uint8_t x, uint8_t y, uint64_t WRGB, bool overlay = false);
  void setPalette(uint8_t x, uint8_t y, uint8_t pick_palette, uint8_t colour, bool overlay = false);

  //Raw index - for BottomLED ，PoWERCoRD and raw strap.
  void off(uint8_t index, bool overlay = false);
  void on(uint8_t index, bool overlay = false);
  void setW(uint8_t index, uint8_t w, bool overlay = false);
  void setRGB(uint8_t index, uint8_t R, uint8_t G, uint8_t B, bool overlay = false);
  void setWRGB(uint8_t index, uint8_t W, uint8_t R, uint8_t G, uint8_t B, bool overlay = false);
  void setHEX(uint8_t index, uint64_t WRGB, bool overlay = false);
  void setPalette(uint8_t index, uint8_t pick_palette, uint8_t colour, bool overlay = false);

  //Processing
  void update();
  void rainbow();
  void fillRegion(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint64_t WRGB, bool overlay = false);
  void fillRegion(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t W, bool overlay = false);
  void fillRegion(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t P, uint8_t C, bool overlay = false);
  void fillRegion(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t W, uint8_t R, uint8_t G, uint8_t B, bool overlay = false);
  void fillRegion(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t R, uint8_t G, uint8_t B, bool overlay = false);
  uint64_t applyGamma(uint64_t WRGB);

  void enableOverlayMode();
  void disableOverlayMode();
private:
  boolean overlay_mode = false;
  CRGB leds[NUM_TOTAL_LEDS];
  CRGB buffer[NUM_TOTAL_LEDS];
};



#endif
