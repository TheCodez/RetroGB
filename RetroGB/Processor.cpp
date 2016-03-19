#include "Processor.h"
#include "Memory.h"

Processor::Processor(Memory* mem)
	: memory(mem)
{
	InitOpcodes();
	Reset();
}


Processor::~Processor()
{
}

uint8 Processor::Run()
{
	uint8 opcode = memory->ReadByte(PC++);

	if (opcode == 0xCB)
	{
		opcode = memory->ReadByte(PC++);
		opcodesCB[opcode]();
	}
	else
	{
		opcodes[opcode]();
	}

    LOG("PC: 0x%d, Opcode: 0x%d, Instr: 0x%d", PC, opcode, memory->ReadByte(PC));

	return 0;
}

void Processor::Reset(bool color)
{
	if (color)
		AF = 0x11B0;
	else
		AF = 0x01B0;

	BC = 0x0013;
	DE = 0x00D8;
	HL = 0x014F;
	PC = 0x00; // TODO boot rom support
	SP = 0xFFFE;
    ime = true;
}

void Processor::SetFlag(uint8 flag)
{
	F = flag;
}

void Processor::EnableFlag(uint8 flag)
{
	F |= flag;
}

void Processor::DisableFlag(uint8 flag)
{
	F &= ~flag;
}

void Processor::ClearFlags(uint8 flag)
{
	SetFlag(FLAG_NONE);
}

bool Processor::IsFlagSet(uint8 flag)
{
	return (F & flag) != 0;
}

void Processor::InitOpcodes()
{
	// TODO generate tables with CpuGenerator

	auto nop = []() 
	{ 
		/* NOP */
	};

	for (int i = 0; i < 256; i++)
	{
        opcodes[i] = std::bind(&Processor::InitOpcodes, this);
        opcodesCB[i] = std::bind(&Processor::InitOpcodes, this);
	}
}

void Processor::InvalidOpcode()
{
    LOG("Not implemented opcode: 0x%d", memory->ReadByte(PC));
}
