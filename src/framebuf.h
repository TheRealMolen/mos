#pragma once

#include "mcore.h"

#include <vector>

//----------------------------------------------------------------------------------------------

class Framebuf
{
    Framebuf() = delete;

public:
    Framebuf(u32 width, u32 height);

    u32 width() const { return mWidth; }
    u32 height() const { return mHeight; }

    const u32* data() const { return mPixels.data(); }
    u32 stride() const { return (mWidth * sizeof(decltype(*mPixels.data()))); }

    // drawing --------------------
    void clear(u32 col = 0);

    void hline(int x0, int y, int x1, u32 col);
    void vline(int x, int y0, int y1, u32 col);
    
    void rect(int x0, int y0, int x1, int y1, u32 col);
    void rectStroke(int x0, int y0, int x1, int y1, u32 col);

private:
    void hlineUnchecked(u32 x0, u32 y, u32 x1, u32 col);
    void vlineUnchecked(u32 x, u32 y0, u32 y1, u32 col);

private:

    u32 mWidth = 0;
    u32 mHeight = 0;

    std::vector<u32> mPixels;

};

//----------------------------------------------------------------------------------------------

