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

    /**
    * \fn sft_init()
    * \brief Setting up globals and OS specific functions
    */
    void sft_init();

    /**
    * \fn sft_shutdown()
    * \brief Cleaning up globals and OS specific functions
    */
    void sft_shutdown();

#ifdef __cplusplus
}
#endif