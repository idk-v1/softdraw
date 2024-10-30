#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

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
* \brief returns true once a specified time in milliseconds has passed
* \param last A pointer to the last time
* \param val The value to check for
*/
bool sft_timer_msPassed(uint64_t* last, uint64_t val);

/**
* \brief Pauses for milliseconds
* \param ms Milliseconds to pause for
*/
void sft_sleep(uint32_t ms);

#ifdef __cplusplus
}
#endif