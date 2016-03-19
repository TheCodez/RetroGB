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
            Sleep(400); // to see whats going on
        }
    }
}

void Gameboy::Reset()
{
    memory->Reset();
    processor->Reset();
    video->Reset();
    cartridge->Reset();
}

void Gameboy::LoadRom(const std::string& fileName)
{
    cartridge->LoadRom(fileName);
    memory->LoadRom(cartridge->GetROM());
}