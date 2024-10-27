#include "softdraw.h"
#include "window/win32_window.h"

#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define NOMINMAX
#include <Windows.h>

void sft_init()
{
	wc.hInstance = GetModuleHandleA(NULL);
	wc.lpszClassName = wcName;
	wc.lpfnWndProc = wndProc;
	wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
	RegisterClassA(&wc);
}

void sft_shutdown()
{
	UnregisterClassA(wcName, GetModuleHandleA(NULL));
}

void sft_sleep(uint32_t ms)
{
	Sleep(ms);
}
