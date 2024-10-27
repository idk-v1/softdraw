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
    window->width = left;
    window->height = top;
}

void sft_window_display(sft_window* window)
{
    if (!window)
        return;

    if (window->fpsLimit > 0 &&
        sft_timer_diff(window->_lastFrame) < 1000000ull / window->fpsLimit)
        return;

    _sft_window_display(window);

    window->_lastFrame = sft_timer_now();
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