#include "Gameboy.h"
#include "Memory.h"
#include "Processor.h"
#include "Video.h"
#include "Cartridge.h"
#include <Windows.h>

Gameboy::Gameboy()
{
    memory = new Memory();
    processor = new Processor(memory);
    video = new Video(memory, processor);
    cartridge = new Cartridge();
}


Gameboy::~Gameboy()
{
    delete memory;
    delete processor;
    delete video;
    delete cartridge;
}

void Gameboy::Run()
{
    while (true)
    {
        if (cartridge->IsROMLoaded())
        {
            uint8 cycles = processor->Run();
            video->Run(cycles);
            Sleep(600); // to see whats going on
        }
    }
}

void Gameboy::Reset(bool color)
{
    memory->Reset();
    processor->Reset(color);
    video->Reset(color);
    //cartridge->Reset();
}

bool Gameboy::LoadRom(const std::string& fileName)
{
    if (cartridge->LoadRom(fileName))
    {
        Reset(cartridge->IsGameboyColor());
        memory->LoadRom(cartridge->GetROM());

        return true;
    }

    return false;
}