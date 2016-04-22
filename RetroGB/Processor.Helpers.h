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

void Processor::StackPush(uint16 reg)
{
    SP -= 2;
    memory->WriteWord(SP, reg);
}

void Processor::StackPop(uint16& reg)
{
    reg = memory->ReadWord(SP);
    SP += 2;
}

uint8 Processor::Inc(uint8 reg)
{
    uint8 result = reg + 1;
    
    IsFlagSet(Flags::CARRY) ? SetFlag(Flags::CARRY) : ClearFlags();

    if (result == 0)
        EnableFlag(Flags::ZERO);

    if ((result & 0x0F) == 0x00)
        EnableFlag(Flags::HALFCARRY);

    return result;
}

uint8 Processor::Dec(uint8 reg)
{
    uint8 result = reg - 1;
    
    IsFlagSet(Flags::CARRY) ? SetFlag(Flags::CARRY) : ClearFlags();
    EnableFlag(Flags::SUB);

    if (result == 0)
        EnableFlag(Flags::ZERO);

    if ((result & 0x0F) == 0x0F)
        EnableFlag(Flags::HALFCARRY);

    return result;
}

void Processor::Add(uint8 reg)
{
    int result = A + reg;
    int bits = A ^ reg ^ result;
    
    A += reg;

    ClearFlags();
    if (result == 0) 
        EnableFlag(Flags::ZERO);

    if ((bits & 0x100) != 0x00)
        EnableFlag(Flags::CARRY);

    if ((bits & 0x10) != 0x00)
        EnableFlag(Flags::HALFCARRY);
}

void Processor::Adc(uint8 reg)
{
    uint8 carry = IsFlagSet(Flags::CARRY) ? 1 : 0;
    int result = A + reg + carry;
    
    ClearFlags();
    if (result == 0)
        EnableFlag(Flags::ZERO);

    if (result > 0xFF)
        EnableFlag(Flags::CARRY);

    if (((A & 0x0F) + (reg & 0x0F) + carry) > 0x0F)
        EnableFlag(Flags::HALFCARRY);

    A += reg + carry;
}

void Processor::Sub(uint8 reg)
{
    int result = A - reg;
    int bits = A ^ reg ^ result;

    A -= reg;

    SetFlag(Flags::SUB);
    if (result == 0)
        EnableFlag(Flags::ZERO);

    if ((bits & 0x100) != 0x00)
    {
        EnableFlag(Flags::CARRY);
    }
    if ((bits & 0x10) != 0x00)
    {
        EnableFlag(Flags::HALFCARRY);
    }
}

void Processor::Sbc(uint8 reg)
{
    uint8 carry = IsFlagSet(Flags::CARRY) ? 1 : 0;
    int result = A - reg - carry;
    
    SetFlag(Flags::SUB);
    if (result == 0)
        EnableFlag(Flags::ZERO);

    if (result < 0)
        EnableFlag(Flags::CARRY);

    if (((A & 0x0F) - (reg & 0x0F) - carry) < 0)
        EnableFlag(Flags::HALFCARRY);
}

void Processor::AddHL(uint16 val)
{
    int result = HL + val;

    IsFlagSet(Flags::ZERO) ? SetFlag(Flags::ZERO) : ClearFlags();
    if (result & 0x10000)
        EnableFlag(Flags::CARRY);

    if ((HL ^ val ^ (result & 0xFFFF)) & 0x1000)
        EnableFlag(Flags::HALFCARRY);

    HL += val;
}

void Processor::AddSP(uint8 val)
{
    int result = SP + val;

    ClearFlags();

    if (((SP ^ val ^ (result & 0xFFFF)) & 0x100) == 0x100)
        EnableFlag(Flags::CARRY);

    if (((SP ^ val ^ (result & 0xFFFF)) & 0x10) == 0x10)
        EnableFlag(Flags::HALFCARRY);

    SP += val;
}

uint8 Processor::Rl(uint8 reg)
{
    uint8 carry = IsFlagSet(Flags::CARRY) ? 1 : 0;
    uint8 result = reg;

    if ((result & 0x80) != 0)
        SetFlag(Flags::CARRY);
    else
        ClearFlags();

    result <<= 1;
    result |= carry;

    if (result == 0)
        EnableFlag(Flags::ZERO);

    return result;
}

uint8 Processor::Rlc(uint8 reg)
{
    uint8 result = reg;
    
    if ((result & 0x80) != 0)
    {
        SetFlag(Flags::CARRY);
        result <<= 1;
        result |= 1;
    }
    else
    {
        ClearFlags();
        result <<= 1;
    }

    if (result == 0)
        EnableFlag(Flags::ZERO);

    return result;
}

uint8 Processor::Rr(uint8 reg)
{
    uint8 carry = IsFlagSet(Flags::CARRY) ? 1 : 0;
    uint8 result = reg;

    if ((result & 0x80) != 0)
        SetFlag(Flags::CARRY);
    else
        ClearFlags();

    result >>= 1;
    result |= carry;

    if (result == 0)
        EnableFlag(Flags::ZERO);

    return result;
}

uint8 Processor::Rrc(uint8 reg)
{
    uint8 result = reg;

    if ((result & 0x80) != 0)
    {
        SetFlag(Flags::CARRY);
        result >>= 1;
        result |= 1;
    }
    else
    {
        ClearFlags();
        result >>= 1;
    }

    if (result == 0)
        EnableFlag(Flags::ZERO);

    return result;
}

uint8 Processor::Sla(uint8 reg)
{
    uint8 result = reg;

    if ((result & 0x80) != 0)
        SetFlag(Flags::CARRY);
    else
        ClearFlags();

    result <<= 1;

    if (result == 0)
        EnableFlag(Flags::ZERO);

    return result;
}

uint8 Processor::Sra(uint8 reg)
{
    uint8 result = reg;

    if ((result & 0x01) != 0)
        SetFlag(Flags::CARRY);
    else
        ClearFlags();

    if ((result & 0x80) != 0)
    {
        result >>= 1;
        result |= 0x80;
    }
    else
    {
        result >>= 1;
    }

    if (result == 0)
        EnableFlag(Flags::ZERO);

    return result;
}

uint8 Processor::Srl(uint8 reg)
{
    uint8 result = reg;

    if ((result & 0x01) != 0)
        SetFlag(Flags::CARRY);
    else
        ClearFlags();

    result >>= 1;

    if (result == 0)
        EnableFlag(Flags::ZERO);

    return result;
}

void Processor::Bit(uint8 reg, uint8 bit)
{
    if (((reg >> bit) & 0x01) == 0) 
        EnableFlag(Flags::ZERO);
    else 
        DisableFlag(Flags::ZERO);

    DisableFlag(Flags::SUB);
    EnableFlag(Flags::HALFCARRY);
}

