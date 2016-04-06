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

    /*
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
    */

    for (int i = 0; i < 0x10000; i++)
    {
        data[i] = 0xFF;
    }

    // Default values
    Write(0xFF05, 0x00);
    Write(0xFF06, 0x00);
    Write(0xFF07, 0x00);
    Write(0xFF10, 0x80);
    Write(0xFF11, 0xBF);
    Write(0xFF12, 0xF3);
    Write(0xFF14, 0xBF);
    Write(0xFF16, 0x3F);
    Write(0xFF17, 0x00);
    Write(0xFF19, 0xBF);
    Write(0xFF1A, 0x7F);
    Write(0xFF1B, 0xFF);
    Write(0xFF1C, 0x9F);
    Write(0xFF1E, 0xBF);
    Write(0xFF20, 0xFF);
    Write(0xFF21, 0x00);
    Write(0xFF22, 0x00);
    Write(0xFF23, 0xBF);
    Write(0xFF24, 0x77);
    Write(0xFF25, 0xF3);
    Write(0xFF26, 0xF1);
    Write(0xFF40, 0x91);
    Write(0xFF42, 0x00);
    Write(0xFF43, 0x00);
    Write(0xFF45, 0x00);
    Write(0xFF47, 0xFC);
    Write(0xFF48, 0xFF);
    Write(0xFF49, 0xFF);
    Write(0xFF4A, 0x00);
    Write(0xFF4B, 0x00);
    Write(0xFFFF, 0x00);
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
        LOG("%c", (char)value);
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
    if (address >= 0xC000 && address <= 0xDFFF)
    {
        // Echo  RAM
        Write(address + 0x2000, value);
        Write(address, value);
    }
    else if (address >= 0xE000 && address <= 0xFDFF)
    {
        // Echo  RAM
        Write(address - 0x2000, value);
        Write(address, value);
    }
    else if (address == 0xFF01)
    {
        // SB
        LOG("%c", (char)value);
        Write(address, value);
    }
    else if (address == 0xFF04)
    {
        // DIV
        Write(0xFF04, 0x00);
    }
    else if (address == 0xFF44)
    {
        // LY
        Write(0xFF44, 0x00);
    }
    else if (address == 0xFF45)
    {
        // LYC
        Write(0xFF45, value);
    }
    else if (address == 0xFF46)
    {
        // DMA
        for (int i = 0; i < 160; i++)
        {
            Write(0xFE00 + i, Read((value << 8) + i));
        }
    }
    else
    {
        Write(address, value);
    }
}

uint8 Memory::ReadByte(uint16 address)
{
    return Read(address);
}

void Memory::WriteWord(uint16 address, uint16 value)
{
    WriteByte(address, value & 0xFF);
    WriteByte(address + 1, value >> 8);
}

uint16 Memory::ReadWord(uint16 address)
{
    return (ReadByte(address) | (ReadByte(address + 1) << 8 ));
}

void Memory::Write(uint16 address, uint8 value)
{
    data[address] = value;
}

uint8 Memory::Read(uint16 address) const
{
    return data[address];
}