#include "Gameboy.h"
#include "Color.h"
#include "Definitions.h"
#include "Memory.h"
#include "Processor.h"
#include "SDL.h"
#include "SDL_opengl.h"

GLuint texture;
Gameboy* gameboy;
int scale = 2;
int screenWidth = SCREEN_WIDTH * scale, screenHeight = SCREEN_HEIGHT * scale;
bool enableFiltering = false;

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, screenWidth, screenHeight);

    glGenTextures(1, &texture);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void updateTexture()
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)gameboy->GetFrameBuffer());

    if (enableFiltering)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0);
    glVertex2d(0.0, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex2d(screenWidth, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex2d(screenWidth, screenHeight);
    glTexCoord2d(0.0, 1.0);
    glVertex2d(0.0, screenHeight);
    glEnd();
}

void run()
{
    gameboy->Run();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateTexture();
    SDL_GL_SwapBuffers();
}

void HandleInput(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
            gameboy->Step();
            break;
        }
    }
}

int main(int argc, char** argv)
{
    gameboy = new Gameboy();

    std::string fileName("E:/RetroGB/Roms/opus5.gb");

    if (!gameboy->LoadRom(fileName))
    {
        return 0;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 0;
    }
    if (SDL_SetVideoMode(screenWidth, screenHeight, 8, SDL_OPENGL) == NULL)
    {
        return 0;
    }

    init();

    SDL_WM_SetCaption("RetroGB", NULL);

    bool quit = false;
    SDL_Event event;

    float fps = 59.73f;
    float interval = 1000 / fps;
    unsigned int lastTime = SDL_GetTicks();

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            HandleInput(event);

            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        unsigned int currentTime = SDL_GetTicks();

        if ((lastTime + interval) < currentTime)
        {
            run();
            lastTime = currentTime;
        }

    }
    SDL_Quit();

    delete gameboy;

    return 0;
}