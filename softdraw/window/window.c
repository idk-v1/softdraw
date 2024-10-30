#include "window.h"
#include <malloc.h>
#include <string.h>

void sft_window_defOnClose(sft_window* window)
{
    window->flags |= sft_flag_closed;
}

void sft_window_defOnResize(sft_window* window, uint32_t width, uint32_t height)
{
    window->width = width;
    window->height = height;
    sft_image_resize(window->frameBuf, window->width, window->height);
}

void sft_window_defOnMove(sft_window* window, int32_t left, int32_t top)
{
    window->left = left;
    window->top = top;
}

void sft_window_display(sft_window* window)
{
    if (!window)
        return;

    if (window->fpsLimit > 0)
    {
        if (sft_timer_msPassed(&window->_lastFrame, 1000 / window->fpsLimit))
            _sft_window_display(window);
    }
    else
        _sft_window_display(window);

}

sft_window* sft_window_open(const char* title, uint32_t width, uint32_t height, int32_t left, int32_t top, sft_flags flags)
{
    // No idea why you would want this, 
    // but it should do what it says it should do
    if (flags & sft_flag_closed)
        return NULL;

    sft_window* window = malloc(sizeof(sft_window));
    if (window)
    {
        memset(window, 0, sizeof(*window));

        window->flags = flags;

        window->titleLen = 0;
        window->titleLen = strlen(title);
        window->title = malloc(window->titleLen + 1ull);
        if (window->title)
            memcpy(window->title, title, window->titleLen + 1ull);

        if (window->flags & sft_flag_fullscreen)
        {
            window->width = sft_screenWidth();
            window->height = sft_screenHeight();
        }
        else
        {
            window->width = width;
            window->height = height;
        }

        if (left == -1 && top == -1)
        {
            window->left = (sft_screenWidth() - window->width) / 2;
            window->top = (sft_screenHeight() - window->height) / 2;
        }
        else
        {
            window->left = left;
            window->top = top;
        }

        if (_sft_window_open(window, title, width, height, left, top, flags))
        {
            window->frameBuf = sft_image_create(window->width, window->height);
        }
        else
        {
            free(window);
            window = NULL;
        }
    }

    return window;
}

bool sft_window_update(sft_window* window)
{
    if (!window)
        return false;

    _sft_window_update(window);
    return ~window->flags & sft_flag_closed;
}

void sft_window_close(sft_window* window)
{
    if (!window)
        return;

    _sft_window_close(window);

    free(window->title);
    sft_image_delete(window->frameBuf);
    free(window);
}

void sft_window_drawImage(sft_window* dest, const sft_image* src, int32_t srcX, int32_t srcY, uint32_t srcW, uint32_t srcH, int32_t destX, int32_t destY)
{
    if (!dest || !src)
        return;

    sft_image_drawImage(dest->frameBuf, src, 
        srcX, srcY, srcW, srcH, destX, destY);
}

void sft_window_drawRect(sft_window* dest, int32_t x, int32_t y, uint32_t w, uint32_t h, sft_color color)
{
    if (!dest)
        return;

    sft_image_drawRect(dest->frameBuf, x, y, w, h, color);
}

void sft_window_fill(sft_window* window, sft_color color)
{
    if (!window)
        return;

    sft_image_fill(window->frameBuf, color);
}
