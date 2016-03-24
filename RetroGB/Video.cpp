#include "Video.h"
#include "Memory.h"
#include "Processor.h"

Video::Video(Memory* mem, Processor* cpu)
    : memory(mem), processor(cpu)
{
    Reset();
}


Video::~Video()
{
}

void Video::Reset(bool color)
{
    gameBoycolor = color;

    mode = Mode::HBlank;

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = 0; y < SCREE_HEIGHT; y++)
        {
            frameBuffer[x + y * SCREEN_WIDTH] = color ? Color::BLACK : Color::WHITE;
        }
    }
}

void Video::Run(uint8 cycles)
{
    modeCounter += cycles;

    switch (mode)
    {
    case Mode::HBlank:
        if (modeCounter >= 204)
        {
            modeCounter = 0;
            currLine++;

            if (currLine == 143)
            {
                mode = Mode::VBlank;
            }
        }
        break;
    case Mode::VBlank:
        if (modeCounter >= 4560)
        {
            modeCounter = 0;
            mode = Mode::HBlank;
            currLine++;
        }
        break;
    case Mode::Oam:
        if (modeCounter >= 80)
        {
            modeCounter = 0;
            mode = Mode::Vram;
        }
        break;
    case Mode::Vram:
        if (modeCounter >= 172)
        {
            modeCounter = 0;
            mode = Mode::VBlank;

            ScanLine(currLine);
        }
        break;
    }
}

void Video::ScanLine(int scanLine)
{
    uint8 lcdc = memory->ReadByte(0xFF40);
    
    if (IsBitSet(lcdc, 7))
    {
        RenderBackground(scanLine);
        RenderWindow(scanLine);
        RenderSprites(scanLine);
    }
    else
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            frameBuffer[x + scanLine * SCREEN_WIDTH] = gameBoycolor ? Color::BLACK : Color::WHITE;
        }
    }
}

void Video::RenderBackground(int scanLine)
{
    uint8 lcdc = memory->ReadByte(0xFF40);

    if (IsBitSet(lcdc, 0))
    {
        int scrollY = memory->ReadByte(0xFF42);
        int scrollX = memory->ReadByte(0xFF43);
        int tiles = IsBitSet(lcdc, 4) ? 0x8000 : 0x8800;
        int maps = IsBitSet(lcdc, 3) ? 0x9C00 : 0x9800;
        int yPos = scrollY + scanLine;
    }
}

void Video::RenderWindow(int scanLine)
{
    uint8 lcdc = memory->ReadByte(0xFF40);

    if (IsBitSet(lcdc, 5))
    {
        int windowY = memory->ReadByte(0xFF4A);
        int windowX = memory->ReadByte(0xFF4B) - 7;
        int tiles = IsBitSet(lcdc, 4) ? 0x8000 : 0x8800;
        int maps = IsBitSet(lcdc, 3) ? 0x9C00 : 0x9800;
        int yPos = scanLine - windowY;
    }
}

void Video::RenderSprites(int scanLine)
{
    uint8 lcdc = memory->ReadByte(0xFF40);

    if (IsBitSet(lcdc, 1))
    {
        int spriteWidth = 8;
        int spriteHeight = IsBitSet(lcdc, 2) ? 16 : 8;

        // 40 sprites
        for (int sprite = 40; sprite > 0; sprite--)
        {
            // Every sprite has 4 bytes of memory assigned
            int index = sprite * 4;
            int spriteY = memory->ReadByte(0xFE00 + index + 0) - 16;
            int spriteX = memory->ReadByte(0xFE00 + index + 1) - 8;
            uint8 tileLocation = memory->ReadByte(0xFE00 + index + 2);
            uint8 attributes = memory->ReadByte(0xFE00 + index + 3);

            bool belowBG = IsBitSet(attributes, 7);
            bool yFlip = IsBitSet(attributes, 6);
            bool xFlip = IsBitSet(attributes, 5);
            uint16 paletteNumber = IsBitSet(attributes, 4) ? 0xFF49 : 0xFF48;

            // don't show sprites if outside of bounds
            if (spriteX < -7 || spriteX >= SCREEN_WIDTH)
            {
                continue;
            }
            else if (spriteY > scanLine || (spriteY + spriteHeight) < scanLine)
            {
                continue;
            }

            int line = yFlip ? spriteHeight - (scanLine - spriteY) * 2 : (scanLine - spriteY) * 2;

            uint16 tileAddress = 0x8000 + tileLocation * 16;
            uint8 data1 = memory->ReadByte(tileAddress + line);
            uint8 data2 = memory->ReadByte(tileAddress + line + 1);

            for (int pixelX = 0; pixelX < 8; pixelX++)
            {
                int posX = spriteX + pixelX;
                int colorBit = xFlip ? 7 - pixelX : pixelX;
                int colorNum = GetBitValue(data1, colorBit) | GetBitValue(data2, colorBit);

                if (belowBG)
                {
                    if (frameBuffer[posX + scanLine * SCREEN_WIDTH] != Color::WHITE)
                        continue;
                }

                uint8 palette = memory->ReadByte(paletteNumber);
                Color color = GetColor(colorNum, palette);

                if (color == Color::WHITE)
                    continue;

                frameBuffer[posX + scanLine * SCREEN_WIDTH] = color;
            }
        }
    }
}

Color Video::GetColor(int colorNum, uint8 palette)
{
    //                  White,        Light grey,                Dark grey,              Black
    Color colors[4] = { Color::WHITE, Color(170, 170, 170, 255), Color(85, 85, 85, 255), Color::BLACK };

    int color = 0;
    int high, low = 0;

    switch (colorNum)
    {
    case 3:
        high = 7; low = 6;
        break;
    case 2:
        high = 5; low = 4;
        break;
    case 1:
        high = 3; low = 2;
        break;
    case 0:
        high = 1; low = 0;
        break;
    }

    color = GetBitValue(palette, high) | GetBitValue(palette, low);

    return colors[color];
}

