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

sft_image* sft_image_create(uint32_t width, uint32_t height);

void sft_image_resize(sft_image* image, uint32_t width, uint32_t height);

void sft_image_fill(sft_image* image, sft_color color);

void sft_image_delete(sft_image* image);

void sft_image_drawImage(sft_image* dest, const sft_image* src,
	int32_t srcX, int32_t srcY, uint32_t srcW, uint32_t srcH,
	int32_t destX, int32_t destY);

void sft_image_drawRect(sft_image* dest, 
	int32_t x, int32_t y, uint32_t w, uint32_t h, sft_color color);