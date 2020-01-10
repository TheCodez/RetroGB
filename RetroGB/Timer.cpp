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

#include "Timer.h"
#include "Memory.h"
#include "Processor.h"

Timer::Timer(std::shared_ptr<Memory> memory, std::shared_ptr<Processor> cpu)
    : memory(memory), processor(cpu)
{
    Reset(false);
}

Timer::~Timer()
{
}

void Timer::Reset(bool color)
{
}

void Timer::Run(unsigned int cycles)
{
    //uint8 div = memory->Read(0xFF04);
    //div++;
    //memory->Write(0xFF04, div);

    //uint8 tima = memory->Read(0xFF05);
    //tima++;

    //if (tima == 0xFF)
    //{
    //    tima = memory->Read(0xFF06);
    //    processor->RequestInterrupt(Interrupt::Time);
    //}

    //memory->Write(0xFF05, tima);
}

void Timer::ResetDIV()
{
    memory->Write(0xFF04, 0x00);
}
