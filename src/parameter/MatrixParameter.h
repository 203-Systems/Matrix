typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

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
//SYSYTM
#define RESET_PIN PC13

//DeviceInfo
#define DEVICENAME "Matrix"
#define MAUNFACTURERNAME "203 Industries"
#define SERIALSTRING "unsigned"
#define VID  0x0203
#define VID2 0x0203 // for device ID USE
#define PID  0x1000
#define PID2 0x1000 // for device ID USE
#define SUPPORT_WRGB false
#define FWVERSION "0.1 Alpha"
//LED
#define NUM_LEDS 64
#define NUM_BOTTOM_LEDS 36
#define NUM_TOTAL_LEDS 96   //64+32
#define NUM_POWERCORD_LEDS 60
#define FPS 100

//KeyPad
#define KEYPADX 8
#define KEYPADY 8 //Cantchange due to KeyPad 16*16 as 8*32 instead
#define MULTIPRESS 10 //Key Press Process At Once
#define MULTITAP_THRESHOLD 200
