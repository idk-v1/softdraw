#include "window.h"
#include "win32_window.h"

#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")

LRESULT __stdcall wndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    sft_window* window = GetWindowLongPtrA(hwnd, GWLP_USERDATA);
    if (!window)
        return DefWindowProcA(hwnd, msg, wp, lp);

    switch (msg)
    {
    case WM_CLOSE:
        if (window->onClose)
            window->onClose(window);
        else
            sft_window_defOnClose(window);
        return 0;

    case WM_SIZE:
        if (window->onResize)
            window->onResize(window, LOWORD(lp), HIWORD(lp));
        else
            sft_window_defOnResize(window, LOWORD(lp), HIWORD(lp));
        return 0;

    case WM_MOVE:
        if (window->onMove)
            window->onMove(window, LOWORD(lp), HIWORD(lp));
        else
            sft_window_defOnMove(window, LOWORD(lp), HIWORD(lp));
        return 0;

    default:
        return DefWindowProcA(hwnd, msg, wp, lp);
    }
}

void flagsToWin32Style(sft_flags flags, uint32_t* style, uint32_t* styleEx)
{
    *style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
    *styleEx = WS_EX_LAYERED;

    if (flags & sft_flag_hidden)
        *style ^= WS_VISIBLE;

    if (flags & sft_flag_noresize)
        *style ^= WS_THICKFRAME | WS_MAXIMIZEBOX;

    if (flags & sft_flag_borderless)
    {
        *style ^= WS_CAPTION | WS_SYSMENU | WS_THICKFRAME;
        *style |= WS_POPUP;
    }

    if (flags & sft_flag_maximized)
        *style |= WS_MAXIMIZE;

    if (flags & sft_flag_minimized)
        *style |= WS_MINIMIZE;

    if (flags & sft_flag_topmost)
        *styleEx |= WS_EX_TOPMOST;

    if (flags & sft_flag_passthru)
        *styleEx |= WS_EX_TRANSPARENT;

    if (flags & sft_flag_syshide)
        *styleEx |= WS_EX_TOOLWINDOW;
}

bool _sft_window_open(sft_window* window, const char* title, uint32_t width, uint32_t height, int32_t left, int32_t top, sft_flags flags)
{
    if (!window)
        return false;

    uint32_t style = 0;
    uint32_t styleEx = 0;

    flagsToWin32Style(flags, &style, &styleEx);

    window->handle = CreateWindowExA(
        styleEx, wcName, window->title, style,
        window->left, window->top, window->width, window->height,
        NULL, NULL, GetModuleHandleA(NULL), NULL);

    if (window->handle)
    {
        // Dark titlebar
        DWORD value = window->flags & sft_flag_darkmode;
        DwmSetWindowAttribute(window->handle,
            DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));

        // Transparent framebuffer
        BOOL opaque;
        DWORD color;
        HRGN region = CreateRectRgn(0, 0, -1, -1);
        DWM_BLURBEHIND bb;

        DwmGetColorizationColor(&color, &opaque);
        memset(&bb, 0, sizeof(bb));
        bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        bb.hRgnBlur = region;
        bb.fEnable = true;

        DwmEnableBlurBehindWindow(window->handle, &bb);
        DeleteObject(region);

        // Window transparency
        SetLayeredWindowAttributes(window->handle,
            0, 255, LWA_ALPHA);

        // Give window procedure the window pointer
        SetWindowLongPtrA(window->handle, GWLP_USERDATA, window);

        return true;
    }
    return false;
}

void _sft_window_update(sft_window* window)
{
    if (!window)
        return false;

    MSG msg;
    while (PeekMessageA(&msg, window->handle, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

void _sft_window_display(sft_window* window)
{
    if (!window)
        return;

    HDC hdc = GetDC(window->handle);

    BITMAPINFO info;
    memset(&info, 0, sizeof(info));
    info.bmiHeader.biBitCount = sizeof(sft_color) * 8;
    info.bmiHeader.biWidth = window->frameBuf->width;
    info.bmiHeader.biHeight = 0-window->frameBuf->height;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biSizeImage = 0;
    info.bmiHeader.biCompression = BI_RGB;

    StretchDIBits(hdc, 0, 0, window->width, window->height,
        0, 0, window->frameBuf->width, window->frameBuf->height,
        window->frameBuf->pixels, &info, DIB_RGB_COLORS, SRCCOPY);

    ReleaseDC(window->handle, hdc);
}

void _sft_window_close(sft_window* window)
{
    if (!window)
        return;

    DestroyWindow(window->handle);
}