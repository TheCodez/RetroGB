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

    uint8 ReadByte(uint16 address);
    uint16 ReadWord(uint16 address);

private:
    uint8 rom[0x8000];
    uint8 eram[0x2000];
    uint8 io[0x100];
    uint8 vram[0x2000];
    uint8 oam[0x100];
    uint8 wram[0x2000];
    uint8 hram[0x80];
    uint8 interruptEnable;
    uint8 interruptFlag;

    uint8 data[0x10000]; // 65536
    bool inBootRom;
};

