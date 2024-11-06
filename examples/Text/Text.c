#include "softdraw/softdraw.h"
#include <malloc.h>

int main()
{
	sft_init();

	sft_window* window = sft_window_open("test features", 800, 500, -1, -1, sft_flag_darkmode);
	if (!window)
		return 1;

	uint64_t lastTime = sft_timer_now();

	int buffSize = 20;
	char* buff = malloc(buffSize + 1);
	if (!buff)
		return 1;
	int buffPos = 0;

	sft_window_fill(window, 0xFF000000);
	sft_window_display(window);

	while (sft_window_update(window))
	{
		sft_input_update();

		if (sft_input_typedChar())
		{
			if (buffPos < 20)
				buff[buffPos++] = sft_input_typedChar();
		}
		else if (sft_input_keyPressed(sft_key_BackSp))
		{
			if (buffPos > 0)
				buff[--buffPos] = 0;
		}

		sft_window_fill(window, 0xFF000000);
		sft_window_drawText(window, buff, 20, 20, 5, 0xFFFF0000);
		sft_window_display(window);

		sft_timer_msWait(&lastTime, 10);
	}

	free(buff);

	sft_shutdown();
	return 0;
}