#include "Memory.h"
#include "BootRoms.h"
#include <fstream>
#include <iostream>

Memory::Memory()
{
    Reset();
}

Memory::~Memory()
{
}

void Memory::Save()
{
}

void Memory::Reset()
{
    inBootRom = false;

    for (int i = 0; i < 0x8000; i++)
    {
        rom[i] = 0xFF;
    }
    for (int i = 0; i < 0x2000; i++)
    {
        eram[i] = 0;
    }
    for (int i = 0; i < 0x100; i++)
    {
        io[i] = 0;
    }
    for (int i = 0; i < 0x2000; i++)
    {
        vram[i] = 0;
    }
    for (int i = 0; i < 0x100; i++)
    {
        oam[i] = 0;
    }
    for (int i = 0; i < 0x2000; i++)
    {
        wram[i] = 0;
    }
    for (int i = 0; i < 0x80; i++)
    {
        hram[i] = 0;
    }

    for (int i = 0; i < 0x10000; i++)
    {
        data[i] = 0;
    }

    // Default values
    WriteByte(0xFF05, 0x00);
    WriteByte(0xFF06, 0x00);
    WriteByte(0xFF07, 0x00);
    WriteByte(0xFF10, 0x80);
    WriteByte(0xFF11, 0xBF);
    WriteByte(0xFF12, 0xF3);
    WriteByte(0xFF14, 0xBF);
    WriteByte(0xFF16, 0x3F);
    WriteByte(0xFF17, 0x00);
    WriteByte(0xFF19, 0xBF);
    WriteByte(0xFF1A, 0x7F);
    WriteByte(0xFF1B, 0xFF);
    WriteByte(0xFF1C, 0x9F);
    WriteByte(0xFF1E, 0xBF);
    WriteByte(0xFF20, 0xFF);
    WriteByte(0xFF21, 0x00);
    WriteByte(0xFF22, 0x00);
    WriteByte(0xFF23, 0xBF);
    WriteByte(0xFF24, 0x77);
    WriteByte(0xFF25, 0xF3);
    WriteByte(0xFF26, 0xF1);
    WriteByte(0xFF40, 0x91);
    WriteByte(0xFF42, 0x00);
    WriteByte(0xFF43, 0x00);
    WriteByte(0xFF45, 0x00);
    WriteByte(0xFF47, 0xFC);
    WriteByte(0xFF48, 0xFF);
    WriteByte(0xFF49, 0xFF);
    WriteByte(0xFF4A, 0x00);
    WriteByte(0xFF4B, 0x00);
    WriteByte(0xFFFF, 0x00);
}

void Memory::LoadRom(uint8* r)
{
    for (int i = 0; i < 0x8000; i++)
    {
        data[i] = r[i];
    }
}

/*
void Memory::WriteByte(uint16 address, uint8 value)
{
    if (address >= 0x8000 && address <= 0x9FFF)
    {
        vram[address - 0x8000] = value;
    }
    else if (address >= 0xA000 && address <= 0xBFFF)
    {
        eram[address - 0xA000] = value;
    }
    else if (address >= 0xC000 && address <= 0xCFFF)
    {
        wram[address - 0xC000] = value;
    }
    else if (address >= 0xD000 && address <= 0xDFFF)
    {
        wram[address - 0xD000] = value;
    }
    else if (address >= 0xE000 && address <= 0xFDFF)
    {
        wram[address - 0xE000] = value;
    }
    else if (address >= 0xFE00 && address <= 0xFE9F)
    {
        oam[address - 0xFE00] = value;
    }
    else if (address == 0xFF01)
    {
        LOG_LINE("%c", (char)value);
        io[address - 0xFF00] = value;
    }
    else if (address >= 0xFF00 && address <= 0xFF7F)
    {
        io[address - 0xFF00] = value;
    }
    else if (address >= 0xFF80 && address <= 0xFFFE)
    {
        hram[address - 0xFF80] = value;
    }
    else if (address == 0xFF46)
    {
        // DMA
        WriteByte(address, value);
        for (int i = 0; i < 0xA0; i++)
            WriteByte(0xFE00 + i, ReadByte((value << 8) + i));
    }
    else if (address == 0xFFFF)
    {
        interruptEnable = value;
    }
    else if (address == 0xFF0F)
    {
        interruptFlag = value;
    }
}

uint8 Memory::ReadByte(uint16 address)
{
    if (address <= 0x7FFF)
    {
        return rom[address];
    }
    else if (address >= 0x8000 && address <= 0x9FFF)
    {
        return vram[address - 0x8000];
    }
    else if (address >= 0xA000 && address <= 0xBFFF)
    {
        return eram[address - 0xA000];
    }
    else if (address >= 0xC000 && address <= 0xCFFF)
    {
        return wram[address - 0xC000];
    }
    else if (address >= 0xD000 && address <= 0xDFFF)
    {
        return wram[address - 0xD000];
    }
    else if (address >= 0xE000 && address <= 0xFDFF)
    {
        return wram[address - 0xE000];
    }
    else if (address >= 0xFE00 && address <= 0xFE9F)
    {
        return oam[address - 0xFE00];
    }
    else if (address >= 0xFF00 && address <= 0xFF7F)
    {
        return io[address - 0xFF00];
    }
    else if (address >= 0xFF80 && address <= 0xFFFE)
    {
        return hram[address - 0xFF80];
    }
    else if (address == 0xFFFF)
    {
        return interruptEnable;
    }
    else if (address == 0xFF0F)
    {
        return interruptFlag;
    }

    return 0;
}
*/

void Memory::WriteByte(uint16 address, uint8 value)
{
    if (address == 0xFF01)
    {
        // Catch data on the SB port
        data[address] = value;
        LOG("%c", (char)value);
    }
    else if (address == 0xFFFF)
    {
        interruptEnable = value;
    }
    else if (address == 0xFF0F)
    {
        interruptFlag = value;
    }
    else
    {
        data[address] = value;
    }
}

uint8 Memory::ReadByte(uint16 address)
{
    if (address == 0xFFFF)
    {
        return interruptEnable;
    }
    else if (address == 0xFF0F)
    {
        return interruptFlag;
    }
    else
    {
        return data[address];
    }
}


void Memory::WriteWord(uint16 address, uint16 value)
{
    WriteByte(address, value & 0xFF);
    WriteByte(address + 1, value >> 8);
}

uint16 Memory::ReadWord(uint16 address)
{
    return (uint16)(ReadByte(address) | (ReadByte(address + 1) << 8));
}

void Memory::WriteIO(uint16 address, uint8 value)
{
    io[address] = value;
}

uint8 Memory::ReadIO(uint16 address)
{
    return io[address];
}