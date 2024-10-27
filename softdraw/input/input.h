#pragma once
#include "../util.h"
#include "../window/window.h"
#include <stdint.h>

/**
* \fn sft_point sft_mouse_pos(sft_window* window)
* \brief Returns the mouse position relative to the window client area
* 
* \param window [optional] The window client area relative to
*/
sft_point sft_mouse_pos(const sft_window* window);