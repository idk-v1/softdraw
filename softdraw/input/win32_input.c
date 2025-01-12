#include "input.h"

#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define NOMINMAX
#include <Windows.h>

sft_point sft_input_mousePos(const sft_window* window)
{
    POINT point;
    GetCursorPos(&point);

    if (window)
        ScreenToClient(window->handle, &point);

    sft_point pt = { .x = point.x, .y = point.y };

    return pt;
}

void _sft_input_update()
{
    // Toggles
    sft_input_keys[sft_key_Capslock] |= (uint16_t)GetKeyState(VK_CAPITAL) & 1; // Return state instead of pressed
    sft_input_keys[sft_key_Numlock] |= (uint16_t)GetKeyState(VK_NUMLOCK) & 1; // Return state instead of pressed
    
    // Letters
    for (uint32_t i = 0; i < 26; i++)
        sft_input_keys[sft_key_A + i] |= (uint16_t)GetAsyncKeyState('A' + i) >> 15;

    // Numbers
    for (uint32_t i = 0; i < 10; i++)
        sft_input_keys[sft_key_0 + i] |= (uint16_t)GetAsyncKeyState('0' + i) >> 15;

    // Numberpad
    for (uint32_t i = 0; i < 10; i++)
        sft_input_keys[sft_key_Num0 + i] |= (uint16_t)GetAsyncKeyState(VK_NUMPAD0 + i) >> 15;
    
    sft_input_keys[sft_key_NumDiv] |= (uint16_t)GetAsyncKeyState(VK_DIVIDE) >> 15;
    sft_input_keys[sft_key_NumMult] |= (uint16_t)GetAsyncKeyState(VK_MULTIPLY) >> 15;
    sft_input_keys[sft_key_NumSub] |= (uint16_t)GetAsyncKeyState(VK_SUBTRACT) >> 15;
    sft_input_keys[sft_key_NumAdd] |= (uint16_t)GetAsyncKeyState(VK_ADD) >> 15;
    sft_input_keys[sft_key_NumEnter] |= (uint16_t)GetAsyncKeyState(VK_RETURN) >> 15;
    sft_input_keys[sft_key_NumPeriod] |= (uint16_t)GetAsyncKeyState(VK_DECIMAL) >> 15;

    // Function keys
    for (uint32_t i = 0; i < 12; i++)
        sft_input_keys[sft_key_Fn1 + i] |= (uint16_t)GetAsyncKeyState(VK_F1 + i) >> 15;

    // Modifiers and control keys
    sft_input_keys[sft_key_Control] |= (uint16_t)GetAsyncKeyState(VK_CONTROL) >> 15;
    sft_input_keys[sft_key_Shift] |= (uint16_t)GetAsyncKeyState(VK_SHIFT) >> 15;
    sft_input_keys[sft_key_Alt] |= (uint16_t)GetAsyncKeyState(VK_MENU) >> 15;
    sft_input_keys[sft_key_System] |= (uint16_t)GetAsyncKeyState(VK_LWIN) >> 15 | (uint16_t)GetAsyncKeyState(VK_RWIN) >> 15;
    sft_input_keys[sft_key_Escape] |= (uint16_t)GetAsyncKeyState(VK_ESCAPE) >> 15;
    sft_input_keys[sft_key_BackSp] |= (uint16_t)GetAsyncKeyState(VK_BACK) >> 15;
    sft_input_keys[sft_key_Tab] |= (uint16_t)GetAsyncKeyState(VK_TAB) >> 15;
    sft_input_keys[sft_key_Enter] |= (uint16_t)GetAsyncKeyState(VK_RETURN) >> 15;
    sft_input_keys[sft_key_Delete] |= (uint16_t)GetAsyncKeyState(VK_DELETE) >> 15;
    sft_input_keys[sft_key_End] |= (uint16_t)GetAsyncKeyState(VK_END) >> 15;
    sft_input_keys[sft_key_Home] |= (uint16_t)GetAsyncKeyState(VK_HOME) >> 15;
    sft_input_keys[sft_key_Insert] |= (uint16_t)GetAsyncKeyState(VK_INSERT) >> 15;
    sft_input_keys[sft_key_PrintScr] |= (uint16_t)GetAsyncKeyState(VK_SNAPSHOT) >> 15;
    sft_input_keys[sft_key_PageUp] |= (uint16_t)GetAsyncKeyState(VK_PRIOR) >> 15;
    sft_input_keys[sft_key_PageDown] |= (uint16_t)GetAsyncKeyState(VK_NEXT) >> 15;
    sft_input_keys[sft_key_Up] |= (uint16_t)GetAsyncKeyState(VK_UP) >> 15;
    sft_input_keys[sft_key_Down] |= (uint16_t)GetAsyncKeyState(VK_DOWN) >> 15;
    sft_input_keys[sft_key_Left] |= (uint16_t)GetAsyncKeyState(VK_LEFT) >> 15;
    sft_input_keys[sft_key_Right] |= (uint16_t)GetAsyncKeyState(VK_RIGHT) >> 15;

    // Symbols
    sft_input_keys[sft_key_Space] |= (uint16_t)GetAsyncKeyState(VK_SPACE) >> 15;
    sft_input_keys[sft_key_Apostr] |= (uint16_t)GetAsyncKeyState(VK_OEM_7) >> 15;
    sft_input_keys[sft_key_Comma] |= (uint16_t)GetAsyncKeyState(VK_OEM_COMMA) >> 15;
    sft_input_keys[sft_key_Minus] |= (uint16_t)GetAsyncKeyState(VK_OEM_MINUS) >> 15;
    sft_input_keys[sft_key_Period] |= (uint16_t)GetAsyncKeyState(VK_OEM_PERIOD) >> 15;
    sft_input_keys[sft_key_FSlash] |= (uint16_t)GetAsyncKeyState(VK_OEM_2) >> 15;
    sft_input_keys[sft_key_Equal] |= (uint16_t)GetAsyncKeyState(VK_OEM_PLUS) >> 15;
    sft_input_keys[sft_key_Semicolon] |= (uint16_t)GetAsyncKeyState(VK_OEM_1) >> 15;
    sft_input_keys[sft_key_LBracket] |= (uint16_t)GetAsyncKeyState(VK_OEM_4) >> 15;
    sft_input_keys[sft_key_BSlash] |= (uint16_t)GetAsyncKeyState(VK_OEM_5) >> 15;
    sft_input_keys[sft_key_RBracket] |= (uint16_t)GetAsyncKeyState(VK_OEM_6) >> 15;
    sft_input_keys[sft_key_Grave] |= (uint16_t)GetAsyncKeyState(VK_OEM_3) >> 15;

    // Mouse clicks
    sft_input_clicks[sft_click_Left] = (uint16_t)GetAsyncKeyState(VK_LBUTTON) >> 15;
    sft_input_clicks[sft_click_Right] = (uint16_t)GetAsyncKeyState(VK_RBUTTON) >> 15;
    sft_input_clicks[sft_click_Middle] = (uint16_t)GetAsyncKeyState(VK_MBUTTON) >> 15;
    sft_input_clicks[sft_click_Extra1] = (uint16_t)GetAsyncKeyState(VK_XBUTTON1) >> 15;
    sft_input_clicks[sft_click_Extra2] = (uint16_t)GetAsyncKeyState(VK_XBUTTON2) >> 15;
}
