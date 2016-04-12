#include "Timer.h"
#include "Memory.h"

Timer::Timer(Memory* mem)
    : memory(mem)
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
    //uint8 div = memory->Read(0xFF04);
    //div++;
    //memory->Write(0xFF04, div);
}

void Timer::ResetDIV()
{
    memory->Write(0xFF04, 0);
}
