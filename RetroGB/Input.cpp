#include "Input.h"
#include "Memory.h"

Input::Input(Memory* mem)
    : memory(mem)
{
    Reset(false);
}

Input::~Input()
{
}

void Input::Reset(bool color)
{
}

void Input::Run(int cycles)
{
}

void Input::KeyPressed(int key)
{

}

void Input::KeyReleased(int key)
{

}

void Input::Write(uint8 value)
{
}

uint8 Input::Read()
{
    return 0xFF;
}
