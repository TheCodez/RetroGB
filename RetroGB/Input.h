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

class Memory;

class Input
{
public:
    Input(std::shared_ptr<Memory> memory);
    ~Input();

    void Reset(bool color);
    void Run(unsigned int cycles);

    void KeyPressed(int key);
    void KeyReleased(int key);

    void Write(uint8 value);
    uint8 Read();

private:
	std::shared_ptr<Memory> memory;
};

