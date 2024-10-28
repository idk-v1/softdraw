#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "window.h"

#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define NOMINMAX
#include <Windows.h>

/**
* \brief Windows specific internal message function
* \param hwnd Window handle
* \param msg Message type
* \param wp Message data
* \param lp Message data
*/
LRESULT WINAPI wndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

static WNDCLASSA wc;
static const char* wcName = "softdraw";

/**
* \brief Windows specific function to convert window flags to window styles
* \param flags input style
* \param style [out] Windows specific normal window style
* \param styleEx [out] Windows specific extended window style
*/
void flagsToWin32Style(sft_flags flags, uint32_t* style, uint32_t* styleEx);

#ifdef __cplusplus
}
#endif