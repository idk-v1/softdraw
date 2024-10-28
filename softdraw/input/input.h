#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "../util.h"
#include "../window/window.h"
#include <stdint.h>

/**
* \brief Returns the mouse position relative to the window client area
* \param window [optional] The window client area relative to
*/
sft_point sft_input_mousePos(const sft_window* window);

#ifdef __cplusplus
}
#endif