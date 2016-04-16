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

#pragma once

#include "Definitions.h"
#include "MemoryController.h"

class Cartridge;
class Memory;

class Mbc1 : public MemoryController
{
    enum class BankingMode : uint8
    {
        ROMBanking,
        RAMBanking
    };


public:
    Mbc1(Memory* memory, Cartridge* cartridge);
    ~Mbc1();

    virtual void Reset(bool color) override;
    virtual void Write(uint16 address, uint8 value) override;
    virtual uint8 Read(uint16 address) const override;

private:
    uint8 romBank;
    uint8 ramBank;
    uint8* ramBanks;

    uint16 romOffset;
    uint16 ramOffset;
    bool ramEnabled;
    BankingMode bankMode;
};

