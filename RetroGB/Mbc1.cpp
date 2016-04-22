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

#include "Mbc1.h"
#include "Cartridge.h"

Mbc1::Mbc1(Memory* memory, Cartridge* cartridge)
    : MemoryController(memory, cartridge)
{
    ramBanks = new uint8[0x8000];
    Reset(false);
}

Mbc1::~Mbc1()
{
    delete[] ramBanks;
}

void Mbc1::Reset(bool color)
{
    romBank = 1;
    ramBank = 0;
    romOffset = 0x4000;
    ramOffset = 0;
    ramEnabled = false;
    bankMode = BankingMode::ROMBanking;

    for (int i = 0; i < 0x8000; i++)
        ramBanks[i] = 0xFF;
}

void Mbc1::Write(uint16 address, uint8 value)
{
    if (address < 0x2000)
    {
        ramEnabled = (value & 0x0F) == 0xA;
    }
    else if (address >= 0x2000 && address <= 0x3FFF)
    {
        romBank = value & 0x1F;
            
        if (romBank == 0x00 || romBank == 0x20 || romBank == 0x40 || romBank == 0x60)
            romBank++;

        romOffset = romBank * 0x4000;
    }
    else if (address >= 0x4000 && address <= 0x5FFF) 
    {
        if (bankMode == BankingMode::ROMBanking)
        {
            romBank = ((value & 0x03) << 5) | (romBank & 0x1F);
            romOffset = romBank * 0x4000;
        }
        else if (bankMode == BankingMode::RAMBanking)
        {
            ramBank = value & 0x03;
            ramOffset = ramBank * 0x4000;
        }
    }
    else if (address >= 0xA000 && address <= 0xBFFF)
    {
        if (ramEnabled)
        {
            ramBanks[(address - 0xA000) + ramOffset] = value;
        }
    }
    else if (0x6000 >= address && address <= 0x7FFF)
    {
        bankMode = (BankingMode)(value & 0x01);
    }
    else
    {
        MemoryController::Write(address, value);
    }
}

uint8 Mbc1::Read(uint16 address) const
{
    if (address >= 0x4000 && address <= 0x7FFF)
    {
        uint8* rom = cartridge->GetROM();
        return rom[(address - 0x4000) + romOffset];
    }
    else if (address >= 0xA000 && address <= 0xBFFF)
    {
        if (ramEnabled)
            return ramBanks[(address - 0xA000) + ramOffset];
        else
            return 0xFF;
    }
    else
    {
        return MemoryController::Read(address);
    }
}