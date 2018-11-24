//HardwareMapping
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
//Analog(TouchBar)
#define Analog0 PA0
#define Analog1 PA1
#define Analog2 PA2
#define Analog3 PA3
#define Analog4 PA4
#define Analog5 PA5
#define Analog6 PA6
#define Analog7 PA7
#define Analog8 PB0
#define Analog9 PB1
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
//SYSYTM
#define RESET_PIN PC13

//DeviceInfo
#define DEVICENAME "Matrix Prototype 2"
#define VID 0x0203
#define PID 0x0809

//LED
#define NUM_LEDS 64
#define NUM_BOTTOM_LEDS 36
#define NUM_TOTAL_LEDS 96   //64+32
#define NUM_POWERCORD_LEDS 60
#define FPS 60

//KeyPad
#define KEYPADX 8
#define KEYPADY 8
#define SCAN_RATE 120
