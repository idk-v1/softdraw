#include "timer.h"

#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define NOMINMAX
#include <Windows.h>
#include <profileapi.h>

uint64_t sft_timer_now()
{
    uint64_t time;
    uint64_t freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&time);

    return (1'000'000ull * time / freq);
}

void sft_sleep(uint32_t ms)
{
    Sleep(ms);
}