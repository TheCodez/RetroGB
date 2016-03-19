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

void Video::Reset()
{
}

void Video::ScanLine(int line)
{
    uint8 lcd = memory->ReadByte(0xFF40);
    
    if (IsBitSet(lcd, 7))
    {
        RenderBackground(line);
        RenderWindow(line);
        RenderSprites(line);
    }
    else
    {
        // black screen on gbc white on dmg
    }
}

void Video::RenderBackground(int line)
{
    uint8 lcd = memory->ReadByte(0xFF40);

    if (IsBitSet(lcd, 0))
    {
        int scrollY = memory->ReadByte(0xFF42);
        int scrollX = memory->ReadByte(0xFF43);
    }
}

void Video::RenderWindow(int line)
{
    uint8 lcd = memory->ReadByte(0xFF40);

    if (IsBitSet(lcd, 5))
    {
        int windowY = memory->ReadByte(0xFF4A);
        int windowX = memory->ReadByte(0xFF4B) - 7;
    }
}

void Video::RenderSprites(int line)
{
    uint8 lcd = memory->ReadByte(0xFF40);

    if (IsBitSet(lcd, 1))
    {
        int spriteWidth = 8;
        int spriteHeight = IsBitSet(lcd, 2) ? 16 : 8;

        // 40 sprites
        for (int sprite = 40; sprite > 0; sprite--)
        {
            // Every sprite has 4 bytes of memory assigned
            int index = sprite * 4;
            int spriteY = memory->ReadByte(0xFE00 + index + 0) - 16;
            int spriteX = memory->ReadByte(0xFE00 + index + 1) - 8;
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
            else if (spriteY > line || (spriteY + spriteHeight) < line)
            {
                continue;
            }

            // TODO render
        }
    }
}
