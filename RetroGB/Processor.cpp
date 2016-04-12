#include "Processor.h"
#include "Processor.Timings.h"

Processor::Processor(Memory* mem)
    : memory(mem)
{
    Reset(false);
    InitOpcodes();
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
    HL = 0x014D;
    PC = 0x100; // TODO boot rom support
    SP = 0xFFFE;
    ime = true;
    halted = false;
    clockCycles = 0;
    condition = false;
}

int Processor::Run()
{
    clockCycles = 0;

    if (!halted)
    {
        HandleInterrupts();

        uint8 opcode = memory->ReadByte(PC++);

        //int c = IsFlagSet(FLAG_CARRY);
        //int n = IsFlagSet(FLAG_SUB);
        //int h = IsFlagSet(FLAG_HALFCARRY);
        //int z = IsFlagSet(FLAG_ZERO);
        //LOG_LINE("PC:%02X, OP:%02X, AF:%04X, BC:%04X, DE:%04X, HL:%04X, SP:%04X, Z:%d, N:%d, H:%d, C:%d", PC - 1, opcode, AF, BC, DE, HL, SP, z, n, h, c);
        
        if (opcode == 0xCB)
        {
            opcode = memory->ReadByte(PC++);
            opcodesCB[opcode]();

            clockCycles += opcodeCBCycles[opcode] * 4;
        }
        else
        {
            opcodes[opcode]();

            if (condition)
            {
                clockCycles += opcodeConditionalCycles[opcode] * 4;
                condition = false;
            }
            else
            {
                clockCycles += opcodeCycles[opcode] * 4;
            }
        }
    }
    else
    {
        clockCycles += 4;
    }

    return clockCycles;
}

void Processor::RequestInterrupt(Interrupts interrupt)
{
    memory->Write(0xFF0F, memory->Read(0xFF0F) | interrupt);
}

void Processor::HandleInterrupts()
{
    if (ime)
    {
        uint8 interruptEnable = memory->Read(0xFFFF);
        uint8 interruptFlag = memory->Read(0xFF0F);

        uint8 interrupt = interruptEnable & interruptFlag;

        if (interrupt & VBLANK)
        {
            halted = false;
            memory->Write(0xFF0F, interruptFlag & ~VBLANK);
            ime = false;
            StackPush(PC);
            PC = 0x0040;
        }
        else if (interrupt & LCDSTAT)
        {
            halted = false;
            memory->Write(0xFF0F, interruptFlag & ~LCDSTAT);
            ime = false;
            StackPush(PC);
            PC = 0x0048;
        }
        else if (interrupt & TIMER)
        {
            halted = false;
            memory->Write(0xFF0F, interruptFlag & ~TIMER);
            ime = false;
            StackPush(PC);
            PC = 0x0050;
        }
        else if (interrupt & SERIAL)
        {
            halted = false;
            memory->Write(0xFF0F, interruptFlag & ~SERIAL);
            ime = false;
            StackPush(PC);
            PC = 0x0058;
        }
        else if (interrupt & JOYPAD)
        {
            halted = false;
            memory->Write(0xFF0F, interruptFlag & ~JOYPAD);
            ime = false;
            StackPush(PC);
            PC = 0x0060;
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
    LOG_LINE("Unimplemented opcode: PC: 0x%02X, Opode: 0x%02X", PC, memory->ReadByte(PC));
}

void Processor::InvalidOpcode()
{
    LOG_LINE("Invalid opcode: Opcode: 0x%02X", memory->ReadByte(PC));
}
