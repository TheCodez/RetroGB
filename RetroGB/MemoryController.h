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

#include <memory>

class Cartridge; 
class Memory;

class MemoryController
{
public:
    MemoryController(Memory* memory, std::shared_ptr<Cartridge> cartridge);
    virtual ~MemoryController();

    virtual void Reset(bool color) {}
    virtual void Write(uint16 address, uint8 value);
    virtual uint8 Read(uint16 address) const;

protected:
	Memory* memory;
	std::shared_ptr<Cartridge> cartridge;
};
