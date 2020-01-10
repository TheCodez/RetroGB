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

#if defined(__ANDROID__)
#include <android/log.h>
#endif

constexpr int SCREEN_WIDTH = 160;
constexpr int SCREEN_HEIGHT = 144;

using uint8 = uint8_t;
using uint16 = uint16_t;
using int8 = int8_t;
using int16 = int16_t;

#define ENUM_FLAG_OPERATOR(T, X) \
	inline T operator X (T lhs, T rhs) { return (T) (static_cast<std::underlying_type_t<T>>(lhs) X static_cast<std::underlying_type_t<T>>(rhs)); } 

#define ENUM_FLAGS(T) \
	enum class T; \
	inline T operator ~ (T t) { return (T) (~static_cast<std::underlying_type_t<T>>(t)); } \
	ENUM_FLAG_OPERATOR(T, |) \
	ENUM_FLAG_OPERATOR(T, ^) \
	ENUM_FLAG_OPERATOR(T, &)

#define DEBUG

#ifdef DEBUG
template <typename ... Args>
void Log(const char* msg, const Args& ... args)
{
#if defined(__ANDROID__)
    __android_log_print(ANDROID_LOG_DEBUG, "RetroGB.Native", msg, args...);
#else
    printf(msg, args...);
#endif
}

template <typename ... Args>
void LogLine(const char* msg, const Args& ... args)
{
#if defined(__ANDROID__)
    __android_log_print(ANDROID_LOG_DEBUG, "RetroGB.Native", msg, args...);
#else
    printf(msg, args...);
    printf("\n");
#endif
}
#else
template <typename ... Args>
void Log(const char* format, const Args& ... args) {}
template <typename ... Args>
void LogLine(const char* format, const Args& ... args) {}
#endif
