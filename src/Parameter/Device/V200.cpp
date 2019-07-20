#include "../DeviceSelector.h"

void loadConfigV200()
{

  device_config = 200;

  //LED
  led_pin = PC7;
  powercord_pin = PA8;
  powercord_detection = PC9;

  led_color_correction = 0xC0FFD8;

  //KeyPad
  keypad_type = 2;
  u8 type2keyPins[16] = {PB15, PB14, PB13, PB12, PC6, PC15, PC14, PC13, //X (SOURCE)
                 PB1, PB0, PA2, PA1, PA0, PA3, PC5, PC4}; // Y (RECIVE)
  for(u8 i = 0; i < 16; i ++)
  {
    keyPins[i] = type2keyPins[i];
  }
  
  velocity_sensitivity = 12;

  fn_pin = PB7;

  //I2C
  i2c_scl = PB8;
  i2c_sda = PB9;
  //SPI
  spi_sck = PB3;
  spi_miso = PD1;
  spi_mosi= PB5;
  spi_cs1 = PA15;
  spi_cs2 = PB6;
  //Serial1
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

  touch_type = 1; //TTP229
}
