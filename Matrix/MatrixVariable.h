#ifndef MATRIX_VARIABLE
#define MATRIX_VARIABLE

#include <Arduino.h>
#include <stdint.h>

//HardwareMapping
//LED
extern uint8 LED_PIN; //23;           //PB7
extern uint8 POWERCORD_PIN; //9;      //PA9
//KeyPad
extern uint8 SO_DATA; //30;           //PB12
extern uint8 SO_CLOCK; //31;          //PB13
extern uint8 SI_DATA; //8;            //PA8
extern uint8 SI_CLOCK; //29;          //PB14
extern uint8 SI_SCAN; //28;           //PB15
extern uint8 FN_PIN; //34;            //PC15
//Analog(TouchBar)
extern uint8 Analog0; //0;            //PA0
extern uint8 Analog1; //1;            //PA1
extern uint8 Analog2; //2;            //PA2
extern uint8 Analog3; //3;            //PA3
extern uint8 Analog4; //4;            //PA4
extern uint8 Analog5; //5;            //PA5
extern uint8 Analog6; //6;            //PA6
extern uint8 Analog7; //7;            //PA7
extern uint8 Analog8; //16;           //PB0
extern uint8 Analog9; //17;           //PB1
//I2C
extern uint8 I2C_SCL; //24;           //PB8
extern uint8 I2C_SDA; //25;           //PB9
//SPI
extern uint8 SPI_SCK; //19;           //PB3
extern uint8 SPI_MISO; //20;          //PB4
extern uint8 SPI_MOSI; //21;          //PB5
extern uint8 SPI_CS1; //15;           //PA15
extern uint8 SPI_CS2; //22;           //PB6
//Serial1 (USB-C)
extern uint8 TX1; //9;                //PA9
extern uint8 RX1; //10;               //PA10
//Serial3 (Matrix Mod)
extern uint8 TX3; //26;               //PB10
extern uint8 RX3; //27;               //PB11
//SYSYTM
extern uint8 RESET_PIN; //32;         //PC13

//DeviceInfo
//extern String DeviceName; //"Matrix Prototype";
extern uint8 DeviceID; //0;
extern uint16 VID; //0x0203;
extern uint16 PID; //0x0803;
//LED Setting
extern const uint8 NUM_LEDS; //64;
extern uint8 NUM_BOTTOM_LEDS; //32;
extern uint8 NUM_POWERCORD_LEDS; //60;
extern uint8 FPS; //60;
extern uint8 Brightness; //64;
extern uint64 colour[3][128]; //    //WRGB Colour Pallette

//KeyPad
extern uint8 ScanRate; //120;
extern uint8 KeyMap [8][8];

//TouchBar
extern uint8 TouchSensitive; //0;

//Sysex
extern bool MIDIEnable; //true;
extern bool CDCEnable; //true;
extern bool POWERCORD; //false;
extern bool RETURN; //false;

#endif
