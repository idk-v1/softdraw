#include "softdraw/softdraw.h"

int main()
{
	sft_init();

	sft_image* screen = sft_image_create(1, 1);
	sft_screenshot(screen);

	sft_window* window = sft_window_open("softdraw", 
		sft_screenSize().w, sft_screenSize().h, -1, -1, 
		sft_flag_fullscreen | sft_flag_topmost | sft_flag_passthru);
	window->fpsLimit = 30;

	while (sft_window_update(window))
	{
		sft_image_drawImage(window->frameBuf, screen, 
			0, 0, screen->width, screen->height, 0, 0);
		sft_image_drawRect(window->frameBuf, 
			sft_mouse_pos().x - 50, sft_mouse_pos().y - 50, 100, 100, 0x00000000);
		sft_window_display(window);
	}
	sft_window_close(window);
	sft_image_delete(screen);

	sft_shutdown();
	return 0;
}