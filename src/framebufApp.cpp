#include "framebufApp.h"

#include <format>

//----------------------------------------------------------------------------------------------

FramebufApp::FramebufApp(const char* windowTitle, int width, int height)
    : mFramebuf(width, height)
{
    int res = SDL_Init (SDL_INIT_VIDEO);
    if (res)
        throw std::format("SDL_Init failed with code {}: {}", res, SDL_GetError());

    mWindow = SDL_CreateWindow (windowTitle,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_ALLOW_HIGHDPI);
    if (!mWindow)
        throw std::format("SDL_CreateWindow failed: {}" , SDL_GetError());

    mRenderer = SDL_CreateRenderer (mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
        throw std::format("SDL_CreateRenderer failed: {}", SDL_GetError());

    mBackBuf = SDL_CreateTexture (
        mRenderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
        width, height);
    if (!mBackBuf)
        throw std::format("SDL_CreateTexture failed to create backbuf: {}", SDL_GetError());

    SDL_ShowWindow (mWindow);
}

//----------------------------------------------------------------------------------------------

FramebufApp::~FramebufApp()
{
    SDL_DestroyTexture (mBackBuf);
    SDL_DestroyRenderer (mRenderer);
    SDL_DestroyWindow (mWindow);
}

//----------------------------------------------------------------------------------------------

void FramebufApp::mainLoop()
{
    mFramebuf.rectStroke(100, 100, 400, 400, 0xffee9966);
    mFramebuf.rectStroke(16, 16, mFramebuf.width() - 16, mFramebuf.height() - 16, 0xffeeddaa);

    while (!mWantsQuit)
    {
        readInput();

        // TODO
        const float deltaTime = 1.f / 60.f;
        tick (deltaTime);

        present();
    }
}

//----------------------------------------------------------------------------------------------

void FramebufApp::readInput()
{
    SDL_Event event;
    while (SDL_PollEvent (&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mWantsQuit = true;
            break;

        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                mWantsQuit = true;
            break;

        default:
            break;
        }
    }
}

//----------------------------------------------------------------------------------------------

void FramebufApp::tick(float deltaTime)
{
    (void) deltaTime;
}

//----------------------------------------------------------------------------------------------

void FramebufApp::present()
{
    SDL_UpdateTexture (mBackBuf, nullptr, mFramebuf.data(), mFramebuf.stride());
    SDL_RenderCopy (mRenderer, mBackBuf, nullptr, nullptr);
    SDL_RenderPresent (mRenderer);
}

//----------------------------------------------------------------------------------------------

