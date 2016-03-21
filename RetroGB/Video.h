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
    Vram
};

class Video
{
public:
    Video(Memory* mem, Processor* cpu);
    ~Video();

    void Reset(bool color = false);
    void WriteByte(uint16 address, uint8 value);
    uint8 ReadByte(uint16 address) const;

    void Run(uint8 cycles);
    void ScanLine(int scanLine);
    void RenderBackground(int scanLine);
    void RenderWindow(int scanLine);
    void RenderSprites(int scanLine);
private:
    Color GetColor(int colorNum, uint8 palette);

private:
    Memory* memory;
    Processor* processor;
    Mode mode;
    bool gameBoycolor;
    uint8 vram[0x8000];
    int modeCounter;
    int currLine;

    Color frameBuffer[SCREEN_WIDTH * SCREE_HEIGHT];
};

