#pragma once

class Memory;

class Processor
{
public:
	Processor(Memory* mem);
	~Processor();

	void Reset();

private:
	Memory* memory;
};

