#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
* \brief Returns the tick count in nanoseconds (1,000,000 milliseconds)
*/
uint64_t sft_timer_now();

/**
* \brief Returns now - last
* \param last The last tick count
*/
uint64_t sft_timer_diff(uint64_t last);

/**
* \brief Pauses for milliseconds
* \param ms Milliseconds to pause for
*/
void sft_sleep(uint32_t ms);
#ifdef __cplusplus
}
#endif