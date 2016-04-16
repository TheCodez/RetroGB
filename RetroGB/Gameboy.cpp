#include "Gameboy.h"
#include "Memory.h"
#include "Processor.h"
#include "Video.h"
#include "Cartridge.h"
#include "Timer.h"
#include "Input.h"
#include "Color.h"

Gameboy::Gameboy(UpdateScreenFunc func)
{
    screenFunc = func;
    memory = new Memory();
    processor = new Processor(memory);
    video = new Video(memory, processor);
    cartridge = new Cartridge();
    timer = new Timer(memory, processor);
    input = new Input(memory);

    memory->SetIOs(cartridge, timer, input);
}

Gameboy::~Gameboy()
{
    delete memory;
    delete processor;
    delete video;
    delete cartridge;
    delete timer;
    delete input;
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
            //timer->Run(cycles);
            //input->Run(cycles);
        }
        
        if (screenFunc)
            screenFunc(video->GetFrameBuffer());
    }
}

void Gameboy::Step()
{
    if (cartridge->IsROMLoaded())
    {
        processor->Run();
    }
}

void Gameboy::KeyPressed(int key)
{
    input->KeyPressed(key);
}

void Gameboy::KeyReleased(int key)
{
    input->KeyReleased(key);
}

void Gameboy::Reset(bool color)
{
    memory->Reset(color);
    processor->Reset(color);
    video->Reset(color);
    timer->Reset(color);
    input->Reset(color);
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

Color* Gameboy::GetFrameBuffer() const
{
    return video->GetFrameBuffer();
}