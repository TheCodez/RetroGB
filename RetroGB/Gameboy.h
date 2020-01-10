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

class Processor;
class Memory;
class Video;
class Cartridge;
class Timer;
class Input;
struct Color;

class Gameboy
{
public:
    Gameboy(const std::function<void(Color*)>& renderFunction);
    ~Gameboy();

    void Run();
    void Step();
    void KeyPressed(int key);
    void KeyReleased(int key);

    Color* GetFrameBuffer() const;
    void Reset(bool color = false);
    void ResetRom();
    void LoadRom(const std::string& fileName);

    void SetPaused(bool pause) { paused = pause; }
    bool IsPaused() const { return paused; }

	const std::shared_ptr<Cartridge>& GetCartridge() const { return cartridge; }
	const std::shared_ptr<Processor>& GetProcessor() const { return processor; }
	const std::shared_ptr<Memory>& GetMemory() const { return memory; }

private:
    std::shared_ptr<Memory> memory;
	std::shared_ptr<Processor> processor;
	std::shared_ptr<Video> video;
	std::shared_ptr<Cartridge> cartridge;
	std::shared_ptr<Timer> timer;
	std::shared_ptr<Input> input;
    
	std::function<void(Color*)> renderCallback;
    
	bool paused;
};
