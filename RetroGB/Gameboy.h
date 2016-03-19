#pragma once

class Processor;
class Memory;
class Video;
class Cartridge;

class Gameboy
{
public:
	Gameboy();
	~Gameboy();

	void Reset();

private:
	Memory* memory;
	Processor* processor;
	Video* video;
	Cartridge* cartridge;
};

