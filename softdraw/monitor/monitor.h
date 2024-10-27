#pragma once
#include <stdint.h>

#include "../image/image.h"

/**
* \fn uint32_t sft_screenWidth()
* \brief Returns the primary monitor width
*/
uint32_t sft_screenWidth();

/**
* \fn uint32_t sft_screenHeight()
* \brief Returns the primary monitor height
*/
uint32_t sft_screenHeight();

/**
* \fn void sft_screenshot(sft_image* image)
* \brief Captures the entire screen
* \param image [out] Returns a screenshot
* 
* Uses a parameter rather than returning an image, because of reusing existing memory.
* This is probably only needed for screen recording, not a single screenshot.
* This was also tested on a 2012 laptop, but it was significantly faster
*/
void sft_screenshot(sft_image* image);