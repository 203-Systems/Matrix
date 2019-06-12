#include "DeviceSelector.h"

extern u8 device_config = 0;

extern u8 led_pin = 0;
extern u8 powercord_pin = 0;
extern u8 powercord_detection = 0;

extern u32 led_color_correction = 0xFFFFFFFF;

//KeyPad
extern u8 keypad_type = 1;
extern u8 keyPins[16] = {0};
extern bool velocity_sensitivity = false;

#define KEYPAD_SO_DATA keyPins[0]
#define KEYPAD_SO_CLOCK keyPins[1]
#define KEYPAD_SI_DATA keyPins[2]
#define KEYPAD_SI_CLOCK keyPins[3]
#define KEYPAD_SI_LATCH keyPins[4]

extern u8 fn_pin = 0;

//analog(TouchBar)
extern u8 analog0 = PA3;
extern u8 analog1 = PA4;
extern u8 analog2 = PA5;
extern u8 analog3 = PA6;
extern u8 analog4 = PA7;
extern u8 analog5 = PC4;
extern u8 analog6 = PC5;
extern u8 analog7 = PB0;
extern u8 analog8 = PB1;
extern u8 analog9 = PA0;
extern u8 analog10 = PA1;
extern u8 analog11 = PA2;
//I2C
extern u8 i2c_scl = 0;
extern u8 i2c_sda = 0;
//SPI
extern u8 spi_sck = 0;
extern u8 spi_miso = 0;
extern u8 spi_mosi= 0;
extern u8 spi_cs1 = 0;
extern u8 spi_cs2 = 0;
//Serial1 (USB-C)
extern u8 tx1 = 0;
extern u8 rx1 = 0;
//Serial3 (Matrix Mod)
extern u8 tx3 = 0;
extern u8 rx3 = 0;
//Serial2/4/5 (m2p futureproof)
extern u8 tx2 = 0;
extern u8 rx2 = 0;
extern u8 tx4 = 0;
extern u8 rx4 = 0;
extern u8 tx5 = 0;
extern u8 rx5 = 0;

//SerialAvailabble
extern bool usbmidi_available = 0;
extern bool usbcdc_available = 0;
extern bool serial1_available = 0;
extern bool serial2_available = 0;
extern bool serial3_available = 0;
extern bool serial4_available = 0;
extern bool serial5_available = 0;

extern bool support_wrgb = 0;

//EEPROM
extern bool eeprom_enable = 0;
extern u32 eeprom_user_adds_0 = 0;
extern u32 eeprom_user_adds_1 = 0;
extern u32 eeprom_palette_adds_0 = 0;
extern u32 eeprom_palette_adds_1 = 0;
extern u32 eeprom_sys_adds_0 = 0;
extern u32 eeprom_sys_adds_1 = 0;
extern u32 eeprom_pagesize = 0;

extern u8 touch_type = 0;

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
    case MXPT: //MXPT

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

                            case 200:
                            loadConfigV200();
                            break;
                          }
    break;
  }
}
