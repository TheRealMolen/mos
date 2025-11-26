#include "framebuf.h"

#include <algorithm>


//----------------------------------------------------------------------------------------------

Framebuf::Framebuf(u32 width, u32 height)
    : mWidth(width), mHeight(height)
    , mPixels(width * height, 0xff222020)
{
}

//----------------------------------------------------------------------------------------------

void Framebuf::clear(u32 col)
{
    std::fill(begin(mPixels), end(mPixels), col);
}

//----------------------------------------------------------------------------------------------

void Framebuf::hline(int x0, int y, int x1, u32 col)
{
    if (y < 0 || y >= int(mHeight))
        return;

    if (x1 < x0)
        std::swap(x0, x1);

    const u32 x0safe = clamp(x0, 0, int(mWidth) - 1);
    const u32 x1safe = clamp(x1, 0, int(mWidth) - 1);

    hlineUnchecked(x0safe, y, x1safe, col);
}

//----------------------------------------------------------------------------------------------

void Framebuf::hlineUnchecked(u32 x0, u32 y, u32 x1, u32 col)
{
    u32* first = mPixels.data() + (y * mWidth) + x0;
    u32* last = first + (x1 - x0);

    for (u32* p = first; p != last; ++p)
        *p = col;
}

//----------------------------------------------------------------------------------------------

void Framebuf::vline(int x, int y0, int y1, u32 col)
{
    if (x < 0 || x >= int(mWidth))
        return;

    if (y1 < y0)
        std::swap(y0, y1);

    const u32 y0safe = clamp(y0, 0, int(mHeight));
    const u32 y1safe = clamp(y1, 0, int(mHeight));

    vlineUnchecked(u32(x), y0safe, y1safe, col);
}

//----------------------------------------------------------------------------------------------

void Framebuf::vlineUnchecked(u32 x, u32 y0, u32 y1, u32 col)
{
    u32* first = mPixels.data() + (y0 * mWidth) + x;
    u32* last = first + ((y1 - y0) * mWidth);

    for (u32* p = first; p != last; p += mWidth)
        *p = col;
}

//----------------------------------------------------------------------------------------------

void Framebuf::rect(int x0, int y0, int x1, int y1, u32 col)
{
    if (x1 < x0)
        std::swap(x0, x1);
    if (y1 < y0)
        std::swap(y0, y1);

    const bool inBoundsX = x0 < int(mWidth) && x1 >= 0;
    const bool inBoundsY = y0 < int(mHeight) && y1 >= 0;
    if (!inBoundsX || !inBoundsY)
        return;

    const u32 x0safe = clamp(x0, 0, int(mWidth));
    const u32 x1safe = clamp(x1, 0, int(mWidth));
    const u32 y0safe = clamp(y0, 0, int(mHeight));
    const u32 y1safe = clamp(y1, 0, int(mHeight));

    for (u32 y = y0safe; y < y1safe; ++y)
        hlineUnchecked(x0safe, y, x1safe, col);
}

//----------------------------------------------------------------------------------------------

void Framebuf::rectStroke(int x0, int y0, int x1, int y1, u32 col)
{
    if (x1 < x0)
        std::swap(x0, x1);
    if (y1 < y0)
        std::swap(y0, y1);

    const bool inBoundsX = x0 < int(mWidth) && x1 >= 0;
    const bool inBoundsY = y0 < int(mHeight) && y1 >= 0;
    if (!inBoundsX || !inBoundsY)
        return;

    const u32 x0safe = clamp(x0, 0, int(mWidth));
    const u32 x1safe = clamp(x1, 0, int(mWidth));
    const u32 y0safe = clamp(y0, 0, int(mHeight));
    const u32 y1safe = clamp(y1, 0, int(mHeight));

    if (x0 >= 0)
        vlineUnchecked(x0, y0safe, y1safe, col);
    if (x1 <= int(mWidth)-1)
        vlineUnchecked(x1, y0safe, y1safe, col);

    if (y0 >= 0)
        hlineUnchecked(x0safe, y0, x1safe, col);
    if (y1 <= int(mHeight)-1)
        hlineUnchecked(x0safe, y1, x1safe, col);
}

//----------------------------------------------------------------------------------------------


