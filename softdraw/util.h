#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define sft_min(a, b) ((a) < (b) ? (a) : (b))
#define sft_max(a, b) ((a) > (b) ? (a) : (b))
#define sft_clamp(val, min, max) sft_min(sft_max(val, min), max)

#define sft_abs(val) (val < 0 ? -val : val)

#define sft_setFlag(flags, flag, val) if (val) (flags) |= (flag); else (flags) &= ~(flag);

#define sft_getBit(var, bit) (((var) >> (bit)) & 1)
#define sft_setBit(var, bit, state) if (state) (var) |= (1 << bit); else (state) &= ~(1 << bit);


#define List(type, name) \
typedef struct name \
{ \
	uint64_t size; \
	uint64_t _max; \
	type* data; \
} name; \
static inline name name##_create() \
{ \
	name list = { .size = 0, ._max = 32, .data = malloc(sizeof(type) * list._max) }; \
	if (!list.data) \
		list._max = 0; \
	return list; \
} \
static inline void name##_push(name* list, type add) \
{ \
	if (list->size >= list->_max) \
	{ \
		list->_max *= 2; \
		void* ptr = realloc(list->data, sizeof(type) * list->_max); \
		if (!ptr) \
			basicList_free(list); \
		else \
		{ \
			list->data = (type*)ptr; \
			list->data[list->size++] = add; \
		} \
	} \
	else \
		list->data[list->size++] = add; \
} \
static inline void name##_pop(name* list) \
{ \
	if (list->size > 0) \
		list->size--; \
}

static inline void basicList_free(void* list)
{
	((uint64_t*)list)[0] = 0; // size
	((uint64_t*)list)[1] = 0; // _max
	if (((uint64_t*)list)[2]) // data
		free((void*)((uint64_t*)list)[2]);
	((uint64_t*)list)[2] = 0;
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

static bool sft_colPointRect(sft_rect rect, sft_point pos)
{
	return (pos.x >= rect.x && pos.y >= rect.y && pos.x <= rect.x + rect.w && pos.y <= rect.y + rect.h);
}

static bool sft_colRectRect(sft_rect rect1, sft_rect rect2)
{
	return rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y;
}

static char* sft_strf(const char* fmt, ...)
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
	return buf;
}

#ifdef __cplusplus
}
#endif