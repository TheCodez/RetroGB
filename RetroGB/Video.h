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
#include "Color.h"

class Processor;
class Memory;

enum class Mode
{
    HBlank,
    VBlank,
    Oam,
    DataTransfer
};

class Video
{
public:
    Video(Memory* mem, Processor* cpu);
    ~Video();

    void Reset(bool color);

    void Run(int cycles);
    void ScanLine(int scanLine);
    void RenderBackground(int scanLine);
    void RenderWindow(int scanLine);
    void RenderSprites(int scanLine);

    Color* GetFrameBuffer() const { return frameBuffer; }
private:
    Color GetColor(int colorNum, uint8 palette);
    void CompareLYToLYC();

private:
    Memory* memory;
    Processor* processor;
    Mode mode;
    bool gameBoycolor;
    int modeCounter;
    int scanline;

    Color* frameBuffer;
};

