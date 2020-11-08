#include "../../DeviceSelector.h"

void loadConfigMXPTV120()
{

  device_config = 120;

  device_name = "Matrix Prototype V1.2";


  //LED
  led_pin = PB7;
  powercord_pin = PA9;

  led_color_correction = 0xFFFFFF;

  //KeyPad
  keypad_type = 1;
  keypad_pins[0] = PB12;
  keypad_pins[1] = PB13;
  keypad_pins[2] = PC6;
  keypad_pins[3] = PB14;
  keypad_pins[4] = PB15;

  fn_pin = PA0;
  fn_press_state = HIGH;

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
  eeprom_palette_adds_0 = 0x803C000;
  eeprom_palette_adds_1 = 0x803C800;
  eeprom_sys_adds_0 = 0x803F000;
  eeprom_sys_adds_1 = 0x803F800;
  eeprom_pagesize = 0x800;
}
