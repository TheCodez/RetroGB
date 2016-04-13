#pragma once

#include "Definitions.h"

class Memory;
class Processor;

class Timer
{
public:
    Timer(Memory* mem, Processor* cpu);
    ~Timer();

    void Reset(bool color);
    void Run(int cycles);

    void ResetDIV();

private:
    Memory* memory;
    Processor* processor;
};

