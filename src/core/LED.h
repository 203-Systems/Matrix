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
  void setBrightness(u8 b);
  void fill(u64 WRGB, bool overlay = false);

  // void setLED(INDEXMoDE indexmode, LEDMoDE ledmode, u8 x1, u8 y1, u64 p1, u8 p2, u8 p3, u8 p4);

  //Raw index - for BottomLED ，PoWERCoRD and raw strap.
  void off(u8 index, bool overlay = false);
  void on(u8 index, bool overlay = false);
  void setW(u8 index, u8 w, bool overlay = false);
  void setRGB(u8 index, u8 r, u8 g, u8 b, bool overlay = false);
  void setWRGB(u8 index, u8 w, u8 r, u8 g, u8 b, bool overlay = false);
  void setHEX(u8 index, u64 hex, bool overlay = false, bool ignore_gamma = false);
  void setPalette(u8 index, u8 pick_palette, u8 colour, bool overlay = false);

  //XY
  void offXY(u8 x, u8 y, bool overlay = false);
  void onXY(u8 x, u8 y, bool overlay = false);
  void setXYW(u8 x, u8 y, u8 w, bool overlay = false);
  void setXYRGB(u8 x, u8 y, u8 w, u8 g, u8 b, bool overlay = false);
  void setXYWRGB(u8 x, u8 y, u8 w, u8 r, u8 g, u8 b, bool overlay = false);
  void setXYHEX(u8 x, u8 y, u64 WRGB, bool overlay = false, bool ignore_gamma = false);
  void setXYPalette(u8 x, u8 y, u8 pick_palette, u8 colour, bool overlay = false);

  //Processing
  void update();
  void rainbow();
  void fillRegionOff(u8 x1, u8 y1, u8 x2, u8 y2, bool overlay = false);
  void fillRegionOn(u8 x1, u8 y1, u8 x2, u8 y2, bool overlay = false);
  void fillRegionW(u8 x1, u8 y1, u8 x2, u8 y2, u8 w, bool overlay = false);
  void fillRegionWRGB(u8 x1, u8 y1, u8 x2, u8 y2, u8 w, u8 r, u8 g, u8 b, bool overlay = false);
  void fillRegionRGB(u8 x1, u8 y1, u8 x2, u8 y2, u8 r, u8 g, u8 b, bool overlay = false);
  void fillRegionHEX(u8 x1, u8 y1, u8 x2, u8 y2, u64 hex, bool overlay = false , bool ignore_gamma = false);
  void fillRegionPalette(u8 x1, u8 y1, u8 x2, u8 y2, u8 p, u8 c, bool overlay = false);
  u64 applyGamma(u64 hex);
  void enableOverlayMode();
  void disableOverlayMode();

private:
  boolean overlay_mode = false;
  CRGB leds[NUM_TOTAL_LEDS];
  CRGB buffer[NUM_TOTAL_LEDS];
};




#endif
