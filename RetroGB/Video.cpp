#include "Video.h"
#include "Memory.h"
#include "Processor.h"

Video::Video(Memory* mem, Processor* cpu)
    : memory(mem), processor(cpu)
{
    frameBuffer = new Color[SCREEN_WIDTH * SCREEN_HEIGHT];
    Reset(false);
}

Video::~Video()
{
    delete[] frameBuffer;
}

void Video::Reset(bool color)
{
    scanline = 0;
    gameBoycolor = color;
    modeCounter = 0;
    mode = Mode::VBlank;

    int size = SCREEN_WIDTH * SCREEN_HEIGHT;
    for (int i = 0; i < size; i++)
    {
        frameBuffer[i] = color ? Color::BLACK : Color::WHITE;
    }
}

void Video::Run(int cycles)
{
    modeCounter += cycles;

    switch (mode)
    {
        case Mode::Oam:
            if (modeCounter >= 80)
            {
                modeCounter = 0;
                mode = Mode::DataTransfer;
            }
            break;
        case Mode::DataTransfer:
            if (modeCounter >= 172)
            {
                // Enter hblank
                mode = Mode::HBlank;

                //processor->RequestInterrupt(Interrupts::LCDSTAT);

                ScanLine(scanline);
            }
            break;

        case Mode::HBlank:
            if (modeCounter >= 204)
            {
                modeCounter = 0;
                scanline++;
            
                memory->Write(0xFF44, scanline);
                CompareLYToLYC();

                if (scanline == 144)
                {
                    mode = Mode::VBlank;

                    /*processor->RequestInterrupt(Interrupts::VBlank);

                    uint8 stat = memory->Read(0xFF41);
                    if (IsBitSet(stat, 4))
                    {
                        processor->RequestInterrupt(Interrupts::LCDSTAT);
                    }*/
                }
                else
                {
                    mode = Mode::Oam;

                    /*uint8 stat = memory->Read(0xFF41);
                    if (IsBitSet(stat, 5))
                    {
                        processor->RequestInterrupt(Interrupts::LCDSTAT);
                    }*/
                }
            }
            break;

        case Mode::VBlank:
            if (modeCounter >= 456)
            {
                modeCounter = 0;
                scanline++;

                if (scanline > 153)
                {
                    mode = Mode::Oam;
                    scanline = 0;
                }
            }
            break;
    }
}

void Video::CompareLYToLYC()
{
    uint8 stat = memory->Read(0xFF41);
    uint8 lyc = memory->Read(0xFF45);

    if (lyc == scanline)
    {
        SetBit(stat, 2);

        if (IsBitSet(stat, 6))
        {
            //processor->RequestInterrupt(Interrupts::LCDSTAT);
        }
    }
    else
    {
        ResetBit(stat, 2);
    }

    memory->Write(0xFF41, stat);
}

void Video::ScanLine(int scanLine)
{
    uint8 lcdc = memory->Read(0xFF40);
    
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
    uint8 lcdc = memory->Read(0xFF40);

    if (IsBitSet(lcdc, 0))
    {
        int scrollY = memory->Read(0xFF42);
        int scrollX = memory->Read(0xFF43);
        uint16 tiles = IsBitSet(lcdc, 4) ? 0x8000 : 0x8800;
        uint16 map = IsBitSet(lcdc, 3) ? 0x9C00 : 0x9800;
        int line = scrollY + scanLine;
        int y = line / 8;
        int row = y * 32;

        for (int column = 0; column < 32; column++)
        {
            int tile = 0;

            if (tiles == 0x8800)
            {
                // signed data
                tile = 128 + static_cast<int8>(memory->Read(map + row + column));
            }
            else
            {
                tile = memory->Read(map + row + column);
            }

            int offsetX = column * 8;
            int tileAddress = tiles + (tile * 16) + (line % 8) * 2;

            uint8 data1 = memory->Read(tileAddress);
            uint8 data2 = memory->Read(tileAddress + 1);

            for (int pixelX = 0; pixelX < 8; pixelX++)
            {
                int posX = offsetX + pixelX - scrollX;

                if (posX >= SCREEN_WIDTH)
                    continue;

                int colorBit = 7 - pixelX;
                int colorNum = GetBitValue(data1, colorBit) | (GetBitValue(data2, colorBit) * 2);

                uint8 palette = memory->Read(0xFF47);
                Color color = GetColor(colorNum, palette);

                frameBuffer[posX + scanLine * SCREEN_WIDTH] = color;
            }
        }
    }
    else
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            frameBuffer[x + scanLine * SCREEN_WIDTH] = Color::WHITE;
        }
    }
}

void Video::RenderWindow(int scanLine)
{
    uint8 lcdc = memory->Read(0xFF40);

    if (IsBitSet(lcdc, 5))
    {
        int windowY = memory->Read(0xFF4A);
        int windowX = memory->Read(0xFF4B) - 7;
        uint16 tiles = IsBitSet(lcdc, 4) ? 0x8000 : 0x8800;
        uint16 maps = IsBitSet(lcdc, 3) ? 0x9C00 : 0x9800;
        int yPos = scanLine - windowY;
    }
}

void Video::RenderSprites(int scanLine)
{
    uint8 lcdc = memory->Read(0xFF40);

    if (IsBitSet(lcdc, 1))
    {
        int spriteWidth = 8;
        int spriteHeight = IsBitSet(lcdc, 2) ? 16 : 8;

        // 40 sprites
        for (int sprite = 39; sprite >= 0; sprite--)
        {
            // Every sprite has 4 bytes of memory assigned
            int index = sprite * 4;
            int spriteY = memory->Read(0xFE00 + index + 0) - 16;
            int spriteX = memory->Read(0xFE00 + index + 1) - 8;
            uint8 tileLocation = memory->Read(0xFE00 + index + 2);
            uint8 attributes = memory->Read(0xFE00 + index + 3);

            bool belowBG = IsBitSet(attributes, 7);
            bool yFlip = IsBitSet(attributes, 6);
            bool xFlip = IsBitSet(attributes, 5);
            uint16 paletteNumber = IsBitSet(attributes, 4) ? 0xFF49 : 0xFF48;

            // don't show sprites if outside of bounds
            if (spriteX < -7 || spriteX >= SCREEN_WIDTH)
            {
                continue;
            }
            else if (spriteY > scanLine || (spriteY + spriteHeight) <= scanLine)
            {
                continue;
            }

            int line = yFlip ? spriteHeight - (scanLine - spriteY) * 2 : (scanLine - spriteY) * 2;

            int tileAddress = 0x8000 + (tileLocation * 16) + line;
            uint8 data1 = memory->Read(tileAddress);
            uint8 data2 = memory->Read(tileAddress + 1);

            for (int pixelX = 0; pixelX < 8; pixelX++)
            {
                int posX = spriteX + pixelX;
                int colorBit = xFlip ? pixelX : 7 - pixelX;
                int colorNum = GetBitValue(data1, colorBit) | (GetBitValue(data2, colorBit) * 2);

                if (belowBG && frameBuffer[posX + scanLine * SCREEN_WIDTH] != Color::WHITE)
                {
                    continue;
                }

                if (colorNum == 0)
                    continue;

                uint8 palette = memory->Read(paletteNumber);
                Color color = GetColor(colorNum, palette);
                
                frameBuffer[posX + scanLine * SCREEN_WIDTH] = color;
            }
        }
    }
}

Color Video::GetColor(int colorNum, uint8 palette)
{
    Color colors[4] = 
    {
        Color::WHITE,
        Color(170, 170, 170, 255),
        Color(85, 85, 85, 255),
        Color::BLACK
    };

    int color = (palette >> (colorNum * 2)) & 3;

    return colors[color];
}

