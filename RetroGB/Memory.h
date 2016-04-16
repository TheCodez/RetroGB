#pragma once

#include "Definitions.h"

class Cartridge;
class Timer;
class Input;
class MemoryController;

class Memory
{
public:
    Memory();
    ~Memory();

    void SetIOs(Cartridge* cartridge, Timer* timer, Input* input);
    void Reset(bool color);
    void LoadFromCartridge(Cartridge* cartridge);

    // Software Read / Write
    void WriteByte(uint16 address, uint8 value);
    void WriteWord(uint16 address, uint16 value);
    uint8 ReadByte(uint16 address);
    uint16 ReadWord(uint16 address);

    // Hardware Read / Write
    void Write(uint16 address, uint8 value);
    uint8 Read(uint16 address) const;

    void Save();
private:
    uint8 data[0x10000]; // 65536
    bool inBootRom;
    bool colorGameboy;
    Timer* timer;
    Cartridge* cartridge;
    Input* input;
    MemoryController* memoryController;
};

