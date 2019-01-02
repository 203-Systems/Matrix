#include <Arduino.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef volatile uint8_t vu8;
typedef volatile uint16_t vu16;
typedef volatile uint32_t vu32;
typedef volatile uint64_t vu64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef volatile int8_t vs8;
typedef volatile int16_t vs16;
typedef volatile int32_t vs32;
typedef volatile int64_t vs64;

// typedef enum {
//     VERYDIM = 16,
//     DIM = 32,
//     NORMAL = 64,
//     BRIGHT = 96,
//     VERYBRIGHT = 128,
//     MAX = 196,
// } BRIGHTNESS;

#define MATRIXPROTORE //Hardware model selector
#define DEBUG

//HardwareMapping
#ifdef MATRIXPROTOC8
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

#ifdef MATRIXPROTORE
//LED
#define LED_PIN PB7
#define POWERCORD_PIN PA9
//KeyPad
#define SO_DATA PB12
#define SO_CLOCK PB13
#define SI_DATA PC6
#define SI_CLOCK PB14
#define SI_SCAN PB15
#define FN_PIN PA0
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

#endif

//DeviceInfo
#define DEVICENAME "Matrix"
#define MAUNFACTURERNAME "203 Industries"
#define SERIALSTRING "unsigned"
#define VID  0x0203
#define VID2 0x0203 // for device ID USE
#define PID  0x1000
#define PID2 0x1000 // for device ID USE
#define FWVERSION "Alpha"

//LED
#define NUM_LEDS 64
#define NUM_BOTTOM_LEDS 36
#define NUM_TOTAL_LEDS 96   //64+32
#define NUM_POWERCORD_LEDS 60
#define FPS 100
#define LOWSTATEBRIGHTNESS 0.25

//KeyPad
#define KEYPADX 8 //Max 256 key support due to the m2p and libary data type limition
#define KEYPADY 8 // need tp change data type in keypad.h
#define MULTIPRESS 10 //Key Press Process At Once
#define MULTITAP_THRESHOLD 500
