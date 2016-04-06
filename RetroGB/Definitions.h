#pragma once

#include <stdint.h>
#include <string>
#include <cstdarg>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef int8_t int8;
typedef int16_t int16;

#define FLAG_ZERO 0x80
#define FLAG_SUB 0x40
#define FLAG_HALFCARRY 0x20
#define FLAG_CARRY 0x10
#define FLAG_NONE 0x00

inline void SetBit(uint8& value, uint8 bit)
{
    value |= 1 << bit;
}

inline void ResetBit(uint8& value, uint8 bit)
{
    value &= ~(1 << bit);
}

inline bool IsBitSet(uint8 value, uint8 bit)
{
    return (value & (1 << bit)) != 0;
}

inline uint8 GetBitValue(uint8 value, uint8 bit)
{
    return (value & (1 << bit)) ? 1 : 0;
}

#define DEBUG

#ifdef DEBUG
#define LOG_LINE(msg, ...) (LogLine(true, msg, ##__VA_ARGS__))
#define LOG(msg, ...) (LogLine(false, msg, ##__VA_ARGS__))
#else
#define LOG_LINE(msg, ...)  
#define LOG(msg, ...)  
#endif

inline void LogLine(bool newLine, const char* msg, ...)
{
    char buf[512];

    va_list args;
    va_start(args, msg);
    vsprintf_s(buf, msg, args);
    va_end(args);

    if (newLine)
        printf("%s\n", buf);
    else
        printf("%s", buf);
}