#include "Gameboy.h"

int main(int argc, const char** argv)
{
	Gameboy* gameboy = new Gameboy();
    gameboy->LoadRom("E:/RetroGB/tetris.gb");
    gameboy->Run();

    //delete gameboy;

	return 0;
}