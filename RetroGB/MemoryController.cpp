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

#include "MemoryController.h"
#include "Memory.h"
#include "Cartridge.h"


MemoryController::MemoryController(Memory* memory, std::shared_ptr<Cartridge> cartridge)
    : memory(memory), cartridge(cartridge)
{
}

MemoryController::~MemoryController()
{
}

void MemoryController::Write(uint16 address, uint8 value)
{
    memory->Write(address, value);
}

uint8 MemoryController::Read(uint16 address) const
{
    return memory->Read(address);
}