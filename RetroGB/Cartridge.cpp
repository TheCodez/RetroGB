#include "Cartridge.h"
#include <iostream>
#include <fstream>

Cartridge::Cartridge()
    : rom(nullptr)
{
    Reset();
}

Cartridge::~Cartridge()
{
    delete[] rom;
}

void Cartridge::Reset()
{
    if (rom != nullptr)
    {
        delete[] rom;
        rom = nullptr;
    }

    title = "";
    licenseeCode = 0;
    colorGameboy = false;
    superGameboy = false;
    cartridgeType = CartridgeType::ROMONLY;
    romSize = 0;
    ramSize = 0;
    japanese = false;
    version = 0;
    oldLicenseeCode = 0;
}

bool Cartridge::LoadRom(const std::string& fileName)
{
    Reset();

    std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        int size = static_cast<int>(file.tellg());
        rom = new uint8[size];

        file.seekg(0, std::ios::beg);
        file.read((char*)rom, size);
        file.close();

        if (rom != nullptr && size > 0)
        {
            for (int i = 0x0134; i < 0x0143; i++)
            {
                if (rom[i] == 0)
                    break;

                title += rom[i];
            }

            licenseeCode = (rom[0x0144] << 4) | rom[0x0145];
            colorGameboy = rom[0x0143] == 0x80 || (rom[0x0143] == 0xC0);
            superGameboy = rom[0x0146] == 0x03;
            cartridgeType = (CartridgeType)rom[0x0147];
            romSize = rom[0x0148];
            ramSize = rom[0x0149];
            japanese = rom[0x014A] == 0x00;
            version = rom[0x014C];
            oldLicenseeCode = rom[0x014B];

            LogLine("Title: %s", title.c_str());
            LogLine("Licensee Code: %d", licenseeCode);
            LogLine("Gameboy Color: %s", colorGameboy ? "true" : "false");
            LogLine("Super Gameboy: %s", superGameboy ? "true" : "false");
            LogLine("Cartridge Type: %d", cartridgeType);
            LogLine("ROM Size: %d", romSize);
            LogLine("RAM Size: %d", ramSize);
            LogLine("Japanese: %s", japanese ? "true" : "false");
            LogLine("Version: %d", version);
            LogLine("Old Licensee Code: %d", oldLicenseeCode);

            return true;
        }
    }
    return false;
}
