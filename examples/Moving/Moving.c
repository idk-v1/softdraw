#include <softdraw/softdraw.h>

int main()
{
	sft_init();

	sft_window* window = sft_window_open("Moving", 800, 500, -1, -1, sft_flag_darkmode);
	if (!window)
		return 1;

	uint64_t lastTime = 0;

	window->fpsLimit = 60;

	sft_point point;
	point.x = window->width / 2;
	point.y = window->height / 2;

	int size = 50;
	int speed = 5;

	while (sft_window_update(window))
	{
		sft_input_update();

		if (sft_timer_msPassed(&lastTime, 1000 / 60))
		{
			point.x += speed * (sft_input_keyState('D') - sft_input_keyState('A'));
			point.y += speed * (sft_input_keyState('S') - sft_input_keyState('W'));
		}

		sft_window_fill(window, 0xFF000000);
		sft_window_drawRect(window, point.x, point.y, size, size, 0xFFFF0000);
		
		sft_window_display(window);

	}
	sft_window_close(window);

	sft_shutdown();

	return 0;
}