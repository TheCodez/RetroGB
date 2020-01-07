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

#include "Processor.h"
#include "Processor.Helpers.h"
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
    PC = 0x0000; // TODO boot rom support
    SP = 0xFFFE;
    ime = true;
    halted = false;
    clockCycles = 0;
}

int Processor::Run()
{
    clockCycles = 0;

    if (!halted)
    {
        HandleInterrupts();

        uint8 opcode = memory->ReadByte(PC++);

        //int c = IsFlagSet(Flags::CARRY);
        //int n = IsFlagSet(Flags::SUB);
        //int h = IsFlagSet(Flags::HALFCARRY);
        //int z = IsFlagSet(Flags::ZERO);
        //LOG_LINE("PC:%02X, OP:%02X, AF:%04X, BC:%04X, DE:%04X, HL:%04X, SP:%04X, Z:%d, N:%d, H:%d, C:%d", PC - 1, opcode, AF, BC, DE, HL, SP, z, n, h, c);
        
        if (opcode == 0xCB)
        {
            opcode = memory->ReadByte(PC++);
            clockCycles += opcodesCB[opcode]();
        }
        else
        {
			clockCycles += opcodes[opcode]();
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
            clockCycles = 20;
        }
        else if (interrupt & LCDSTAT)
        {
            halted = false;
            memory->Write(0xFF0F, interruptFlag & ~LCDSTAT);
            ime = false;
            StackPush(PC);
            PC = 0x0048;
            clockCycles = 20;
        }
        else if (interrupt & TIMER)
        {
            halted = false;
            memory->Write(0xFF0F, interruptFlag & ~TIMER);
            ime = false;
            StackPush(PC);
            PC = 0x0050;
            clockCycles = 20;
        }
        else if (interrupt & SERIAL)
        {
            halted = false;
            memory->Write(0xFF0F, interruptFlag & ~SERIAL);
            ime = false;
            StackPush(PC);
            PC = 0x0058;
            clockCycles = 20;
        }
        else if (interrupt & JOYPAD)
        {
            halted = false;
            memory->Write(0xFF0F, interruptFlag & ~JOYPAD);
            ime = false;
            StackPush(PC);
            PC = 0x0060;
            clockCycles = 20;
        }
    }
}

void Processor::SetFlag(Flags flag)
{
    F = flag;
}

void Processor::EnableFlag(Flags flag)
{
    F |= flag;
}

void Processor::DisableFlag(Flags flag)
{
    F &= ~flag;
}

void Processor::InvertFlag(Flags flag)
{
    F ^= flag;
}

void Processor::ClearFlags()
{
    SetFlag(NONE);
}

bool Processor::IsFlagSet(uint8 flag)
{
    return (F & flag) != 0;
}

int Processor::UnknownOpcode()
{
    LogLine("Unimplemented opcode: PC: 0x%02X, Opode: 0x%02X", PC, memory->ReadByte(PC));

	return 0;
}

int Processor::InvalidOpcode()
{
    LogLine("Invalid opcode: Opcode: 0x%02X", memory->ReadByte(PC));

	return 0;
}
