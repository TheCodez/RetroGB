#pragma once

#include "Definitions.h"

class Memory;

class Timer
{
public:
    Timer(Memory* mem);
    ~Timer();

    void Reset(bool color);
    void Run(int cycles);

    void ResetDIV();

private:
    Memory* memory;
};

