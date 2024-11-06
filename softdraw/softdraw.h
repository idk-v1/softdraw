#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "window/window.h"
#include "image/image.h"
#include "input/input.h"
#include "timer/timer.h"
#include "util.h"

    /**
    * \brief Setting up globals and OS specific functions
    */
    void sft_init()
    {
        sft_window_init();
        sft_input_update();
    }

    /**
    * \brief Cleaning up globals and OS specific functions
    */
    void sft_shutdown()
    {
        sft_window_shutdown();
    }

#ifdef __cplusplus
}
#endif