#include <softdraw/softdraw.h>

int main()
{
	sft_init();

	sft_window* window = sft_window_open("Window", 800, 500, -1, -1, sft_flag_darkmode);
	if (!window)
		return 1;

	while (sft_window_update(window))
	{
	}
	sft_window_close(window);

	sft_shutdown();

	return 0;
}