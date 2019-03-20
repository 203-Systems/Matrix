#ifndef MATRIX_PARAMETER
#define MATRIX_PARAMETER

#include <Arduino.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef const uint8_t uc8;
typedef const uint16_t uc16;
typedef const uint32_t uc32;
typedef const uint64_t uc64;

typedef volatile uint8_t vu8;
typedef volatile uint16_t vu16;
typedef volatile uint32_t vu32;
typedef volatile uint64_t vu64;

typedef volatile const uint8_t vuc8;
typedef volatile const uint16_t vuc16;
typedef volatile const uint32_t vuc32;
typedef volatile const uint64_t vuc64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef const int8_t sc8;
typedef const int16_t sc16;
typedef const int32_t sc32;
typedef const int64_t sc64;

typedef volatile int8_t vs8;
typedef volatile int16_t vs16;
typedef volatile int32_t vs32;
typedef volatile int64_t vs64;

typedef volatile const int8_t vsc8;
typedef volatile const int16_t vsc16;
typedef volatile const int32_t vsc32;
typedef volatile const int64_t vsc64;

// typedef enum {
//     VERYDIM = 16,
//     DIM = 32,
//     NORMAL = 64,
//     BRIGHT = 96,
//     VERYBRIGHT = 128,
//     MAX = 196,
// } BRIGHTNESS;

#define DEBUG

//DeviceInfo
#define DEVICENAME "Matrix"
#define MAUNFACTURERNAME "203 Industries"
#define SERIALSTRING "Prototype"
#define VID  0x0203
#define VID2 0x0203 // for device ID USE
#define PID  0x1000
#define PID2 0x1000 // for device ID USE
#define FWVERSION "1.0 __DATE__"

#define BOOTLOADER_VERSION   *(u32 *) (0x08001E00)
#define MATRIX_MODEL         *(u32 *) (0x08001E04)
#define MATRIX_VERSION       *(u32 *) (0x08001E08)
#define MATRIX_BATCH         *(u32 *) (0x08001E0C)

#define DEVICE_SERIAL_1   *(u32 *) (0x1FFFF7E8)
#define DEVICE_SERIAL_2   *(u32 *) (0x1FFFF7E8+0x04)
#define DEVICE_SERIAL_3   *(u32 *) (0x1FFFF7E8+0x08)

#define MXPT 0x4D585054


//LED
#define NUM_LEDS 64
#define NUM_BOTTOM_LEDS 36
#define NUM_TOTAL_LEDS 100   //64+32
#define NUM_POWERCORD_LEDS 120
#define LOWSTATEBRIGHTNESS 0.4

#define XSIZE 8 //Max 256 key support due to the m2p and libary data type limition
#define YSIZE 8 // need tp change data type in keypad.h

//KeyPad
#define MULTIPRESS 10 //Key Press Process At Once
#define MULTITAP_THRESHOLD 500

#endif
