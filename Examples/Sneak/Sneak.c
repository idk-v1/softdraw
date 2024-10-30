#include <softdraw/softdraw.h>

/*
    This program hides what you are actually doing from the screen,
    except for a small window.

    This waits 3 seconds, then takes a screenshot.

    A fullscreen window that cannot be interacted with opens

    This draws the screenshot to the window, 
    then draws a transparent rectangle where the mouse is.

    Pressing escape closes the program
*/

int main()
{
    sft_init();

    sft_sleep(3000);
    sft_image* screen = sft_image_create(0, 0);
    sft_screenshot(screen);

    sft_window* window = sft_window_open("softdraw", 800, 500, -1, -1,
        sft_flag_darkmode | sft_flag_fullscreen | sft_flag_topmost | sft_flag_passthru);
    if (!window)
        return 1;
    window->fpsLimit = 30;

    while (sft_window_update(window))
    {
        sft_input_updateKeys();
        if (sft_input_keyReleased(sft_key_Escape))
        {
            sft_window_close(window);
            window = NULL;
        }
        if (sft_input_keyReleased(sft_key_Capslock))
            sft_window_setFlag(window, sft_flag_hidden, 0);
        if (sft_input_keyPressed(sft_key_Capslock))
            sft_window_setFlag(window, 0, sft_flag_hidden);

        sft_window_drawImage(window, screen,
            0, 0, screen->width, screen->height, 0, 0);

        sft_window_drawRect(window,
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