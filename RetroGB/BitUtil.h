#pragma once

#include "Definitions.h"

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