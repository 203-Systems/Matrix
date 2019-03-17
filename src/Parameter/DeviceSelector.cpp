#include "DeviceSelector.h"

extern u8 LED_PIN = PC7;

extern u8 POWERCORD_PIN = PA9;
//KeyPad
extern u8 SO_DATA = PB12;
extern u8 SO_CLOCK = PB13;
extern u8 SI_DATA = PC6;
extern u8 SI_CLOCK = PB14;
extern u8 SI_SCAN = PB15;

extern u8 FN_PIN = PB7;

//ANALOG(TouchBar)
extern u8 ANALOG0 = PA3;
extern u8 ANALOG1 = PA4;
extern u8 ANALOG2 = PA5;
extern u8 ANALOG3 = PA6;
extern u8 ANALOG4 = PA7;
extern u8 ANALOG5 = PC4;
extern u8 ANALOG6 = PC5;
extern u8 ANALOG7 = PB0;
extern u8 ANALOG8 = PB1;
extern u8 ANALOG9 = PA0;
extern u8 ANALOG10 = PA1;
extern u8 ANALOG11 = PA2;
//I2C
extern u8 I2C_SCL = PB8;
extern u8 I2C_SDA = PB9;
//SPI
extern u8 SPI_SCK = PB3;
extern u8 SPI_MISO = PD1;
extern u8 SPI_MOSI = PB5;
extern u8 SPI_CS1 = PA15;
extern u8 SPI_CS2 = PB6;
//Serial1 (USB-C)
extern u8 TX1 = PA9;
extern u8 RX1 = PA10;
//Serial3 (Matrix Mod)
extern u8 TX3 = PB10;
extern u8 RX3 = PB11;
//Serial2/4/5 (m2p futureproof)
extern u8 TX2 = PA2;
extern u8 RX2 = PA3;
extern u8 TX4 = PB4;
extern u8 RX4 = PC10;
extern u8 TX5 = PC11;
extern u8 RX5 = PC12;

//SerialAvailabble
extern bool USBMIDI_AVAILABLE = true;
extern bool USBCDC_AVAILABLE = true;
extern bool SERIAL1_AVAILABLE = true;
extern bool SERIAL2_AVAILABLE = false;
extern bool SERIAL3_AVAILABLE = true;
extern bool SERIAL4_AVAILABLE = true;
extern bool SERIAL5_AVAILABLE = true;

extern bool SUPPORT_WRGB = false;

//EEPROM
extern bool EEPROM_ENABLE = true;
extern u32 EEPROM_USER_ADDS_0 = 0x803E000;
extern u32 EEPROM_USER_ADDS_1 = 0x803E800;
extern u32 EEPROM_PALETTE_ADDS_0 = 0x803D000;
extern u32 EEPROM_PALETTE_ADDS_1 = 0x803D800;
extern u32 EEPROM_SYS_ADDS_0 = 0x803F000;
extern u32 EEPROM_SYS_ADDS_1 = 0x803F800;
extern u32 EEPROM_PAGESIZE = 0x800;

void loadDeviceConfig()
{
  switch(MATRIX_MODEL)
  {
    case 0x4D585054: //MXTP

                          switch(MATRIX_VERSION)
                          {
                            case 110:
                            loadConfigV110();
                            break;

                            case 120:
                            loadConfigV120();
                            break;

                            case 150:
                            loadConfigV150();
                            break;

                            default:
                            loadConfigV150();
                            break;
                          }
    break;

    default:
      loadConfigV150();
    break;
  }
}
