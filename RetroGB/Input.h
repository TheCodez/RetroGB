#pragma once

#include "Definitions.h"

class Memory;

class Input
{
public:
    Input(Memory* mem);
    ~Input();

    void Reset(bool color);
    void Run(int cycles);

    void KeyPressed(int key);
    void KeyReleased(int key);

private:
    Memory* memory;
};

