#include "Processor.h"

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

void Processor::UnknownOpcode()
{
    LOG("Unimplemented opcode: PC: 0x%02X, Opode: 0x%02X", PC, memory->ReadByte(PC));
}

void Processor::InvalidOpcode()
{
    LOG("Unimplemented opcode: Opcode: 0x%02X", memory->ReadByte(PC));
}
