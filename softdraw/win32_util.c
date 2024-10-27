#include "util.h"

#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define NOMINMAX
#include <Windows.h>

void sft_sleep(uint32_t ms)
{
    Sleep(ms);
}