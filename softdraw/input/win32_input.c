#include "input.h"

#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define NOMINMAX
#include <Windows.h>

sft_point sft_mouse_pos()
{
	sft_point pt;
	GetCursorPos(&pt);
	return pt;
}