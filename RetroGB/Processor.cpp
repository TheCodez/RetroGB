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

void Processor::Reset(bool color)
{
    if (color)
        AF = 0x11B0;
    else
        AF = 0x01B0;

    BC = 0x0013;
    DE = 0x00D8;
    HL = 0x014F;
    PC = 0x100; // TODO boot rom support
    SP = 0xFFFE;
    ime = true;
    halted = false;
    clockCycles = 0;
}

uint8 Processor::Run()
{
    clockCycles = 0;

    if (!halted)
    {
        HandleInterrupts();

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

        LOG("PC: 0x%02X, Opode: 0x%02X, AF: 0x%02X, DE: 0x%02X, BC: 0x%02X, HL: 0x%02X, SP: 0x%02X", PC, memory->ReadByte(PC), AF, DE, BC, HL, SP);
    }

    return clockCycles;
}

void Processor::RequestInterrupt(Interrupts interrupt)
{
    memory->WriteByte(0xFF0F, memory->ReadByte(0xFF0F) | interrupt);
}

void Processor::HandleInterrupts()
{
    if (ime)
    {
        uint8 interruptEnable = memory->ReadByte(0xFFFF);
        uint8 interruptFlag = memory->ReadByte(0xFF0F);

        uint8 interrupt = interruptEnable & interruptFlag;

        if (interrupt & VBlank)
        {
            memory->WriteByte(0xFF0F, interruptFlag & ~VBlank);
            ime = false;
            StackPush(PC);
            PC = 0x40;
        }
        else if (interrupt & LCDSTAT)
        {
            memory->WriteByte(0xFF0F, interruptFlag & ~LCDSTAT);
            ime = false;
            StackPush(PC);
            PC = 0x48;
        }
        else if (interrupt & Timer)
        {
            memory->WriteByte(0xFF0F, interruptFlag & ~Timer);
            ime = false;
            StackPush(PC);
            PC = 0x50;
        }
        else if (interrupt & Serial)
        {
            memory->WriteByte(0xFF0F, interruptFlag & ~Serial);
            ime = false;
            StackPush(PC);
            PC = 0x58;
        }
        else if (interrupt & Joypad)
        {
            memory->WriteByte(0xFF0F, interruptFlag & ~Joypad);
            ime = false;
            StackPush(PC);
            PC = 0x60;
        }
    }
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

void Processor::InvertFlag(uint8 flag)
{
    F ^= flag;
}

void Processor::ClearFlags()
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

void Processor::StackPush(uint16& reg)
{
    SP -= 2;
    memory->WriteWord(SP, reg);
}

void Processor::StackPop(uint16& reg)
{
    reg = memory->ReadWord(SP);
    SP += 2;
}
