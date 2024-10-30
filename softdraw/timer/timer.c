#include "timer.h"

uint64_t sft_timer_diff(uint64_t last)
{
    return sft_timer_now() - last;
}

bool sft_timer_msPassed(uint64_t* last, uint64_t val)
{
    uint64_t diff = sft_timer_diff(*last);

    if (diff / 1'000 >= val)
    {
        *last = sft_timer_now();
        return true;
    }
    return false;
}
