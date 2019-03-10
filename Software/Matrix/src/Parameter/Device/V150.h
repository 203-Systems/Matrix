#define LED_PIN PC7

#define POWERCORD_PIN PA9
//KeyPad
#define SO_DATA PB12
#define SO_CLOCK PB13
#define SI_DATA PC6
#define SI_CLOCK PB14
#define SI_SCAN PB15

#define FN_PIN PB7

//ANALOG(TouchBar)
#define ANALOG0 PA3
#define ANALOG1 PA4
#define ANALOG2 PA5
#define ANALOG3 PA6
#define ANALOG4 PA7
#define ANALOG5 PC4
#define ANALOG6 PC5
#define ANALOG7 PB0
#define ANALOG8 PB1
#define ANALOG9 PA0
#define ANALOG10 PA1
#define ANALOG11 PA2
//I2C
#define I2C_SCL PB8
#define I2C_SDA PB9
//SPI
#define SPI_SCK PB3
#define SPI_MISO PD1
#define SPI_MOSI PB5
#define SPI_CS1 PA15
#define SPI_CS2 PB6
//Serial1 (USB-C)
#define TX1 PA9
#define RX1 PA10
//Serial3 (Matrix Mod)
#define TX3 PB10
#define RX3 PB11
//Serial2/4/5 (m2p futureproof)
// #define TX2 PA2
// #define RX2 PA3
#define TX4 PB4
#define RX4 PC10
#define TX5 PC11
#define RX5 PC12

//SYSYTM
#define RESET_PIN PC15
//SerialAvailabble
#define USBMIDI_AVAILABLE
#define USBCDC_AVAILABLE
#define SERIAL1_AVAILABLE
// #define SERIAL2_AVAILABLE
#define SERIAL3_AVAILABLE
#define SERIAL4_AVAILABLE
#define SERIAL5_AVAILABLE

//#define SUPPORT_WRGB

//EEPROM
#define EEPROM_USER_ADDS_0 0x803E000
#define EEPROM_USER_ADDS_1 0x803E800
#define EEPROM_PALETTE_ADDS_0 0x803D000
#define EEPROM_PALETTE_ADDS_1 0x803D800
#define EEPROM_SYS_ADDS_0 0x803F000
#define EEPROM_SYS_ADDS_1 0x803F800
#define EEPROM_PAGESIZE 0x800
