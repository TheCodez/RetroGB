#pragma once

#include <stdint.h>

#define SCREEN_WIDTH 160
#define SCREE_HEIGHT 144

typedef uint8_t uint8;
typedef uint16_t uint16;

#define FLAG_ZERO 0x80
#define FLAG_SUB 0x40
#define FLAG_HALFCARRY 0x20
#define FLAG_CARRY 0x10
#define FLAG_NONE 0x00