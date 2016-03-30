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
    cartridgeType = 0;
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

        char* memblock = new char[size];
        file.seekg(0, std::ios::beg);
        file.read(memblock, size);
        file.close();

        memcpy(rom, memblock, size);

        delete[] memblock;

        if (rom != nullptr && size > 0)
        {
            for (int i = 0x0134; i < 0x0143; i++)
            {
                if (rom[i] == 0)
                    break;

                title += rom[i];
            }

            licenseeCode = (rom[0x0144] << 8) | rom[0x0145];
            colorGameboy = rom[0x0143] == 0x80 || (rom[0x0143] == 0xC0);
            superGameboy = rom[0x0146] == 0x03;
            cartridgeType = rom[0x0147];
            romSize = rom[0x0148];
            ramSize = rom[0x0149];
            japanese = rom[0x014A] == 0x00;
            version = rom[0x014C];
            oldLicenseeCode = rom[0x014B];

            LOG_LINE("Title: %s", title.c_str());
            LOG_LINE("Licensee Code: %d", licenseeCode);
            LOG_LINE("Gameboy Color: %s", colorGameboy ? "true" : "false");
            LOG_LINE("Super Gameboy: %s", superGameboy ? "true" : "false");
            LOG_LINE("Cartridge Type: %d", cartridgeType);
            LOG_LINE("ROM Size: %d", romSize);
            LOG_LINE("RAM Size: %d", ramSize);
            LOG_LINE("Japanese: %s", japanese ? "true" : "false");
            LOG_LINE("Version: %d", version);
            LOG_LINE("Old Licensee Code: %d", oldLicenseeCode);

            return true;
        }
    }
    return false;
}
