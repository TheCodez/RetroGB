#pragma once

class Processor;
class Memory;

class Video
{
public:
	Video(Memory* mem, Processor* cpu);
	~Video();

	void Reset();

private:
	Memory* memory;
	Processor* processor;
};

