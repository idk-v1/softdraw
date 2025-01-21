#include "image.h"

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
        image->pixels = malloc((uint64_t)width * height * sizeof(sft_color));
    }
    image->width = width;
    image->height = height;
}

void sft_image_fill(sft_image* image, sft_color color)
{
    if (!image || !image->pixels)
        return;

    for (uint64_t i = 0; i < (uint64_t)image->width * image->height; i++)
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

    if (destX < 0)
    {
        srcX -= destX;
        destX = 0;
    }
    if (destY < 0)
    {
        srcY -= destY;
        destY = 0;
    }
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

void sft_image_outlineRect(sft_image* dest, int32_t x, int32_t y, uint32_t w, uint32_t h, sft_color color)
{
    if (!dest || !dest->pixels)
        return;

    int32_t xo = x, yo = y;
    uint32_t wo = w, ho = h;

    _sft_image_adjustRect(&x, &y, &w, &h, dest->width, dest->height);

    if (w && h)
    {
        if (x == xo)
        {
            for (uint32_t i = y; i < y + h; i++)
                dest->pixels[x + i * dest->width] = color;
            if (w == wo)
                for (uint32_t i = y; i < y + h; i++)
                    dest->pixels[x + w - 1 + i * dest->width] = color;
        }
        else
            for (uint32_t i = y; i < y + h; i++)
                dest->pixels[x + w + i * dest->width] = color;

        if (y == yo)
        {
            for (uint32_t i = x; i < x + w; i++)
                dest->pixels[i + y * dest->width] = color;
            if (h == ho)
                for (uint32_t i = x; i < x + w; i++)
                    dest->pixels[i + (y + h - 1) * dest->width] = color;
        }
        else
            for (uint32_t i = x; i < x + w; i++)
                dest->pixels[i + (y + h) * dest->width] = color;
    }

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
    if ((uint64_t)*x + *w >= width)
        *w = width - sft_min(*x, width);
    if ((uint64_t)*y + *h >= height)
        *h = height - sft_min(*y, height);
}

void sft_image_drawText(sft_image* dest, const char* text, int32_t x, int32_t y, uint32_t fontSize, sft_color color)
{
    if (!dest || !text)
        return;

    uint32_t rows = 0;
    uint32_t cols = 0;

    for (uint32_t i = 0; text[i]; i++)
    {
        switch (text[i])
        {
        case '\n':
            rows++;
            cols = 0;
            break;

        case '\t':
            cols += 4 - cols % 4;
            break;
            
        default:

            sft_image_drawChar(dest, text[i], x + cols * fontSize * 8, y + rows * fontSize * 8, fontSize, color);
            cols++;
        }
    }
}

void sft_image_drawTextF(sft_image* dest, int32_t x, int32_t y, uint32_t fontSize, sft_color color, const char* fmt, ...)
{
    va_list args1, args2;
    va_start(args1, fmt);
    va_copy(args2, args1);

    uint64_t size = vsnprintf(NULL, 0, fmt, args1);

    char* buf = malloc(size + 1);
    if (buf)
        vsnprintf(buf, size + 1, fmt, args2);

    va_end(args1);
    va_end(args2);
    

    if (buf)
    {
        sft_image_drawText(dest, buf, x, y, fontSize, color);
        free(buf);
    }
}

void sft_image_drawChar(sft_image* dest, char ch, int32_t x, int32_t y, uint32_t fontSize, sft_color color)
{
    if (!dest || ch > 127)
        return;

    uint32_t width = fontSize * 8;
    uint32_t height = fontSize * 8;

    _sft_image_adjustRect(&x, &y, &width, &height, dest->width, dest->height);

    for (uint32_t yp = 0; yp < height; yp++)
        for (uint32_t xp = 0; xp < width; xp++)
        {
            uint32_t yr = yp / fontSize;
            uint32_t xr = xp / fontSize;
            if (sft_getBit(_sft_font[ch], 63 - (xr + yr * 8)))
                dest->pixels[(xp + x) + (yp + y) * dest->width] = color;
        }
}
