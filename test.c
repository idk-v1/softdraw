#include "softdraw/softdraw.h"
#include <stdlib.h>

int main()
{
	sft_init();

	sft_window* window = sft_window_open("test features", 800, 500, -1, -1, sft_flag_darkmode);
	if (!window)
		return 1;

	int c = 0;

	while (sft_window_update(window))
	{
		sft_input_update();

		char buf[10] = { 0 };
		_itoa_s(c++, buf, sizeof(buf), 10);
		sft_window_setTitle(window, buf);

		sft_sleep(10);
	}

	sft_shutdown();
	return 0;
}