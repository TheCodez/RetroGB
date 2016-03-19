#include "Gameboy.h"
#include "Memory.h"
#include "Processor.h"
#include "Video.h"
#include "Cartridge.h"

Gameboy::Gameboy()
{
	memory = new Memory();
	processor = new Processor(memory);
	video = new Video(memory, processor);
	cartridge = new Cartridge();
}


Gameboy::~Gameboy()
{
	delete memory;
	delete processor;
	delete video;
	delete cartridge;
}

void Gameboy::Reset()
{
	memory->Reset();
	processor->Reset();
	video->Reset();
	cartridge->Reset();
}