#include "image.h"

#include <malloc.h>

sft_image* sft_image_create(uint32_t width, uint32_t height)
{
	sft_image* image = malloc(sizeof(sft_image));
	if (image)
	{
		image->pixels = NULL;
		sft_image_resize(image, width, height);
		if (image->pixels)
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
	if (!image)
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
	if (!dest || !src)
		return;

	if (srcX < 0)
	{
		srcW += srcX;
		srcX = 0;
	}
	if (srcY < 0)
	{
		srcH += srcY;
		srcY = 0;
	}
	if (srcX + srcW >= src->width)
		srcW = src->width - srcX;
	if (srcY + srcH >= src->height)
		srcH = src->height - srcY;

	if (destX < 0)
	{
		srcW += destX;
		destX = 0;
	}
	if (destY < 0)
	{
		srcH += destY;
		destY = 0;
	}
	if (destX + srcW >= dest->width)
		srcW = dest->width - destX;
	if (destY + srcH >= dest->height)
		srcH = dest->height - destY;

	for (uint64_t y = 0; y < srcH; y++)
		for (uint64_t x = 0; x < srcW; x++)
			dest->pixels[(x + destX) + (y + destY) * dest->width] = 
			src->pixels[(x + srcX) + (y + srcY) * src->width];
}

void sft_image_drawRect(sft_image* dest, int32_t x, int32_t y, uint32_t w, uint32_t h, sft_color color)
{
	if (!dest)
		return;

	if (x < 0)
	{
		w += x;
		x = 0;
	}
	if (y < 0)
	{
		h += y;
		y = 0;
	}
	if (x + w >= dest->width)
		w = dest->width - x;
	if (y + h >= dest->height)
		h = dest->height - y;

	for (uint64_t yy = 0; yy < h; yy++)
		for (uint64_t xx = 0; xx < w; xx++)
			dest->pixels[(xx + x) + (yy + y) * dest->width] = color;
}
