#pragma once

#include <string>
#include "Definitions.h"

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
    Gameboy(UpdateScreenFunc func);
    ~Gameboy();

    void Run();
    void Step();
    void KeyPressed(int key);
    void KeyReleased(int key);

    const Color* GetFrameBuffer() const;
    void Reset(bool color = false);
    bool LoadRom(const std::string& fileName);

    Cartridge* GetCartridge() const { return cartridge; }
    Processor* GetProcessor() const { return processor; }
    Memory* GetMemory() const { return memory; }

private:
    Memory* memory;
    Processor* processor;
    Video* video;
    Cartridge* cartridge;
    Timer* timer;
    Input* input;
};

