#ifndef DEVICE_SELECTOR_H
#define DEVICE_SELECTOR_H

#include "../Parameter/MatrixParameter.h"

#define V120

extern u8 device_config;
extern String device_name;


extern u8 led_pin;
extern u8 powercord_pin;
extern u8 powercord_detection;

extern u32 led_color_correction;

//KeyPad
extern u8 keypad_type;
extern u8 keypad_pins[16];
//For Type 1, it will be SO_DATA, SO_CLOCK, SI_LATCH, SI_CLOCK, SI_DATA. Rest slots will remain null;
//(I know the Type 1 pin order is kind weird but type 1 support is just for legacy now, not gonna touch it)
//For Type 2, it will be x(source) 1~8, y(sink) 1~8. 

extern u8 velocity_sensitivity;

extern u8 fn_pin;
extern bool fn_press_state;

//analog(TouchBar)
extern u8 analog0;
extern u8 analog1;
extern u8 analog2;
extern u8 analog3;
extern u8 analog4;
extern u8 analog5;
extern u8 analog6;
extern u8 analog7;
extern u8 analog8;
extern u8 analog9;
extern u8 analog10;
extern u8 analog11;

//I2C
extern u8 i2c_scl;
extern u8 i2c_sda;
//SPI
extern u8 spi_sck;
extern u8 spi_miso;
extern u8 spi_mosi;
extern u8 spi_cs1;
extern u8 spi_cs2;
//Serial1 (USB-C)
extern u8 tx1;
extern u8 rx1;
//Serial3 (Matrix Mod)
extern u8 tx3;
extern u8 rx3;
//Serial2/4/5 (m2p futureproof)
extern u8 tx2;
extern u8 rx2;
extern u8 tx4;
extern u8 rx4;
extern u8 tx5;
extern u8 rx5;

//SerialAvailabble
extern bool usbmidi_available;
extern bool usbcdc_available;
extern bool serial1_available;
extern bool serial2_available;
extern bool serial3_available;
extern bool serial4_available;
extern bool serial5_available;

extern bool support_wrgb;

//EEPROM
extern bool eeprom_enable;
extern u32 eeprom_user_adds_0;
extern u32 eeprom_user_adds_1;
extern u32 eeprom_palette_adds_0;
extern u32 eeprom_palette_adds_1;
extern u32 eeprom_sys_adds_0;
extern u32 eeprom_sys_adds_1;
extern u32 eeprom_pagesize;

extern u8 touch_type;
extern u8 touch_length;
extern u8 touch_pins[2];
//for Type 1, it will be SO_CLOCK, SO_DATA

void loadDeviceConfig();
//MXPT
void loadConfigMXPTV120();
void loadConfigMXPTV150();
void loadConfigMXPTV210();
//MXFE
void loadConfigMXFE1();

#endif
