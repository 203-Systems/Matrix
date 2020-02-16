#include "../Parameter/MatrixParameter.h"

const u8 SYSEX_HEADER[5] = {SYSEXID[0], SYSEXID[1], SYSEXID[2], PID >> 8, PID & 0x7F};
const u8 IDENTITY_REQUEST[2] = {0x06, 0x01};
