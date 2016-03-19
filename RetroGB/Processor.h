#pragma once

#include "Definitions.h"
#include <functional>

class Memory;

class Processor
{
public:
	Processor(Memory* mem);
	~Processor();

	uint8 Run();
	void Reset(bool color = false);
	void InitOpcodes();

private:
	void SetFlag(uint8 flag);
	void EnableFlag(uint8 flag);
	void DisableFlag(uint8 flag);
	void ClearFlags(uint8 flag);
	bool IsFlagSet(uint8 flag);

    void InvalidOpcode();

private:
	Memory* memory;
	std::function<void()> opcodes[256];
	std::function<void()> opcodesCB[256];

    bool ime;
	uint16 PC;
	uint16 SP;

	union {
		struct {
			uint8 A;
			uint8 F;
		};
		uint16 AF;
	};

	union {
		struct {
			uint8 B;
			uint8 C;
		};
		uint16 BC;
	};

	union {
		struct {
			uint8 D;
			uint8 E;
		};
		uint16 DE;
	};

	union {
		struct {
			uint8 H;
			uint8 L;
		};
		uint16 HL;
	};
};

