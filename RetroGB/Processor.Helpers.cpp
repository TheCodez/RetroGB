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

#include "BitUtil.h"
#include "Processor.h"

void Processor::SetFlags(Flag flag)
{
	F = flag;
}

void Processor::EnableFlag(Flag flag)
{
	F |= flag;
}

void Processor::DisableFlag(Flag flag)
{
	F &= ~flag;
}

void Processor::InvertFlag(Flag flag)
{
	F ^= flag;
}

void Processor::ClearFlags()
{
	SetFlags(Flag::None);
}

bool Processor::IsFlagSet(uint8 flag)
{
	return (F & flag) != 0;
}

void Processor::ToggleFlag(Flag flag, bool condition)
{
	if (condition)
	{
		EnableFlag(flag);
	}
	else
	{
		DisableFlag(flag);
	}
}

void Processor::KeepFlag(Flag flag)
{
	if (IsFlagSet(flag))
	{
		SetFlags(flag);
	}
	else
	{
		ClearFlags();
	}
}

void Processor::PushToStack(uint16 reg)
{
	SP -= 2;
	memory->WriteWord(SP, reg);
}

void Processor::PopFromStack(uint16& reg)
{
	reg = memory->ReadWord(SP);
	SP += 2;
}

uint8 Processor::Inc(uint8 reg)
{
	uint8 result = reg + 1;

	KeepFlag(Flag::Carry);
	ToggleFlag(Flag::Zero, result == 0);
	ToggleFlag(Flag::Half_Carry, (result & 0x0F) == 0);

	return result;
}

uint8 Processor::Dec(uint8 reg)
{
	uint8 result = reg - 1;

	KeepFlag(Flag::Carry);
	EnableFlag(Flag::Sub);

	ToggleFlag(Flag::Zero, result == 0);
	ToggleFlag(Flag::Half_Carry, (result & 0x0F) == 0x0F);

	return result;
}

void Processor::Add(uint8 reg)
{
	int result = A + reg;
	int bits = A ^ reg ^ result;

	A = static_cast<uint8>(result);

	ClearFlags();

	ToggleFlag(Flag::Zero, A == 0);
	ToggleFlag(Flag::Carry, (bits & 0x100) != 0);
	ToggleFlag(Flag::Half_Carry, (bits & 0x10) != 0);
}

void Processor::Adc(uint8 reg)
{
	int carry = IsFlagSet(Flag::Carry) ? 1 : 0;
	int result = A + reg + carry;

	ClearFlags();

	ToggleFlag(Flag::Zero, static_cast< uint8 >(result) == 0);
	ToggleFlag(Flag::Carry, result > 0xFF);
	ToggleFlag(Flag::Half_Carry, ((A & 0x0F) + (reg & 0x0F) + carry) > 0x0F);

	A = static_cast<uint8>(result);
}

void Processor::Sub(uint8 reg)
{
	int result = A - reg;
	int bits = A ^ reg ^ result;

	A = static_cast<uint8>(result);

	SetFlags(Flag::Sub);

	ToggleFlag(Flag::Zero, A == 0);
	ToggleFlag(Flag::Carry, (bits & 0x100) != 0);
	ToggleFlag(Flag::Half_Carry, (bits & 0x10) != 0);
}

void Processor::Sbc(uint8 reg)
{
	int carry = IsFlagSet(Flag::Carry) ? 1 : 0;
	int result = A - reg - carry;

	SetFlags(Flag::Sub);

	ToggleFlag(Flag::Zero, static_cast< uint8 >(result) == 0);
	ToggleFlag(Flag::Carry, result < 0);
	ToggleFlag(Flag::Half_Carry, ((A & 0x0F) - (reg & 0x0F) - carry) < 0);

	A = static_cast<uint8>(result);
}

void Processor::AddHL(uint16 val)
{
	int result = HL + val;

	KeepFlag(Flag::Zero);

	ToggleFlag(Flag::Carry, result & 0x10000);
	ToggleFlag(Flag::Half_Carry, (HL ^ val ^ (result & 0xFFFF)) & 0x1000);

	HL = static_cast<uint16>(result);
}

void Processor::AddSP(int8 val)
{
	int result = SP + val;

	ClearFlags();

	ToggleFlag(Flag::Carry, ((SP ^ val ^ (result & 0xFFFF)) & 0x100) == 0x100);
	ToggleFlag(Flag::Half_Carry, ((SP ^ val ^ (result & 0xFFFF)) & 0x10) == 0x10);

	SP = static_cast<uint16>(result);
}

uint8 Processor::Rl(uint8 reg, bool registerA)
{
	uint8 carry = IsFlagSet(Flag::Carry) ? 1 : 0;
	uint8 result = reg;

	ClearFlags();
	ToggleFlag(Flag::Carry, (result & 0x80) != 0);

	result <<= 1;
	result |= carry;

	if (!registerA)
	{
		ToggleFlag(Flag::Zero, result == 0);
	}

	return result;
}

uint8 Processor::Rlc(uint8 reg, bool registerA)
{
	uint8 result = reg;

	if ((result & 0x80) != 0)
	{
		SetFlags(Flag::Carry);
		result <<= 1;
		result |= 1;
	}
	else
	{
		ClearFlags();
		result <<= 1;
	}

	if (!registerA)
	{
		ToggleFlag(Flag::Zero, result == 0);
	}

	return result;
}

uint8 Processor::Rr(uint8 reg, bool registerA)
{
	uint8 carry = IsFlagSet(Flag::Carry) ? 0x80 : 0x00;
	uint8 result = reg;

	ClearFlags();
	ToggleFlag(Flag::Carry, (result & 0x01) != 0);

	result >>= 1;
	result |= carry;

	if (!registerA)
	{
		ToggleFlag(Flag::Zero, result == 0);
	}

	return result;
}

uint8 Processor::Rrc(uint8 reg, bool registerA)
{
	uint8 result = reg;

	if ((result & 0x01) != 0)
	{
		SetFlags(Flag::Carry);
		result >>= 1;
		result |= 0x80;
	}
	else
	{
		ClearFlags();
		result >>= 1;
	}

	if (!registerA)
	{
		ToggleFlag(Flag::Zero, result == 0);
	}

	return result;
}

uint8 Processor::Sla(uint8 reg)
{
	uint8 result = reg;

	ClearFlags();
	ToggleFlag(Flag::Carry, (result & 0x80) != 0);

	result <<= 1;

	ToggleFlag(Flag::Zero, result == 0);

	return result;
}

uint8 Processor::Sra(uint8 reg)
{
	uint8 result = reg;

	ClearFlags();
	ToggleFlag(Flag::Carry, (result & 0x01) != 0);

	if ((result & 0x80) != 0)
	{
		result >>= 1;
		result |= 0x80;
	}
	else
	{
		result >>= 1;
	}

	ToggleFlag(Flag::Zero, result == 0);

	return result;
}

uint8 Processor::Srl(uint8 reg)
{
	uint8 result = reg;

	ClearFlags();
	ToggleFlag(Flag::Carry, (result & 0x01) != 0);

	result >>= 1;

	ToggleFlag(Flag::Zero, result == 0);

	return result;
}

void Processor::Bit(uint8 reg, int bit)
{
	ToggleFlag(Flag::Zero, ((reg >> bit) & 0x01) == 0);

	DisableFlag(Flag::Sub);
	EnableFlag(Flag::Half_Carry);
}
