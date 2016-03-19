#include "Video.h"
#include "Memory.h"
#include "Processor.h"

Video::Video(Memory* mem, Processor* cpu)
	: memory(mem), processor(cpu)
{
}


Video::~Video()
{
}

void Video::Reset()
{
}