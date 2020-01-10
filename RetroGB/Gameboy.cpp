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

Gameboy::Gameboy(const std::function<void(Color*)>& renderFunction)
	: renderCallback(renderFunction), paused(false)
{
	memory = std::make_shared<Memory>();
    processor = std::make_shared<Processor>(memory);
    video = std::make_shared<Video>(memory, processor);
    timer = std::make_shared<Timer>(memory, processor);
    input = std::make_shared<Input>(memory);

	cartridge = std::make_shared<Cartridge>();

    memory->RegisterInputs(cartridge, timer, input);
}

Gameboy::~Gameboy() = default;

void Gameboy::Run()
{
    if (!paused && cartridge->IsROMLoaded())
    {
		unsigned int cycles = 0;
        const unsigned int targetCycles = 70224;

        while (cycles < targetCycles)
        {
            cycles += processor->Run();
            video->Run(cycles);
            timer->Run(cycles);
            input->Run(cycles);
        }
        
		if (renderCallback)
		{
			renderCallback(video->GetFrameBuffer());
		}
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

    paused = false;
}

void Gameboy::ResetRom()
{
    if (cartridge->IsROMLoaded())
    {
        Reset(cartridge->IsGameboyColor());
        memory->LoadFromCartridge(cartridge);
    }
}

void Gameboy::LoadRom(const std::string& fileName)
{
    if (cartridge->LoadRom(fileName))
    {
        Reset(cartridge->IsGameboyColor());

        memory->LoadFromCartridge(cartridge);
    }
}

Color* Gameboy::GetFrameBuffer() const
{
    return video->GetFrameBuffer();
}
