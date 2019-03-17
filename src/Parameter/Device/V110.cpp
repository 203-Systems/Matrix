//V110 NO LONGER SUPPORTED
#include "../DeviceSelector.h"

void loadConfigV110()
{
  //LED
  LED_PIN = PB7;
  POWERCORD_PIN = PA9;

  //KeyPad
  SO_DATA = PB12;
  SO_CLOCK = PB13;
  SI_DATA = PA8;
  SI_CLOCK  = PB14;
  SI_SCAN = PB15;
  FN_PIN = PC15;

  //ANALOG(TouchBar)
  ANALOG0 = PA0;
  ANALOG1 = PA1;
  ANALOG2 = PA2;
  ANALOG3 = PA3;
  ANALOG4 = PA4;
  ANALOG5 = PA5;
  ANALOG6 = PA6;
  ANALOG7 = PA7;
  ANALOG8 = PB0;
  ANALOG9 = PB1;
  ANALOG10 = 0;
  ANALOG11 = 0;
  //I2C
  I2C_SCL = PB8;
  I2C_SDA = PB9;
  //SPI
  SPI_SCK = PB3;
  SPI_MISO = PB4;
  SPI_MOSI = PB5;
  SPI_CS1 = PA15;
  SPI_CS2 = PB6;

  //Serial1 (USB-C)
  TX1 = PA9;
  RX1 = PA10;
  //Serial3 (Matrix Mod)
  TX3 = PB10;
  RX3 = PB11;
  //Serial2/4/5 (m2p futureproof)
  TX2 = 0;
  RX2 = 0;
  TX4 = 0;
  RX4 = 0;
  TX5 = 0;
  RX5 = 0;

  //SerialAvailabble
  USBMIDI_AVAILABLE = true;
  USBCDC_AVAILABLE = true;
  SERIAL1_AVAILABLE = true;
  SERIAL2_AVAILABLE = false;
  SERIAL3_AVAILABLE = true;
  SERIAL4_AVAILABLE = false;
  SERIAL5_AVAILABLE = false;

  SUPPORT_WRGB = false;

  //EEPROM
  EEPROM_ENABLE = false;
  EEPROM_USER_ADDS_0 = 0;
  EEPROM_USER_ADDS_1 = 0;
  EEPROM_PALETTE_ADDS_0 = 0;
  EEPROM_PALETTE_ADDS_1 = 0;
  EEPROM_SYS_ADDS_0 = 0;
  EEPROM_SYS_ADDS_1 = 0;
  EEPROM_PAGESIZE = 0x400;
}
