#pragma once
#include <stdint.h>

#define sft_min(a, b) ((a) < (b) ? (a) : (b))
#define sft_max(a, b) ((a) > (b) ? (a) : (b))
#define sft_clamp(val, min, max) sft_min(sft_max(val, min), max)

inline uint32_t sft_u32Min(uint32_t a, uint32_t b)
{
	return a < b ? a : b;
}

inline uint32_t sft_u32Max(uint32_t a, uint32_t b)
{
	return a > b ? a : b;
}

inline uint32_t sft_u32Clamp(uint32_t val, uint32_t min, uint32_t max)
{
	return sft_u32Min(sft_u32Max(val, min), max);
}

inline int32_t sft_i32Min(int32_t a, int32_t b)
{
	return a < b ? a : b;
}

inline int32_t sft_i32Max(int32_t a, int32_t b)
{
	return a > b ? a : b;
}

inline int32_t sft_i32Clamp(int32_t val, int32_t min, int32_t max)
{
	return sft_i32Min(sft_i32Max(val, min), max);
}

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