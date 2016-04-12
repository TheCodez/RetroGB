#include "Gameboy.h"
#include "Memory.h"
#include "Processor.h"
#include "Video.h"
#include "Cartridge.h"
#include "Color.h"

Gameboy::Gameboy(UpdateScreenFunc func)
{
    memory = new Memory();
    processor = new Processor(memory);
    video = new Video(func, memory, processor);
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
    if (cartridge->IsROMLoaded())
    {
        int cycles = 0;
        const int targetCycles = 70224;

        while (cycles < targetCycles)
        {
            cycles += processor->Run();
            video->Run(cycles);
        }
    }
}

void Gameboy::Step()
{
    if (cartridge->IsROMLoaded())
    {
        processor->Run();
    }
}

void Gameboy::Reset(bool color)
{
    memory->Reset(color);
    processor->Reset(color);
    video->Reset(color);
    //cartridge->Reset();
}

bool Gameboy::LoadRom(const std::string& fileName)
{
    if (cartridge->LoadRom(fileName))
    {
        Reset(cartridge->IsGameboyColor());
        memory->LoadFromCartridge(cartridge);

        return true;
    }

    return false;
}

const Color* Gameboy::GetFrameBuffer() const
{
    return video->GetFrameBuffer();
}