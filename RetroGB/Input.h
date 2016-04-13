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

    void Write(uint8 value);
    uint8 Read();

private:
    Memory* memory;
};

