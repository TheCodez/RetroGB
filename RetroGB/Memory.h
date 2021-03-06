/*
* RetroGB

* Copyright (C) 2016  Michael K�sel

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

#include <memory>
#include <array>

class Cartridge;
class Timer;
class Input;
class MemoryController;

class Memory
{
public:
    Memory();
    ~Memory();

    void Reset(bool color);

    void RegisterInputs(std::shared_ptr<Cartridge> cartridge, std::shared_ptr<Timer> timer, std::shared_ptr<Input> input);
    void LoadFromCartridge(std::shared_ptr<Cartridge> cartridge);

    // Software Read / Write
    void WriteByte(uint16 address, uint8 value);
    void WriteWord(uint16 address, uint16 value);
    uint8 ReadByte(uint16 address) const;
    uint16 ReadWord(uint16 address) const;

    // Hardware Read / Write
    void Write(uint16 address, uint8 value);
    uint8 Read(uint16 address) const;

private:
    void WriteDefaultValues();

private:
    uint8* data; // 65536
    
    bool inBootRom;
    bool colorGameboy;

	std::shared_ptr<Timer> timer;
    std::shared_ptr<Cartridge> cartridge;
    std::shared_ptr<Input> input;
    
	std::unique_ptr<MemoryController> memoryBankController;
};
