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

Processor::Processor(std::shared_ptr<Memory> memory)
    : memory(memory)
{
	InitOpcodes();
	Reset(false);
}

Processor::~Processor() = default;

void Processor::Reset(bool color)
{
	AF = color ? 0x11B0 : 0x01B0;
    BC = 0x0013;
    DE = 0x00D8;
    HL = 0x014D;
    PC = 0x0000; // TODO boot rom support
    SP = 0xFFFE;
    ime = true;
    halted = false;
    clockCycles = 0;
}

unsigned int Processor::Run()
{
    clockCycles = 0;

    if (!halted)
    {
        clockCycles += HandleInterrupts();

        uint8 opcode = memory->ReadByte(PC++);

		//int c = IsFlagSet(Flag::Carry);
        //int n = IsFlagSet(Flag::Sub);
        //int h = IsFlagSet(Flag::Half_Carry);
        //int z = IsFlagSet(Flag::Zero);
        //LogLine("PC:%02X, OP:%02X, AF:%04X, BC:%04X, DE:%04X, HL:%04X, SP:%04X, Z:%d, N:%d, H:%d, C:%d", PC - 1, opcode, AF, BC, DE, HL, SP, z, n, h, c);
        
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

void Processor::RequestInterrupt(Interrupt interrupt)
{
    memory->Write(0xFF0F, memory->Read(0xFF0F) | interrupt);
}

unsigned int Processor::HandleInterrupts()
{
	unsigned int cycles = 0;

    if (ime)
    {
        uint8 interruptEnable = memory->Read(0xFFFF);
        uint8 interruptFlag = memory->Read(0xFF0F);

        uint8 interrupt = interruptEnable & interruptFlag;

		halted = false;
		ime = false;
		PushToStack(PC);
		cycles = 20;

        if (interrupt & Interrupt::VBlank)
        {
			interruptFlag &= ~Interrupt::VBlank;
            PC = 0x0040;
        }
        else if (interrupt & Interrupt::LCD_Stat)
        {
			interruptFlag &= ~Interrupt::LCD_Stat;
            PC = 0x0048;
        }
        else if (interrupt & Interrupt::Time)
        {
			interruptFlag &= ~Interrupt::Time;
            PC = 0x0050;
        }
        else if (interrupt & Interrupt::Serial)
        {
			interruptFlag &= ~Interrupt::Serial;
            PC = 0x0058;
        }
        else if (interrupt & Interrupt::Joypad)
        {
			interruptFlag &= ~Interrupt::Joypad;
            PC = 0x0060;
        }

		memory->Write(0xFF0F, interruptFlag);
    }

	return cycles;
}

int Processor::UnknownOpcode()
{
    LogLine("Unimplemented opcode: PC: 0x%02X, Opode: 0x%02X", PC, memory->ReadByte(PC));

	return 4;
}

int Processor::InvalidOpcode()
{
    LogLine("Invalid opcode: Opcode: 0x%02X", memory->ReadByte(PC));

	return 4;
}
