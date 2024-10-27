#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "../image/image.h"
#include "../timer/timer.h"
#include "../monitor/monitor.h"
#include "../util.h"

#define enumBit 1 << 
#define fncPtrEvent(name) void (*name)(struct sft_window* window)

typedef uint64_t sft_flags;
enum
{
	sft_flag_closed     = enumBit 0,

	sft_flag_hidden     = enumBit 1,
	sft_flag_noresize   = enumBit 2,
	sft_flag_borderless = enumBit 3,

	sft_flag_maximized  = enumBit 4,
	sft_flag_minimized  = enumBit 5,
	sft_flag_fullscreen = sft_flag_borderless | sft_flag_maximized,

	sft_flag_topmost    = enumBit 6,
	sft_flag_passthru   = enumBit 7,
	sft_flag_syshide    = enumBit 8,

	sft_flag_darkmode   = enumBit 9,

	sft_flag_default = 0,
};

typedef struct sft_window
{
	void* handle;

	char* title;
	uint64_t titleLen;

	sft_image* frameBuf;

	sft_flags flags;

	int32_t left;
	int32_t top;
	uint32_t width;
	uint32_t height;

	uint32_t fpsLimit;
	uint64_t _lastFrame;

	void* userData;

	fncPtrEvent(onMove);
	fncPtrEvent(onResize);
	fncPtrEvent(onClose);
} sft_window;

sft_window* sft_window_open(const char* title, uint32_t width, uint32_t height, int32_t left, int32_t top, sft_flags flags);

bool sft_window_update(sft_window* window);

void sft_window_display(sft_window* window);

void sft_window_close(sft_window* window);