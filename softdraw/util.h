#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define sft_min(a, b) ((a) < (b) ? (a) : (b))
#define sft_max(a, b) ((a) > (b) ? (a) : (b))
#define sft_clamp(val, min, max) sft_min(sft_max(val, min), max)

#define sft_abs(val) (val < 0 ? -val : val)

#define sft_setFlag(flags, flag, val) if (val) (flags) |= (flag); else (flags) &= ~(flag);

#define sft_getBit(var, bit) (((var) >> (bit)) & 1)
#define sft_setBit(var, bit, state) if (state) (var) |= (1 << bit); else (state) &= ~(1 << bit);

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

#ifdef __cplusplus
}
#endif