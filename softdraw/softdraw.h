#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "window/window.h"
#include "image/image.h"
#include "input/input.h"
#include "timer/timer.h"
#include "monitor/monitor.h"
#include "util.h"

	void sft_init();

	void sft_shutdown();

	void sft_sleep(uint32_t ms);

#ifdef __cplusplus
}
#endif