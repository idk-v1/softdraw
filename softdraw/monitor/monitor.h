#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "../image/image.h"

/**
* \brief Returns the primary monitor width
*/
uint32_t sft_screenWidth();

/**
* \brief Returns the primary monitor height
*/
uint32_t sft_screenHeight();

/**
* \brief Captures the entire screen
* \param image [out] Returns a screenshot
* 
* Uses a parameter rather than returning an image, because of reusing existing memory.
* This is probably only needed for screen recording, not a single screenshot.
* This was also tested on a 2012 laptop, but it was significantly faster
*/
void sft_screenshot(sft_image* image);

#ifdef __cplusplus
}
#endif