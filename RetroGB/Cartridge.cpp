#include "Cartridge.h"
#include <iostream>
#include <fstream>

Cartridge::Cartridge()
{
}


Cartridge::~Cartridge()
{
    delete[] rom;
}

void Cartridge::Reset()
{
    delete[] rom;

    licenseeCode = 0;
    colorGameboy = false;
    superGameboy = false;
    cartridgeType = rom[0x0147];
    romSize = 0;
    ramSize = 0;
    japanese = false;
    version = 0;

    romLoaded = false;
}

void Cartridge::LoadRom(const std::string& fileName)
{
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
    }

    if (rom != nullptr)
    {
        char name[12];

        for (int i = 0; i < 12; i++)
        {
            name[i] = rom[0x0134 + i];
        }

        title = name;
        StringReplace(title, "0", "");

        licenseeCode = (rom[0x0144] << 8) | rom[0x0145];
        colorGameboy = rom[0x0143] == 0x80 || (rom[0x0143] == 0xC0);
        superGameboy = rom[0x0146] == 0x03;
        cartridgeType = rom[0x0147];
        romSize = rom[0x0148];
        ramSize = rom[0x0149];
        japanese = rom[0x014A] == 0x00;
        version = rom[0x014C];

        romLoaded = true;

        LOG("Title: %s", title.c_str());
        LOG("Gameboy Color: %s", colorGameboy ? "true" : "false");
        LOG("Super Gameboy: %s", superGameboy ? "true" : "false");
        LOG("Cartridge Type: %d", cartridgeType);
        LOG("ROM Size: %d", romSize);
        LOG("RAM Size: %d", ramSize);
        LOG("Japanese: %s", japanese ? "true" : "false");
        LOG("Version: %d", version);
    }
}
