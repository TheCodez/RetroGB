#pragma once

#include <string>
#include "Definitions.h"

class Cartridge
{
public:
    Cartridge();
    ~Cartridge();

    bool LoadRom(const std::string& fileName);
    void Reset();

    const std::string& GetTitle() const { return title; }
    int GetLicenseeCode() const { return licenseeCode; }
    bool IsGameboyColor() const { return colorGameboy; }
    bool IsSuperGameboy() const { return superGameboy; }
    int GetCartridgeType() const { return cartridgeType; }
    int GetRomSize() const { return romSize; }
    int GetRamSize() const { return ramSize; }
    bool IsJapanese() const { return japanese; }
    int GetVersion() const { return version; }
    int GetOldLicenseeCode() const { return oldLicenseeCode; }
    uint8* GetROM() const { return rom; }
    
    bool IsROMLoaded() const { return rom != nullptr; }

private:
    uint8* rom;
    std::string title;
    int licenseeCode;
    bool colorGameboy;
    bool superGameboy;
    int cartridgeType;
    int romSize;
    int ramSize;
    bool japanese;
    int version;
    int oldLicenseeCode;
};

