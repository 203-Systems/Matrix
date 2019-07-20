#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <FastLED.h>
#include "../Parameter/MatrixVariable.h"
#include "../Parameter/MatrixParameter.h"
#include "../Core/MatrixSystem.h"
//#include "../Components/Color.h"


// enum LEDMoDE{ on, off, w, rgb, wrgb, hex, palette};
// enum INDEXMoDE{ INDEX, XY };
enum Direction : u8 {up, right, down, left};

class LED
{
public:
  LED();
  void init();
  void nextBrightnessState();
  void setBrightness(u8 b);
  void setColourCorrection(u32 c);
  void dynamicBrightness(u16 mah);
  void fill(u32 WRGB, bool overlay = false);

  // void setLED(INDEXMoDE indexmode, LEDMoDE ledmode, u8 x1, u8 y1, u32 p1, u8 p2, u8 p3, u8 p4);

  //Raw index - for BottomLED ，PoWERCoRD and raw strap.
  void off(s16 index, bool overlay = false);
  void on(s16 index, bool overlay = false);
  void setW(s16 index, u8 w, bool overlay = false);
  void setRGB(s16 index, u8 r, u8 g, u8 b, bool overlay = false);
  void setWRGB(s16 index, u8 w, u8 r, u8 g, u8 b, bool overlay = false);
  void setHEX(s16 index, u32 hex, bool overlay = false, bool ignore_gamma = false);
  void setPalette(s16 index, u8 pick_palette, u8 colour, bool overlay = false);

  //XY
  void offXY(u8 xy, bool overlay = false);
  void onXY(u8 xy, bool overlay = false);
  void setXYW(u8 xy, u8 w, bool overlay = false);
  void setXYRGB(u8 xy, u8 w, u8 g, u8 b, bool overlay = false);
  void setXYWRGB(u8 xy, u8 w, u8 r, u8 g, u8 b, bool overlay = false);
  void setXYHEX(u8 xy, u32 WRGB, bool overlay = false, bool ignore_gamma = false);
  void setXYPalette(u8 xy, u8 pick_palette, u8 colour, bool overlay = false);

  //Processing
  void update();
  void rainbow();
  // void fillRegionOff(u8 xy1, u8 xy2, bool overlay = false);
  // void fillRegionOn(u8 xy1, u8 xy2, bool overlay = false);
  // void fillRegionW(u8 xy1, u8 xy2, u8 w, bool overlay = false);
  // void fillRegionWRGB(u8 xy1, u8 xy2, u8 w, u8 r, u8 g, u8 b, bool overlay = false);
  // void fillRegionRGB(u8 xy1, u8 xy2, u8 r, u8 g, u8 b, bool overlay = false);
  // void fillRegionHEX(u8 xy1, u8 xy2, u32 hex, bool overlay = false , bool ignore_gamma = false);
  // void fillRegionPalette(u8 xy1, u8 xy2, u8 p, u8 c, bool overlay = false);
  u32 applyGamma(u32 hex);
  void enableOverlayMode();
  void disableOverlayMode();
  u32 readXYLED(u8 xy);
  u32 readLED(u8 index);
  u32 toBrightness(u32 hex, float f);

  bool rotationCW(u8 r);
  void shift(Direction direction, u8 distance);

  bool changed = false;

private:
  bool overlay_mode = false;
  CRGB leds[NUM_TOTAL_LEDS];
  CRGB buffer[NUM_TOTAL_LEDS];
};

//extern LED LED;

#endif
