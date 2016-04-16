#pragma once

#include "Definitions.h"

class Cartridge; 
class Memory;

class MemoryController
{
public:
    MemoryController(Memory* memory, Cartridge* cartridge);
    ~MemoryController();

    virtual void Reset(bool color) {}
    virtual void Write(uint16 address, uint8 value);
    virtual uint8 Read(uint16 address) const;

protected:
    Memory* memory;
    Cartridge* cartridge;
};
