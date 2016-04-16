#pragma once

#include "Definitions.h"
#include "Color.h"

class Processor;
class Memory;

enum class Mode
{
    HBlank,
    VBlank,
    Oam,
    DataTransfer
};

class Video
{
public:
    Video(Memory* mem, Processor* cpu);
    ~Video();

    void Reset(bool color);

    void Run(int cycles);
    void ScanLine(int scanLine);
    void RenderBackground(int scanLine);
    void RenderWindow(int scanLine);
    void RenderSprites(int scanLine);

    Color* GetFrameBuffer() const { return frameBuffer; }
private:
    Color GetColor(int colorNum, uint8 palette);
    void CompareLYToLYC();

private:
    Memory* memory;
    Processor* processor;
    Mode mode;
    bool gameBoycolor;
    int modeCounter;
    int scanline;

    Color* frameBuffer;
};

