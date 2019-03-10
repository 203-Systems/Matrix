#define DEVICEREV V110

//LED
#define LED_PIN PB7
#define POWERCORD_PIN PA9

//KeyPad
#define SO_DATA PB12
#define SO_CLOCK PB13
#define SI_DATA PA8
#define SI_CLOCK PB14
#define SI_SCAN PB15
#define FN_PIN PC15

//ANALOG(TouchBar)
#define ANALOG0 PA0
#define ANALOG1 PA1
#define ANALOG2 PA2
#define ANALOG3 PA3
#define ANALOG4 PA4
#define ANALOG5 PA5
#define ANALOG6 PA6
#define ANALOG7 PA7
#define ANALOG8 PB0
#define ANALOG9 PB1
//I2C
#define I2C_SCL PB8
#define I2C_SDA PB9
//SPI
#define SPI_SCK PB3
#define SPI_MISO PB4
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
#define RESET_PIN PC13
//SerialAvailabble
#define USBMIDI_AVAILABLE
#define USBCDC_AVAILABLE
#define SERIAL1_AVAILABLE
// #define SERIAL2_AVAILABLE
#define SERIAL3_AVAILABLE
// #define SERIAL4_AVAILABLE
// #define SERIAL5_AVAILABLE

//#define SUPPORT_WRGB
#endif
