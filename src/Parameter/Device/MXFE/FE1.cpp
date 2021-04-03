#include "../../DeviceSelector.h"

void loadConfigMXFE1()
{

  device_config = 1;
  device_name = "Matrix Founder Edition 1";

  //LED
  led_pin = PC7;
  powercord_pin = PA8;
  powercord_detection = PC9;

  led_color_correction = 0xFFFFFF;

  //KeyPad
  keypad_type = 2;
  u8 type2_keypad_pins[16] = {PB15, PB14, PB13, PB12, PC6, PC15, PC14, PC13, //X (SOURCE)
                 PB1, PB0, PA2, PA1, PC3, PA3, PC5, PC4}; // Y (RECIVE)
  // for(u8 i = 0; i < 16; i ++)
  // {
  //   keypad_pins[i] = type2_keypad_pins[i];
  // }
  memcpy(keypad_pins, type2_keypad_pins, 16);

  //Velocity sensitivty bit depth
  velocity_sensitivity = 1;

  fn_pin = PA0;
  fn_press_state = HIGH;

  //I2C
  i2c_scl = PB8;
  i2c_sda = PB9;
  //SPI
  spi_sck = PB3;
  spi_miso = PD1;
  spi_mosi= PB5;
  spi_cs1 = PA15;
  spi_cs2 = PB6;
  //Serial1 Matrix Mod
  tx1 = PA9;
  rx1 = PA10;
  //Serial2~5
  tx2 = PA2;
  rx2 = PA3;
  tx4 = PB4;
  rx4 = PC10;
  tx3 = PB10;
  rx3 = PB11;
  tx5 = PC11;
  rx5 = PC12;

  //SerialAvailable
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

  //Touch Bar
  touch_type = 1; //TTP229-BSF
  touch_length = 16;
  touch_pins[0] = PA7;
  touch_pins[1] = PA6;
}
