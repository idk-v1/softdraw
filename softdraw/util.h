#pragma once
#include <stdint.h>

#define sft_min(a, b) ((a) < (b) ? (a) : (b))
#define sft_max(a, b) ((a) > (b) ? (a) : (b))
#define sft_clamp(val, min, max) sft_min(sft_max(val, min), max)

typedef struct
{
    uint32_t w;
    uint32_t h;
} sft_size;

typedef struct
{
    int32_t x;
    int32_t y;
} sft_point;

typedef struct
{
    int32_t x;
    int32_t y;
    uint32_t w;
    uint32_t h;
} sft_rect;