#pragma once

#include <stdint.h>
#include <string>
#include <cstdarg>

#define SCREEN_WIDTH 160
#define SCREE_HEIGHT 144

typedef uint8_t uint8;
typedef uint16_t uint16;

#define FLAG_ZERO 0x80
#define FLAG_SUB 0x40
#define FLAG_HALFCARRY 0x20
#define FLAG_CARRY 0x10
#define FLAG_NONE 0x00

inline uint8 SetBit(uint8 value, uint8 bit)
{
    return value |= 0x01 << bit;
}

inline uint8 ClearBit(uint8 value, uint8 bit)
{
    return value &= ~(0x01 << bit);
}

inline bool IsBitSet(uint8 value, uint8 bit)
{
    return (value & (0x01 << bit)) != 0;
}

inline bool GetBitValue(uint8 value, uint8 bit)
{
    return (value & (0x01 << bit)) ? 1 : 0;
}

#ifdef _DEBUG
#define LOG(msg, ...) (LogLine(msg, ##__VA_ARGS__))
#else
#define LOG(msg, ...)  
#endif

inline void LogLine(const char* msg, ...)
{
    char buf[512];

    va_list args;
    va_start(args, msg);
    vsprintf_s(buf, msg, args);
    va_end(args);

    printf("%s\n", buf);
}