#pragma once

#include "framebuf.h"
#include "mcore.h"

#include "SDL.h"

#include <vector>

//----------------------------------------------------------------------------------------------

class FramebufApp
{
public:
    FramebufApp(const char* windowTitle, int width, int height);
    ~FramebufApp();

    void mainLoop();

private:

    void readInput();
    void tick(float deltaTime);
    void present();

    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;
    SDL_Texture* mBackBuf = nullptr;

    Framebuf mFramebuf;

    bool mWantsQuit = false;
};

//----------------------------------------------------------------------------------------------

