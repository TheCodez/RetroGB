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

#include "Input.h"
#include "Memory.h"

Input::Input(std::shared_ptr<Memory> memory)
    : memory(memory)
{
    Reset(false);
}

Input::~Input()
{
}

void Input::Reset(bool color)
{
}

void Input::Run(unsigned int cycles)
{
}

void Input::KeyPressed(int key)
{

}

void Input::KeyReleased(int key)
{

}

void Input::Write(uint8 value)
{
}

uint8 Input::Read()
{
    return 0xFF;
}
