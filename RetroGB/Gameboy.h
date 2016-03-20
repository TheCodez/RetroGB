#pragma once

#include <string>

class Processor;
class Memory;
class Video;
class Cartridge;

class Gameboy
{
public:
    Gameboy();
    ~Gameboy();

    void Run();
    void Reset(bool color = false);
    bool LoadRom(const std::string& fileName);
    Cartridge* GetCartridge() const { return cartridge; }

private:
    Memory* memory;
    Processor* processor;
    Video* video;
    Cartridge* cartridge;
};

