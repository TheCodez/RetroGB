#include "Processor.h"
#include "Memory.h"

Processor::Processor(Memory* mem)
	: memory(mem)
{
	Reset();
}


Processor::~Processor()
{
}

void Processor::Reset()
{

}

void Processor::SetFlag(uint8 flag)
{
	F = flag;
}

void Processor::EnableFlag(uint8 flag)
{
	F |= flag;
}

void Processor::DisableFlag(uint8 flag)
{
	F &= ~flag;
}

void Processor::ClearFlags(uint8 flag)
{
	SetFlag(FLAG_NONE);
}

bool Processor::IsFlagSet(uint8 flag)
{
	return (F & flag) != 0;
}
