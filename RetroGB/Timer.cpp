#include "Timer.h"
#include "Memory.h"
#include "Processor.h"

Timer::Timer(Memory* mem, Processor* cpu)
    : memory(mem), processor(cpu)
{
    Reset(false);
}

Timer::~Timer()
{
}

void Timer::Reset(bool color)
{
}

void Timer::Run(int cycles)
{
    uint8 div = memory->Read(0xFF04);
    div++;
    memory->Write(0xFF04, div);

    uint8 tima = memory->Read(0xFF05);
    tima++;

    if (tima == 0xFF)
    {
        tima = memory->Read(0xFF06);
        processor->RequestInterrupt(Interrupts::TIMER);
    }

    memory->Write(0xFF05, tima);
}

void Timer::ResetDIV()
{
    memory->Write(0xFF04, 0x00);
}
