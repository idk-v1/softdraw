#include "timer.h"

uint64_t sft_timer_nsDiff(uint64_t last)
{
    return sft_timer_now() - last;
}

bool sft_timer_msPassed(uint64_t* last, uint64_t val)
{
    uint64_t diff = sft_timer_nsDiff(*last);

    if (sft_toMILLISEC(diff) >= val)
    {
        *last = sft_timer_now();
        return true;
    }
    return false;
}

void sft_timer_msWait(uint64_t* last, uint64_t val)
{
    uint64_t diff = sft_timer_nsDiff(*last);

    sft_sleep(sft_toMILLISEC(diff));
    *last = sft_timer_now();
}

bool sft_timer_msDelta(uint64_t* last, uint64_t val)
{
    uint64_t diff = sft_timer_nsDiff(*last);

    if (sft_toMILLISEC(diff) >= val)
    {
        *last += sft_toNANOSEC(val);
        return true;
    }
    return false;
}