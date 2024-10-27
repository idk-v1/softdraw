#pragma once
#include <stdint.h>
#include "../util.h"

typedef uint32_t sft_color;

typedef struct
{
    sft_color* pixels;
    uint32_t width;
    uint32_t height;
} sft_image;

/**
* \fn sft_image* sft_image_create(uint32_t width, uint32_t height)
* \brief Returns an image without filling with color
* \param width The width of the image
* \param height The height of the image
* \warning Must be freed by user. 
* \warning NULL returned if malloc failed
* \warning pixels array NULL if width * height is zero
*/
sft_image* sft_image_create(uint32_t width, uint32_t height);

/**
* \fn void sft_image_resize(sft_image* image, uint32_t width, uint32_t height)
* \brief Resizes image to new size
* \param image Target image to be resized
* \param width The new width of the image
* \param height The new height of the image
* \warning pixels array NULL if malloc failed
* \warning pixels array NULL if width * height is zero
* \warning Must be freed by user.
*/
void sft_image_resize(sft_image* image, uint32_t width, uint32_t height);


/**
* \fn void sft_image_fill(sft_image* image, sft_color color)
* \brief Fills the entire image with a specified color
* \param image Target image to be filled
* \param color Color to fill image with
*/
void sft_image_fill(sft_image* image, sft_color color);


/**
* \fn void sft_image_delete(sft_image* image)
* \brief Frees image memory
* \param image Target image to be freed
* \warning Image cannot be used
*/
void sft_image_delete(sft_image* image);

/**
* \fn void sft_image_drawImage(sft_image* dest, const sft_image* src, int32_t srcX, int32_t srcY, uint32_t srcW, uint32_t srcH, int32_t destX, int32_t destY)
* \brief Copies pixels from a source image to a destination image
* \param dest Destination image to draw to
* \param src Source image to get pixels from
* \param srcX Leftmost position to get pixels from source
* \param srcY Topmost position to get pixels from source
* \param srcW Width of copied image
* \param srcW Height of copied image
* \param destX Leftmost position to copy to on destination image
* \param destY Topmost position to copy to on destination image
*/
void sft_image_drawImage(sft_image* dest, const sft_image* src,
    int32_t srcX, int32_t srcY, uint32_t srcW, uint32_t srcH,
    int32_t destX, int32_t destY);

/**
* \fn void sft_image_drawRect(sft_image* dest, int32_t x, int32_t y, uint32_t w, uint32_t h, sft_color color)
* \brief Fills pixels in rectangle with a color
* \param dest Destination image to draw to
* \param x Leftmost position of rectangle
* \param y Topmost positionof rectangle
* \param w Width of rectangle
* \param h Height of rectangle
* \param color Color to fill rectangle with
*/
void sft_image_drawRect(sft_image* dest, 
    int32_t x, int32_t y, uint32_t w, uint32_t h, sft_color color);

/**
* \fn void _sft_image_adjustRect(int32_t* x, int32_t* y, uint32_t* w, uint32_t* h, uint64_t width, uint64_t height)
* \brief Internal function used by draws. Crops rectangles to fit in destination images
* \param x Leftmost position
* \param y Topmost position
* \param w Width
* \param h Height
* \param width Destination image width
* \param height Destination image height
*/
inline void _sft_image_adjustRect(int32_t* x, int32_t* y, uint32_t* w, uint32_t* h, 
    uint64_t width, uint64_t height);