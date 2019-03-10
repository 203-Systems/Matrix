#include <Arduino.h>

#include "Device/DeviceSelector.h" //Device selector

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

#define DEBUG

//DeviceInfo
#define DEVICENAME "Matrix"
#define MAUNFACTURERNAME "203 Industries"
#define SERIALSTRING "unsigned"
#define VID  0x0203
#define VID2 0x0203 // for device ID USE
#define PID  0x1000
#define PID2 0x1000 // for device ID USE
#define FWVERSION "0.5"

//LED
#define NUM_LEDS 64
#define NUM_BOTTOM_LEDS 36
#define NUM_TOTAL_LEDS 100   //64+32
#define NUM_POWERCORD_LEDS 120
#define LOWSTATEBRIGHTNESS 0.25

#define XSIZE 8 //Max 256 key support due to the m2p and libary data type limition
#define YSIZE 8 // need tp change data type in keypad.h

//KeyPad
#define MULTIPRESS 10 //Key Press Process At Once
#define MULTITAP_THRESHOLD 500
