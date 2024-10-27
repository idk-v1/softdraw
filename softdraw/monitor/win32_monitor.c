#include "monitor.h"

#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define NOMINMAX
#include <Windows.h>

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
