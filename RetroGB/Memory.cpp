#include "Memory.h"
#include "BootRoms.h"

Memory::Memory()
{
}


Memory::~Memory()
{
}

void Memory::Reset()
{

}

void Memory::LoadRom(uint8* r)
{
    if (rom != r)
    {
        rom = r;
    }
}

void Memory::WriteByte(uint16 address, uint8 value)
{
    switch (address & 0xF000)
    {
    case 0x0000:
        break;
    case 0x1000:
    case 0x2000:
    case 0x3000:
        break;
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
        break;
    }
}

void Memory::WriteWord(uint16 address, uint16 value)
{
    WriteByte(address, value & 0xFF);
    WriteByte(address + 1, value >> 8);
}

uint8 Memory::ReadByte(uint16 address) const
{
    switch (address & 0xF000)
    {
    case 0x0000:
        if (address < 0x0100)
            return bootRomDMG[address];
        else
            return rom[address];
    case 0x1000:
    case 0x2000:
    case 0x3000:
        return rom[address];
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
        return rom[address];
    }

    return 0x00;
}

uint16 Memory::ReadWord(uint16 address) const
{
    return (uint16)(ReadByte(address) | (ReadByte(address + 1) << 8));
}