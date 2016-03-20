#include "Gameboy.h"

int main(int argc, const char** argv)
{
    Gameboy* gameboy = new Gameboy();
    gameboy->LoadRom("E:/RetroGB/Roms/Super Mario Bros. Deluxe.gbc");
    //gameboy->LoadRom("E:/RetroGB/Roms/tetris.gb");
    //gameboy->LoadRom("E:/RetroGB/Roms/Super Mario Land.gb");
    gameboy->Run();

    delete gameboy;

    return 0;
}