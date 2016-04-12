#include "Memory.h"
#include "BootRoms.h"
#include "Cartridge.h"
#include "Timer.h"
#include "Input.h"
#include <fstream>
#include <iostream>

Memory::Memory()
{
    Reset(false);
}

Memory::~Memory()
{
}

void Memory::Save()
{
}

void Memory::SetIOs(Cartridge* cartridge, Timer* timer, Input* input)
{
    this->cartridge = cartridge;
    this->timer = timer;
    this->input = input;
}

void Memory::Reset(bool color)
{
    colorGameboy = color;
    inBootRom = false;

    for (int i = 0; i < 0x10000; i++)
    {
        data[i] = 0x00;
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

void Memory::LoadFromCartridge(Cartridge* cartridge)
{
    uint8* rom = cartridge->GetROM();
    for (int i = 0; i < 0x8000; i++)
    {
        data[i] = rom[i];
    }

    // TODO set mbc here
}

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
    return (ReadByte(address) | (ReadByte(address + 1) << 8));
}

void Memory::Write(uint16 address, uint8 value)
{
    data[address] = value;
}

uint8 Memory::Read(uint16 address) const
{
    return data[address];
}