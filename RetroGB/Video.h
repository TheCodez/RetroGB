#pragma once

class Processor;
class Memory;

class Video
{
public:
    Video(Memory* mem, Processor* cpu);
    ~Video();

    void Reset();

    void ScanLine(int line);
    void RenderBackground(int line);
    void RenderWindow(int line);
    void RenderSprites(int line);

private:
    Memory* memory;
    Processor* processor;
};

