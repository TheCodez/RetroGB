#pragma once

#include "Definitions.h"
#include "MemoryController.h"

class Cartridge;
class Memory;

class Mbc1 : public MemoryController
{
    enum class BankingMode : uint8
    {
        ROMBanking,
        RAMBanking
    };


public:
    Mbc1(Memory* memory, Cartridge* cartridge);
    ~Mbc1();

    virtual void Reset(bool color) override;
    virtual void Write(uint16 address, uint8 value) override;
    virtual uint8 Read(uint16 address) const override;

private:
    uint8 romBank;
    uint8 ramBank;
    uint8* ramBanks;

    uint16 romOffset;
    uint16 ramOffset;
    bool ramEnabled;
    BankingMode bankMode;
};

