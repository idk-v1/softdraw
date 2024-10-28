#include "image.h"

#include <malloc.h>

sft_image* sft_image_create(uint32_t width, uint32_t height)
{
    sft_image* image = malloc(sizeof(sft_image));
    if (image)
    {
        image->pixels = NULL;
        sft_image_resize(image, width, height);
        return image;
    }
    return NULL;
}

void sft_image_resize(sft_image* image, uint32_t width, uint32_t height)
{
    if (!image)
        return;

    if (image->width == width && image->height == height)
        return;

    if (width > 0 && height > 0)
    {
        if (image->pixels)
            free(image->pixels);
        image->pixels = malloc(width * height * sizeof(sft_color));
    }
    image->width = width;
    image->height = height;
}

void sft_image_fill(sft_image* image, sft_color color)
{
    if (!image || !image->pixels)
        return;

    for (uint64_t i = 0; i < image->width * image->height; i++)
        image->pixels[i] = color;
}

void sft_image_delete(sft_image* image)
{
    if (!image)
        return;

    if (image->pixels)
        free(image->pixels);
    free(image);
}

void sft_image_drawImage(sft_image* dest, const sft_image* src,
    int32_t srcX, int32_t srcY, uint32_t srcW, uint32_t srcH, 
    int32_t destX, int32_t destY) 
{
    if (!dest || !src || !dest->pixels || !src->pixels)
        return;

    _sft_image_adjustRect(&srcX, &srcY, &srcW, &srcH, src->width, src->height);
    _sft_image_adjustRect(&destX, &destY, &srcW, &srcH, dest->width, dest->height);

    for (uint64_t y = 0; y < srcH; y++)
        for (uint64_t x = 0; x < srcW; x++)
            dest->pixels[(x + destX) + (y + destY) * dest->width] = 
            src->pixels[(x + srcX) + (y + srcY) * src->width];
}

void sft_image_drawRect(sft_image* dest, int32_t x, int32_t y, uint32_t w, uint32_t h, sft_color color)
{
    if (!dest || !dest->pixels)
        return;

    _sft_image_adjustRect(&x, &y, &w, &h, dest->width, dest->height);

    for (uint64_t yy = 0; yy < h; yy++)
        for (uint64_t xx = 0; xx < w; xx++)
            dest->pixels[(xx + x) + (yy + y) * dest->width] = color;
}

void _sft_image_adjustRect(int32_t* x, int32_t* y, uint32_t* w, uint32_t* h, 
    uint64_t width, uint64_t height)
{
    if (*x < 0)
    {
        *w -= sft_min(sft_abs(*x), *w);
        *x = 0;
    }
    if (*y < 0)
    {
        *h -= sft_min(sft_abs(*y), *h);
        *y = 0;
    }
    if (*x + *w >= width)
        *w = width - sft_min(*x, width);
    if (*y + *h >= height)
        *h = height - sft_min(*y, height);
}
