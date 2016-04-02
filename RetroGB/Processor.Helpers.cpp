#include "Processor.h"

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

uint8 Processor::Inc(uint8 reg)
{
    uint8 result = reg + 1;
    IsFlagSet(FLAG_CARRY) ? SetFlag(FLAG_CARRY) : ClearFlags();

    if (result == 0)
        EnableFlag(FLAG_ZERO);

    if ((result & 0x0F) == 0x00)
        EnableFlag(FLAG_HALFCARRY);

    return result;
}

uint8 Processor::Dec(uint8 reg)
{
    uint8 result = reg - 1;
    IsFlagSet(FLAG_CARRY) ? SetFlag(FLAG_CARRY) : ClearFlags();

    if (reg == 0)
        EnableFlag(FLAG_ZERO);

    if ((reg & 0x0F) == 0x0F)
        EnableFlag(FLAG_HALFCARRY);

    return result;
}

void Processor::Add(uint8 reg)
{
    int result = A + reg;
    int bits = A ^ reg ^ result;
    
    A += reg;

    ClearFlags();
    if (A == 0) 
        EnableFlag(FLAG_ZERO);

    if ((bits & 0x100) != 0x00)
        EnableFlag(FLAG_CARRY);

    if ((bits & 0x10) != 0x00)
        EnableFlag(FLAG_HALFCARRY);
}

void Processor::Adc(uint8 reg)
{
    uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
    int result = A + reg + carry;
    
    ClearFlags();
    if (A == 0) EnableFlag(FLAG_ZERO);

    if (result > 0xFF)
        EnableFlag(FLAG_CARRY);

    if (((A & 0x0F) + (reg & 0x0F) + carry) > 0x0F)
        EnableFlag(FLAG_HALFCARRY);

    A += reg + carry;
}

void Processor::Sub(uint8 reg)
{
    int result = A - reg;
    int bits = A ^ reg ^ result;

    SetFlag(FLAG_SUB);
    if (A == 0) EnableFlag(FLAG_ZERO);

    if ((bits & 0x100) != 0x00)
    {
        EnableFlag(FLAG_CARRY);
    }
    if ((bits & 0x10) != 0x00)
    {
        EnableFlag(FLAG_HALFCARRY);
    }

    A -= reg;
}

void Processor::Sbc(uint8 reg)
{
    uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
    int result = A - reg - carry;
    
    SetFlag(FLAG_SUB);
    if (A == 0) 
        EnableFlag(FLAG_ZERO);

    if (result > 0xFF)
        EnableFlag(FLAG_CARRY);

    if (((A & 0x0F) - (reg & 0x0F) - carry) < 0)
        EnableFlag(FLAG_HALFCARRY);

    A -= reg - carry;
}

void Processor::AddHL(uint16 val)
{
    int result = HL + val;

    IsFlagSet(FLAG_ZERO) ? SetFlag(FLAG_ZERO) : ClearFlags();
    if (result & 0x10000)
        EnableFlag(FLAG_CARRY);

    if ((HL ^ val ^ (result & 0xFFFF)) & 0x1000)
        EnableFlag(FLAG_HALFCARRY);

    HL += val;
}

void Processor::AddSP(uint8 val)
{
    int result = SP + val;

    ClearFlags();

    if (((SP ^ val ^ (result & 0xFFFF)) & 0x100) == 0x100)
        EnableFlag(FLAG_CARRY);

    if (((SP ^ val ^ (result & 0xFFFF)) & 0x10) == 0x10)
        EnableFlag(FLAG_HALFCARRY);

    SP += val;
}

uint8 Processor::Rl(uint8 reg)
{
    uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
    uint8 result = reg;

    if ((result & 0x80) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlags();

    result <<= 1;
    result |= carry;

    if (result == 0)
        EnableFlag(FLAG_ZERO);

    return result;
}

uint8 Processor::Rlc(uint8 reg)
{
    uint8 result = reg;
    
    if ((result & 0x80) != 0)
    {
        SetFlag(FLAG_CARRY);
        result <<= 1;
        result |= 1;
    }
    else
    {
        ClearFlags();
        result <<= 1;
    }

    if (result == 0)
        EnableFlag(FLAG_ZERO);

    return result;
}

uint8 Processor::Rr(uint8 reg)
{
    uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
    uint8 result = reg;

    if ((result & 0x80) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlags();

    result >>= 1;
    result |= carry;

    if (result == 0)
        EnableFlag(FLAG_ZERO);

    return result;
}

uint8 Processor::Rrc(uint8 reg)
{
    uint8 result = reg;

    if ((result & 0x80) != 0)
    {
        SetFlag(FLAG_CARRY);
        result >>= 1;
        result |= 1;
    }
    else
    {
        ClearFlags();
        result >>= 1;
    }

    if (result == 0)
        EnableFlag(FLAG_ZERO);

    return result;
}

uint8 Processor::Sla(uint8 reg)
{
    uint8 result = reg;

    if ((result & 0x80) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlags();

    result <<= 1;

    if (result == 0)
        EnableFlag(FLAG_ZERO);

    return result;
}

uint8 Processor::Sra(uint8 reg)
{
    uint8 result = reg;

    if ((result & 0x01) != 0)
        SetFlag(FLAG_CARRY);
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
        EnableFlag(FLAG_ZERO);

    return result;
}

uint8 Processor::Srl(uint8 reg)
{
    uint8 result = reg;

    if ((result & 0x01) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlags();

    result >>= 1;

    if (result == 0)
        EnableFlag(FLAG_ZERO);

    return result;
}
