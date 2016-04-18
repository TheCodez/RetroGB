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

#include "Memory.h"
#include "BootRoms.h"
#include "Cartridge.h"
#include "Timer.h"
#include "Input.h"
#include "MemoryController.h"
#include "Mbc1.h"

Memory::Memory()
    : memoryController(nullptr)
{
    Reset(false);
}

Memory::~Memory()
{
    delete memoryController;
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

    if (memoryController != nullptr)
    {
        memoryController->Reset(color);
    }

    // Default values
    Write(0xFF05, 0x00); // TIMA
    Write(0xFF06, 0x00); // TMA
    Write(0xFF07, 0x00); // TAC
    Write(0xFF10, 0x80); // NR10
    Write(0xFF11, 0xBF); // NR11
    Write(0xFF12, 0xF3); // NR12
    Write(0xFF14, 0xBF); // NR14
    Write(0xFF16, 0x3F); // NR21
    Write(0xFF17, 0x00); // NR22
    Write(0xFF19, 0xBF); // NR24
    Write(0xFF1A, 0x7F); // NR30
    Write(0xFF1B, 0xFF); // NR31
    Write(0xFF1C, 0x9F); // NR32
    Write(0xFF1E, 0xBF); // NR33
    Write(0xFF20, 0xFF); // NR41
    Write(0xFF21, 0x00); // NR42
    Write(0xFF22, 0x00); // NR43
    Write(0xFF23, 0xBF); // NR30
    Write(0xFF24, 0x77); // NR50
    Write(0xFF25, 0xF3); // NR51
    Write(0xFF26, 0xF1); // NR52
    Write(0xFF40, 0x91); // LCDC
    Write(0xFF42, 0x00); // SCY
    Write(0xFF43, 0x00); // SCX
    Write(0xFF45, 0x00); // LYC
    Write(0xFF47, 0xFC); // BGP
    Write(0xFF48, 0xFF); // OBP0
    Write(0xFF49, 0xFF); // OBP1
    Write(0xFF4A, 0x00); // WY
    Write(0xFF4B, 0x00); // WX
    Write(0xFFFF, 0x00); // IE
}

bool Memory::LoadFromCartridge(Cartridge* cartridge)
{
    uint8* rom = cartridge->GetROM();
    for (int i = 0; i < 0x8000; i++)
    {
        data[i] = rom[i];
    }

    bool supported = true;

    // TODO set mbc here
    switch (cartridge->GetCartridgeType())
    {
        case CartridgeType::ROMONLY:
        case CartridgeType::ROM_RAM:
        case CartridgeType::ROM_RAM_BATTERY:
            memoryController = new MemoryController(this, cartridge);
            break;
        case CartridgeType::MBC1:
        case CartridgeType::MBC1_RAM:
        case CartridgeType::MBC1_RAM_BATTERY:
            memoryController = new Mbc1(this, cartridge);
            break;
        case CartridgeType::MBC2:
        case CartridgeType::MBC2_BATTERY:
            break;
        case CartridgeType::MBC3:
        case CartridgeType::MBC3_RAM:
        case CartridgeType::MBC3_RAM_BATTERY:    
        case CartridgeType::MBC3_TIMER_BATTERY:
        case CartridgeType::MBC3_TIMER_RAM_BATTERY:
            break;
        case CartridgeType::MBC5:
        case CartridgeType::MBC5_RAM:
        case CartridgeType::MBC5_RAM_BATTERY:
        case CartridgeType::MBC5_RUMBLE:
        case CartridgeType::MBC5_RUMBLE_RAM:
        case CartridgeType::MBC5_RUMBLE_RAM_BATTERY:
        default:
            supported = false;
            memoryController = new MemoryController(this, cartridge);
            LogLine("Unsupported Cartridge: %02X", cartridge->GetCartridgeType());
            break;
    }

    return supported;
}

void Memory::WriteByte(uint16 address, uint8 value)
{
    if (address <= 0x7FFF)
    {
        memoryController->Write(address, value);
    }
    else if (address >= 0xC000 && address <= 0xDFFF)
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
    if (address == 0xFF00)
    {
        input->Write(value);
    }
    else if (address == 0xFF01)
    {
        // SB
        Log("%c", (char)value);
        Write(address, value);
    }
    else if (address == 0xFF04)
    {
        // DIV
        timer->ResetDIV();
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
        int addr = value << 8;
        for (int i = 0; i < 160; i++)
        {
            Write(0xFE00 + i, Read(addr + i));
        }
    }
    else
    {
        Write(address, value);
    }
}

uint8 Memory::ReadByte(uint16 address)
{
    if (address <= 0x7FFF)
    {
        return memoryController->Read(address);
    }
    else if (address == 0xFF00)
    {
        return input->Read();
    }
    else
    {
        return Read(address);
    }
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
