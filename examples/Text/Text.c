#include "softdraw/softdraw.h"

int main()
{
	sft_init();

	sft_window* window = sft_window_open("test features", 800, 500, -1, -1, sft_flag_darkmode);
	if (!window)
		return 1;

	uint64_t lastTime = sft_timer_now();

	sft_window_fill(window, 0xFF000000);
	sft_window_display(window);

	while (sft_window_update(window))
	{
		sft_input_update();

		if (sft_input_typedChar())
		{
			sft_window_fill(window, 0xFF000000);
			sft_window_drawChar(window, sft_input_typedChar(), 20, 20, 5, 0xFFFF0000);
			sft_window_display(window);
		}

		sft_timer_msWait(&lastTime, 10);
	}

	sft_shutdown();
	return 0;
}