#include "RetroGB.h"
#include "SDL.h"
#include "SDL_opengl.h"

GLuint texture;
Gameboy* gameboy;
int scale = 3;
int screenWidth = SCREEN_WIDTH * scale, screenHeight = SCREEN_HEIGHT * scale;
bool enableFiltering = false;
SDL_Window* window;
SDL_GLContext context;

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

void updateTexture(Color* framebuffer)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)framebuffer);

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

void updateScreen(Color* framebuffer)
{
    glClear(GL_COLOR_BUFFER_BIT);
    updateTexture(framebuffer);
    SDL_GL_SwapWindow(window);
}

void HandleInput(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_F)
        {
            enableFiltering = !enableFiltering;
        }
        else if (event.key.keysym.scancode == SDL_SCANCODE_R)
        {
            gameboy->ResetRom();
        }
    }
}

void ClearConsole()
{
#ifdef _WIN32
    system("cls");
#endif
}

int main(int argc, char** argv)
{
    gameboy = new Gameboy(&updateScreen);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 0;
    }

    window = SDL_CreateWindow("RetroGB",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight,
        SDL_WINDOW_OPENGL);

    if (!window)
    {
        return 0;
    }

    context = SDL_GL_CreateContext(window);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);

    init();

	LogLine("Drag and drop roms to run them.\n");

    bool quit = false;
    SDL_Event event;

    float fps = 59.73f;
    float interval = 1000 / fps;
    unsigned int lastTime = SDL_GetTicks();

    SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            HandleInput(event);

            if (event.type == SDL_QUIT)
            {
                quit = true;
            }

            if (event.type == SDL_DROPFILE)
            {
                ClearConsole();
                if (!gameboy->LoadRom(event.drop.file))
                {
                    gameboy->Reset(false);
                }

                SDL_SetWindowTitle(window, std::string("RetroGB: " + gameboy->GetCartridge()->GetTitle()).c_str());
            }
        }

        unsigned int currentTime = SDL_GetTicks();

        if ((lastTime + interval) < currentTime)
        {
            gameboy->Run();
            lastTime = currentTime;
        }

    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    glDeleteTextures(1, &texture);
    delete gameboy;

    return 0;
}