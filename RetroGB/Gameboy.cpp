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

#include "Gameboy.h"
#include "Memory.h"
#include "Processor.h"
#include "Video.h"
#include "Cartridge.h"
#include "Timer.h"
#include "Input.h"

Gameboy::Gameboy(const std::function<void(Color*)>& updateScreenFunc)
{
    screenFunc = updateScreenFunc;
    memory = new Memory();
    processor = new Processor(memory);
    video = new Video(memory, processor);
    cartridge = new Cartridge();
    timer = new Timer(memory, processor);
    input = new Input(memory);

    memory->SetIOs(cartridge, timer, input);
}

Gameboy::~Gameboy()
{
    delete memory;
    delete processor;
    delete video;
    delete cartridge;
    delete timer;
    delete input;
}

void Gameboy::Run()
{
    if (cartridge->IsROMLoaded())
    {
        int cycles = 0;
        const int targetCycles = 70224;

        while (cycles < targetCycles)
        {
            cycles += processor->Run();
            video->Run(cycles);
            timer->Run(cycles);
            input->Run(cycles);
        }
        
        if (screenFunc)
            screenFunc(video->GetFrameBuffer());
    }
}

void Gameboy::Step()
{
    if (cartridge->IsROMLoaded())
    {
        processor->Run();
    }
}

void Gameboy::KeyPressed(int key)
{
    input->KeyPressed(key);
}

void Gameboy::KeyReleased(int key)
{
    input->KeyReleased(key);
}

void Gameboy::Reset(bool color)
{
    memory->Reset(color);
    processor->Reset(color);
    video->Reset(color);
    timer->Reset(color);
    input->Reset(color);
}

void Gameboy::ResetRom()
{
    if (cartridge->IsROMLoaded())
    {
        Reset(cartridge->IsGameboyColor());
        memory->LoadFromCartridge(cartridge);
    }
}

bool Gameboy::LoadRom(const std::string& fileName)
{
    if (cartridge->LoadRom(fileName))
    {
        Reset(cartridge->IsGameboyColor());

        return memory->LoadFromCartridge(cartridge);
    }

    return false;
}

Color* Gameboy::GetFrameBuffer() const
{
    return video->GetFrameBuffer();
}