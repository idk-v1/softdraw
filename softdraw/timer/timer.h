#pragma once
#include <stdint.h>

/**
* \fn uint64_t sft_timer_now()
* \brief Returns the tick count in nanoseconds (1,000,000 milliseconds)
*/
uint64_t sft_timer_now();

/**
* \fn uint64_t sft_timer_diff(uint64_t last)
* \brief Returns now - last
* \param last The last tick count
*/
uint64_t sft_timer_diff(uint64_t last);