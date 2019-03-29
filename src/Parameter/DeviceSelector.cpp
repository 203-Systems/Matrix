#include "DeviceSelector.h"

extern u8 device_config = 0;

extern u8 LED_PIN = 0;

extern u8 POWERCORD_PIN = 0;
//KeyPad
extern u8 SO_DATA = 0;
extern u8 SO_CLOCK = 0;
extern u8 SI_DATA = 0;
extern u8 SI_CLOCK = 0;
extern u8 SI_SCAN = 0;

extern u8 FN_PIN = 0;

//ANALOG(TouchBar)
extern u8 ANALOG0 = 0;
extern u8 ANALOG1 = 0;
extern u8 ANALOG2 = 0;
extern u8 ANALOG3 = 0;
extern u8 ANALOG4 = 0;
extern u8 ANALOG5 = 0;
extern u8 ANALOG6 = 0;
extern u8 ANALOG7 = 0;
extern u8 ANALOG8 = 0;
extern u8 ANALOG9 = 0;
extern u8 ANALOG10 = 0;
extern u8 ANALOG11 = 0;
//I2C
extern u8 I2C_SCL = 0;
extern u8 I2C_SDA = 0;
//SPI
extern u8 SPI_SCK = 0;
extern u8 SPI_MISO = 0;
extern u8 SPI_MOSI = 0;
extern u8 SPI_CS1 = 0;
extern u8 SPI_CS2 = 0;
//Serial1 (USB-C)
extern u8 TX1 = 0;
extern u8 RX1 = 0;
//Serial3 (Matrix Mod)
extern u8 TX3 = 0;
extern u8 RX3 = 0;
//Serial2/4/5 (m2p futureproof)
extern u8 TX2 = 0;
extern u8 RX2 = 0;
extern u8 TX4 = 0;
extern u8 RX4 = 0;
extern u8 TX5 = 0;
extern u8 RX5 = 0;

//SerialAvailabble
extern bool USBMIDI_AVAILABLE = 0;
extern bool USBCDC_AVAILABLE = 0;
extern bool SERIAL1_AVAILABLE = 0;
extern bool SERIAL2_AVAILABLE = 0;
extern bool SERIAL3_AVAILABLE = 0;
extern bool SERIAL4_AVAILABLE = 0;
extern bool SERIAL5_AVAILABLE = 0;

extern bool SUPPORT_WRGB = 0;

//EEPROM
extern bool EEPROM_ENABLE = 0;
extern u32 EEPROM_USER_ADDS_0 = 0;
extern u32 EEPROM_USER_ADDS_1 = 0;
extern u32 EEPROM_PALETTE_ADDS_0 = 0;
extern u32 EEPROM_PALETTE_ADDS_1 = 0;
extern u32 EEPROM_SYS_ADDS_0 = 0;
extern u32 EEPROM_SYS_ADDS_1 = 0;
extern u32 EEPROM_PAGESIZE = 0;

void loadDeviceConfig()
{
  #ifdef V120
  loadConfigV120();
  #endif

  #ifdef V150
  loadConfigV150();
  #endif

  switch(MATRIX_MODEL)
  {
    case MXPT: //MXTP

                          switch(MATRIX_VERSION)
                          {
                            // case 110:
                            // loadConfigV110();
                            // break;

                            case 120:
                            loadConfigV120();
                            break;

                            case 150:
                            loadConfigV150();
                            break;
                          }
    break;
  }
}
