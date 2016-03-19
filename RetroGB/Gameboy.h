#pragma once

#include <string>

class Processor;
class Memory;
class Video;
class Cartridge;

class Gameboy
{
public:
	Gameboy();
	~Gameboy();

    void Run();
    void Reset();
    void LoadRom(const std::string& fileName);

private:
	Memory* memory;
	Processor* processor;
	Video* video;
	Cartridge* cartridge;
};

