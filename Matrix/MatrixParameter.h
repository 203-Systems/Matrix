//HardwareMapping
//LED
#define LED_PIN PB7
#define POWERCORD_PIN PA9
//KeyPad
#define SO_DATA PB12
#define SO_CLOCK PB13
#define SI_DATA 8            //PA8
#define SI_CLOCK 29          //PB14
#define SI_SCAN 28           //PB15
#define FN_PIN 34            //PC15
//Analog(TouchBar)
#define Analog0 0            //PA0
#define Analog1 1            //PA1
#define Analog2 2            //PA2
#define Analog3 3            //PA3
#define Analog4 4            //PA4
#define Analog5 5            //PA5
#define Analog6 6            //PA6
#define Analog7 7            //PA7
#define Analog8 16           //PB0
#define Analog9 17           //PB1
//I2C
#define I2C_SCL 24           //PB8
#define I2C_SDA 25           //PB9
//SPI
#define SPI_SCK 19           //PB3
#define SPI_MISO 20          //PB4
#define SPI_MOSI 21          //PB5
#define SPI_CS1 15           //PA15
#define SPI_CS2 22           //PB6
//Serial1 (USB-C)
#define TX1 9                //PA9
#define RX1 10               //PA10
//Serial3 (Matrix Mod)
#define TX3 26               //PB10
#define RX3 27               //PB11
//SYSYTM
#define RESET_PIN 32         //PC13

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
