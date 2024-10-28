#include "input.h"

#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define NOMINMAX
#include <Windows.h>

sft_point sft_input_mousePos(const sft_window* window)
{
    sft_point pt;
    GetCursorPos(&pt);

    if (window)
    {
        pt.x -= window->left;
        pt.y -= window->top;
    }

    return pt;
}