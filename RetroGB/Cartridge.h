#pragma once

#include <string>
#include "Definitions.h"

class Cartridge
{
public:
	Cartridge();
	~Cartridge();

    void LoadRom(const std::string& fileName);
	void Reset();

    uint8* GetROM() const { return rom; }
    bool IsROMLoaded() const { return romLoaded; }

private:
    uint8* rom;

    bool romLoaded;

    std::string title;
    uint16 licenseeCode;
    bool colorGameboy;
    bool superGameboy;
    int cartridgeType;
    int romSize;
    int ramSize;
    bool japanese;
    int version;
};

