#include "../DeviceSelector.h"

void loadConfigV150()
{

  device_config = 150;

  //LED
  led_pin = PC7;
  powercord_pin = PA9;

  led_color_correction = 0xC0FFD8;

  //KeyPad
  so_data = PB12;
  so_clock = PB13;
  si_data = PC6;
  si_clock = PB14;
  si_scan = PB15;

  fn_pin = PB7;

  //analog(TouchBar)
  analog0 = PA3;
  analog1 = PA4;
  analog2 = PA5;
  analog3 = PA6;
  analog4 = PA7;
  analog5 = PC4;
  analog6 = PC5;
  analog7 = PB0;
  analog8 = PB1;
  analog9 = PA0;
  analog10 = PA1;
  analog11 = PA2;
  //I2C
  i2c_scl = PB8;
  i2c_sda = PB9;
  //SPI
  spi_sck = PB3;
  spi_miso = PD1;
  spi_mosi= PB5;
  spi_cs1 = PA15;
  spi_cs2 = PB6;
  //Serial1 (USB-C)
  tx1 = PA9;
  rx1 = PA10;
  //Serial3 (Matrix Mod)
  tx3 = PB10;
  rx3 = PB11;
  //Serial2/4/5 (m2p futureproof)
  tx2 = PA2;
  rx2 = PA3;
  tx4 = PB4;
  rx4 = PC10;
  tx5 = PC11;
  rx5 = PC12;

  //SerialAvailabble
  usbmidi_available = true;
  usbcdc_available = true;
  serial1_available = true;
  serial2_available = false;
  serial3_available = true;
  serial4_available = true;
  serial5_available = true;

  support_wrgb = false;

  //EEPROM
  eeprom_enable = true;
  eeprom_user_adds_0 = 0x803E000;
  eeprom_user_adds_1 = 0x803E800;
  eeprom_palette_adds_0 = 0x803D000;
  eeprom_palette_adds_1 = 0x803D800;
  eeprom_sys_adds_0 = 0x803F000;
  eeprom_sys_adds_1 = 0x803F800;
  eeprom_pagesize = 0x800;
}
