#include "softdraw/softdraw.h"

int main()
{
    sft_init();

    sft_sleep(3000);
    sft_image* screen = sft_image_create(0, 0);
    sft_screenshot(screen);

    sft_window* window = sft_window_open("softdraw", 800, 500, -1, -1, 
        sft_flag_darkmode | sft_flag_fullscreen | sft_flag_topmost | sft_flag_passthru);
    window->fpsLimit = 30;

    while (sft_window_update(window))
    {
        sft_image_drawImage(window->frameBuf, screen, 
            0, 0, screen->width, screen->height, 0, 0);

        sft_image_drawRect(window->frameBuf, 
            sft_input_mousePos(window).x - 50, 
            sft_input_mousePos(window).y - 50, 
            100, 100, 0);

        sft_window_display(window);
    }
    sft_window_close(window);
    sft_image_delete(screen);

    sft_shutdown();
    return 0;
}