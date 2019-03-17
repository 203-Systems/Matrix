#ifndef DEVICE_SELECTOR_H
#define DEVICE_SELECTOR_H

#include "../Parameter/MatrixParameter.h"

extern u8 LED_PIN;

extern u8 POWERCORD_PIN;
//KeyPad
extern u8 SO_DATA;
extern u8 SO_CLOCK;
extern u8 SI_DATA;
extern u8 SI_CLOCK;
extern u8 SI_SCAN;

extern u8 FN_PIN;

//ANALOG(TouchBar)
extern u8 ANALOG0;
extern u8 ANALOG1;
extern u8 ANALOG2;
extern u8 ANALOG3;
extern u8 ANALOG4;
extern u8 ANALOG5;
extern u8 ANALOG6;
extern u8 ANALOG7;
extern u8 ANALOG8;
extern u8 ANALOG9;
extern u8 ANALOG10;
extern u8 ANALOG11;
//I2C
extern u8 I2C_SCL;
extern u8 I2C_SDA;
//SPI
extern u8 SPI_SCK;
extern u8 SPI_MISO;
extern u8 SPI_MOSI;
extern u8 SPI_CS1;
extern u8 SPI_CS2;
//Serial1 (USB-C)
extern u8 TX1;
extern u8 RX1;
//Serial3 (Matrix Mod)
extern u8 TX3;
extern u8 RX3;
//Serial2/4/5 (m2p futureproof)
extern u8 TX2;
extern u8 RX2;
extern u8 TX4;
extern u8 RX4;
extern u8 TX5;
extern u8 RX5;

//SerialAvailabble
extern bool USBMIDI_AVAILABLE;
extern bool USBCDC_AVAILABLE;
extern bool SERIAL1_AVAILABLE;
extern bool SERIAL2_AVAILABLE;
extern bool SERIAL3_AVAILABLE;
extern bool SERIAL4_AVAILABLE;
extern bool SERIAL5_AVAILABLE;

extern bool SUPPORT_WRGB;

//EEPROM
extern bool EEPROM_ENABLE;
extern u32 EEPROM_USER_ADDS_0;
extern u32 EEPROM_USER_ADDS_1;
extern u32 EEPROM_PALETTE_ADDS_0;
extern u32 EEPROM_PALETTE_ADDS_1;
extern u32 EEPROM_SYS_ADDS_0;
extern u32 EEPROM_SYS_ADDS_1;
extern u32 EEPROM_PAGESIZE;

void loadDeviceConfig();
void loadConfigV110();
void loadConfigV120();
void loadConfigV150();

#endif
