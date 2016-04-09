#pragma once

#include <string>
#include "Definitions.h"

class Processor;
class Memory;
class Video;
class Cartridge;
struct Color;

class Gameboy
{
public:
    Gameboy(UpdateScreenFunc func);
    ~Gameboy();

    void Run();
    void Step();
    const Color* GetFrameBuffer() const;
    void Reset(bool color = false);
    bool LoadRom(const std::string& fileName);
    Cartridge* GetCartridge() const { return cartridge; }

public:
    Memory* memory;
    Processor* processor;
    Video* video;
    Cartridge* cartridge;
};

