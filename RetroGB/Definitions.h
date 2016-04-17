/*
* RetroGB

* Copyright (C) 2016  Michael Kösel

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*
*/

#pragma once

#include <stdint.h>
#include <string>
#include <functional>

constexpr int SCREEN_WIDTH = 160;
constexpr int SCREEN_HEIGHT = 144;

using uint8 = uint8_t;
using uint16 = uint16_t;
using int8 = int8_t;
using int16 = int16_t;

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
