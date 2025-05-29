#include <softdraw/softdraw.h>

int main()
{
	sft_init();

	sft_window* window = sft_window_open("Window", 500, 500, -1, -1, sft_flag_darkmode);
	if (!window)
		return 1;

	int size = 25;

	while (sft_window_update(window))
	{
		sft_window_fill(window, 0xFF000000);

		for (int x = 0; x < window->width; x += size * 2)
			for (int y = 0; y < window->height; y += size * 2)
				sft_window_drawRect(window, x, y, size, size, 0xFFFF0000);

		sft_window_display(window);
	}
	sft_window_close(window);

	sft_shutdown();

	return 0;
}