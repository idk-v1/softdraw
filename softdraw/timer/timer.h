#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

// 1,000 Milliseconds = 1 Second
// 1,000,000 Nanoseconds = 1 Millisecond

#define sft_toMILLISEC(ns) (ns / 1'000'000ull) 
#define sft_toNANOSEC(ms)  (ms * 1'000'000ull) 

/**
* \brief Returns the tick count in nanoseconds (1,000,000 milliseconds)
*/
uint64_t sft_timer_now();

/**
* \brief Returns now - last
* \param last The last tick count
*/
uint64_t sft_timer_nsDiff(uint64_t last);

/**
* \brief returns true if a specified time in milliseconds has passed
* \param last A pointer to the last time (will be reset)
* \param val The value to check for in milliseconds
*/
bool sft_timer_msPassed(uint64_t* last, uint64_t val);

/**
* \brief Sleeps for val - diff milliseconds
* \param last A pointer to the last time (will be reset)
* \param val The target time to sleep for in milliseconds
*/
void sft_timer_msWait(uint64_t* last, uint64_t val);

/**
* \brief Used in delta time while loop
* \param last A pointer to the last time (will be reset)
* \param val The update time in milliseconds
*/
bool sft_timer_msDelta(uint64_t* last, uint64_t val);

/**
* \brief Pauses for milliseconds
* \param ms Milliseconds to pause for
*/
void sft_sleep(uint32_t ms);

#ifdef __cplusplus
}
#endif