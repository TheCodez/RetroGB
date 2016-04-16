#pragma once

#include "Definitions.h"

enum class CartridgeType : uint8
{
    ROMONLY,
    MBC1,
    MBC1_RAM,
    MBC1_RAM_BATTERY,
    MBC2,
    MBC2_BATTERY,
    ROM_RAM,
    ROM_RAM_BATTERY,
    MMM01,
    MMM01_RAM,
    MMM01_RAM_BATTERY,
    MBC3_TIMER_BATTERY,
    MBC3_TIMER_RAM_BATTERY,
    MBC3,
    MBC3_RAM,
    MBC3_RAM_BATTERY,
    MBC4,
    MBC4_RAM,
    MBC4_RAM_BATTERY,
    MBC5,
    MBC5_RAM,
    MBC5_RAM_BATTERY,
    MBC5_RUMBLE,
    MBC5_RUMBLE_RAM,
    MBC5_RUMBLE_RAM_BATTERY,
    POCKETCAMERA,
    BANDAITAMA5,
    HuC3,
    HuC1_RAM_BATTERY
};

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
    CartridgeType GetCartridgeType() const { return cartridgeType; }
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
    CartridgeType cartridgeType;
    int romSize;
    int ramSize;
    bool japanese;
    int version;
    int oldLicenseeCode;
};

