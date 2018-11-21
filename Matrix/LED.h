#ifndef LED_H
#define LED_H

void LEDsetup();

void LEDonNote(int pallette, int note, int velocity);
void LEDoffNote(int note);

void LEDoff(int X, int Y );
void LEDon(int X, int Y );
void LEDonW(int X, int Y, int w);
void LEDonRGB(int X, int Y, int R, int G, int B);
void LEDonWRGB(int X, int Y, int W, int R, int G, int B);
void LEDonHEX(int X, int Y, uint32_t WRGB)；

void LEDsetPallette(int X, int Y, int w);

#endif
