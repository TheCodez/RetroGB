#pragma once

#include "Definitions.h"

class Memory
{
public:
	Memory();
	~Memory();

	void Reset();

	void WriteByte(uint16 address, uint8 value);
	void WriteWord(uint16 address, uint16 value);

	uint8 ReadByte(uint16 address);
	uint16 ReadWord(uint16 address);
};

