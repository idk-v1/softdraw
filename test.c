#include "softdraw/softdraw.h"
#include <stdlib.h>

int main()
{
	sft_init();

	sft_window* window = sft_window_open("test features", 800, 500, -1, -1, sft_flag_darkmode);
	if (!window)
		return 1;

	uint64_t timer = sft_timer_now();

	sft_point pos = { 100, 100 };
	int32_t speed = 5;

	while (sft_window_update(window))
	{
		sft_input_update();

		while (sft_timer_msDelta(&timer, 1000 / 30))
		{
			if (sft_input_keyState('W'))
				pos.y -= speed;
			if (sft_input_keyState('A'))
				pos.x -= speed;
			if (sft_input_keyState('S'))
				pos.y += speed;
			if (sft_input_keyState('D'))
				pos.x += speed;
		}

		sft_window_fill(window, 0xFF000000);

		sft_window_outlineRect(window, pos.x, pos.y, 100, 100, 0xFFFFFFFF);

		sft_window_display(window);
	}
	sft_window_close(window);

	sft_shutdown();
	return 0;
}