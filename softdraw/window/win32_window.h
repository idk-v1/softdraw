#pragma once
#include "window.h"

#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define NOMINMAX
#include <Windows.h>

LRESULT WINAPI wndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
static WNDCLASSA wc;
static const char* wcName = "softdraw";

void flagsToWin32Style(sft_flags flags, uint32_t* style, uint32_t* styleEx);