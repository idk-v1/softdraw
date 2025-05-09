#include "window.h"

#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")

LRESULT __stdcall wndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    sft_window* window = (sft_window*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
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
    *style = WS_OVERLAPPEDWINDOW;
    *styleEx = WS_EX_LAYERED;

    sft_setFlag(*style, WS_VISIBLE, 
        !(flags & sft_flag_hidden));

    sft_setFlag(*style, WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
        !(flags & sft_flag_borderless));
    sft_setFlag(*style, WS_POPUP,
        (flags & sft_flag_borderless));

    sft_setFlag(*style, WS_THICKFRAME | WS_MAXIMIZEBOX,
        !(flags & sft_flag_noresize));

    sft_setFlag(*style, WS_MAXIMIZE,
        (flags & sft_flag_maximized));

    sft_setFlag(*style, WS_MINIMIZE,
        (flags & sft_flag_minimized));

    sft_setFlag(*styleEx, WS_EX_TOPMOST,
        (flags & sft_flag_topmost));

    sft_setFlag(*styleEx, WS_EX_TRANSPARENT,
        (flags & sft_flag_passthru));

    sft_setFlag(*styleEx, WS_EX_TOOLWINDOW,
        (flags & sft_flag_syshide));
}

bool _sft_window_open(sft_window* window, const char* title, uint32_t width, uint32_t height, int32_t left, int32_t top, sft_flags flags)
{
    if (!window)
        return false;

    uint32_t style = 0;
    uint32_t styleEx = 0;

    flagsToWin32Style(flags, &style, &styleEx);

    window->handle = CreateWindowExA(
        styleEx, "softdraw", window->title, style,
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
        SetWindowLongPtrA(window->handle, GWLP_USERDATA, (LONG_PTR)window);

        // Fix for borderless windows taking up the full screen
        sft_window_setSize(window, width, height);

        return true;
    }
    return false;
}

void _sft_window_update(sft_window* window)
{
    if (!window)
        return;

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

void _sft_window_setTitle(sft_window* window)
{
    if (!window)
        return;

    SetWindowTextA(window->handle, window->title);
}

void _sft_window_setSize(sft_window* window, uint64_t width, uint64_t height)
{
    if (window)
        SetWindowPos(window->handle, NULL, 0, 0, width, height,
            SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);
}

void _sft_window_setPos(sft_window* window, uint64_t left, uint64_t top)
{
    if (window)
        SetWindowPos(window->handle, NULL, left, top, 0, 0,
            SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
}

void _sft_window_setTopmost(sft_window* window, bool value)
{
    if (window)
        SetWindowPos(window->handle, (value ? HWND_TOPMOST : HWND_NOTOPMOST), 0, 0, 0, 0,
            SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
}

void _sft_window_focus(sft_window* window)
{
    if (window)
        SetForegroundWindow(window->handle);
}

void _sft_window_setVisible(sft_window* window, bool value)
{
    if (window)
        SetWindowPos(window->handle, NULL, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | (value ? SWP_SHOWWINDOW : SWP_HIDEWINDOW));
}

void _sft_window_close(sft_window* window)
{
    if (!window)
        return;

    DestroyWindow(window->handle);
}

void sft_window_setFlag(sft_window* window, sft_flags enable, sft_flags disable)
{
    if (!window)
        return;

    uint32_t style = (uint32_t)GetWindowLongPtrA(window->handle, GWL_STYLE);
    uint32_t styleEx = (uint32_t)GetWindowLongPtrA(window->handle, GWL_EXSTYLE);

    sft_setFlag(window->flags, enable, true);
    sft_setFlag(window->flags, disable, false);

    flagsToWin32Style(window->flags, &style, &styleEx);

    SetWindowLongPtrA(window->handle, GWL_STYLE, style);
    SetWindowLongPtrA(window->handle, GWL_EXSTYLE, styleEx);

    // Dark titlebar
    DWORD value = window->flags & sft_flag_darkmode;
    DwmSetWindowAttribute(window->handle,
        DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));

    // Left and top needed for fullscreen and stuff
    SetWindowPos(window->handle, NULL, 
        window->left, window->top, window->width, window->height, 
        SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOACTIVATE);

    if (window->flags & sft_flag_topmost)
        SetWindowPos(window->handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    else
        SetWindowPos(window->handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

    if (window->flags & sft_flag_hidden)
        ShowWindow(window->handle, SW_HIDE);

    InvalidateRect(window->handle, NULL, true);
}

void sft_window_init()
{
    WNDCLASSA wc;
    memset(&wc, 0, sizeof(wc));
    wc.hInstance = GetModuleHandleA(NULL);
    wc.lpszClassName = "softdraw";
    wc.lpfnWndProc = wndProc;
    wc.hCursor = LoadCursorA(NULL, MAKEINTRESOURCEA(32512));
    RegisterClassA(&wc);

    SetProcessDPIAware();
}

void sft_window_shutdown()
{
    UnregisterClassA("softdraw", GetModuleHandleA(NULL));
}

uint32_t sft_screenWidth()
{
    return GetSystemMetrics(SM_CXSCREEN);
}

uint32_t sft_screenHeight()
{
    return GetSystemMetrics(SM_CYSCREEN);
}

void sft_screenshot(sft_image* image)
{
    if (!image)
        return;

    sft_image_resize(image, sft_screenWidth(), sft_screenHeight());

    BITMAPINFOHEADER bmi = { 0 };
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = sizeof(sft_color) * 8;
    bmi.biWidth = image->width;
    bmi.biHeight = 0 - image->height;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;

    HDC hScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen,
        image->width, image->height);
    HGDIOBJ hOld = SelectObject(hdcMem, hBitmap);

    BitBlt(hdcMem, 0, 0, image->width, image->height,
        hScreen, 0, 0, SRCCOPY);
    SelectObject(hdcMem, hOld);

    GetDIBits(hdcMem, hBitmap, 0, image->height, image->pixels, &bmi,
        DIB_RGB_COLORS);

    ReleaseDC(GetDesktopWindow(), hScreen);
    DeleteDC(hdcMem);
    if (hBitmap)
        DeleteObject(hBitmap);

    return image;
}
