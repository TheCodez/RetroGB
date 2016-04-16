#pragma once

#include <stdint.h>
#include <string>
#include <cstdarg>
#include <functional>

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

struct Color;
typedef std::function<void (Color*)> UpdateScreenFunc;

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
template <typename ... Args>
void Log(const char* msg, const Args& ... args)
{
    printf(msg, args...);
}

template <typename ... Args>
void LogLine(const char* msg, const Args& ... args)
{
    printf(msg, args...);
    printf("\n");
}
#else
template <typename ... Args>
void Log(const char* format, const Args& ... args) {}
template <typename ... Args>
void LogLine(const char* format, const Args& ... args) {}
#endif
