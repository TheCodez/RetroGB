#pragma once

#include "Definitions.h"

class Memory
{
public:
    Memory();
    ~Memory();

    void Reset();
    void LoadRom(uint8* r);

    void WriteByte(uint16 address, uint8 value);
    void WriteWord(uint16 address, uint16 value);

    uint8 ReadByte(uint16 address) const;
    uint16 ReadWord(uint16 address) const;

private:
    uint8* rom;
    uint8 data[0x10000]; // 65536
};

