#include "input.h"

#define WIN32_LEAN_AND_MEAN
#define NO_STRICT
#define NOMINMAX
#include <Windows.h>

sft_point sft_input_mousePos(const sft_window* window)
{
    sft_point pt;
    GetCursorPos(&pt);

    if (window)
    {
        pt.x -= window->left;
        pt.y -= window->top;
    }

    return pt;
}

void _sft_input_updateKeys()
{
    // Toggles
    sft_input_keys[sft_key_Capslock] |= GetKeyState(VK_CAPITAL) & 1; // Return state instead of pressed
    sft_input_keys[sft_key_Numlock] |= GetKeyState(VK_NUMLOCK) & 1; // Return state instead of pressed
    
    // Letters
    for (uint32_t i = 0; i < 26; i++)
        sft_input_keys[sft_key_A + i] |= GetAsyncKeyState('A' + i) >> 15;

    // Numbers
    for (uint32_t i = 0; i < 10; i++)
        sft_input_keys[sft_key_0 + i] |= GetAsyncKeyState('0' + i) >> 15;

    // Numberpad
    for (uint32_t i = 0; i < 10; i++)
        sft_input_keys[sft_key_Num0 + i] |= GetAsyncKeyState(VK_NUMPAD0 + i) >> 15;
    
    sft_input_keys[sft_key_NumDiv] |= GetAsyncKeyState(VK_DIVIDE) >> 15;
    sft_input_keys[sft_key_NumMult] |= GetAsyncKeyState(VK_MULTIPLY) >> 15;
    sft_input_keys[sft_key_NumSub] |= GetAsyncKeyState(VK_SUBTRACT) >> 15;
    sft_input_keys[sft_key_NumAdd] |= GetAsyncKeyState(VK_ADD) >> 15;
    sft_input_keys[sft_key_NumEnter] |= GetAsyncKeyState(VK_RETURN) >> 15;
    sft_input_keys[sft_key_NumPeriod] |= GetAsyncKeyState(VK_DECIMAL) >> 15;

    // Function keys
    for (uint32_t i = 0; i < 12; i++)
        sft_input_keys[sft_key_Fn1 + i] |= GetAsyncKeyState(VK_F1 + i) >> 15;

    // Modifiers and control keys
    sft_input_keys[sft_key_Control] |= GetAsyncKeyState(VK_CONTROL) >> 15;
    sft_input_keys[sft_key_Shift] |= GetAsyncKeyState(VK_SHIFT) >> 15;
    sft_input_keys[sft_key_Alt] |= GetAsyncKeyState(VK_MENU) >> 15;
    sft_input_keys[sft_key_System] |= GetAsyncKeyState(VK_LWIN) | GetAsyncKeyState(VK_RWIN) >> 15;
    sft_input_keys[sft_key_Escape] |= GetAsyncKeyState(VK_ESCAPE) >> 15;
    sft_input_keys[sft_key_BackSp] |= GetAsyncKeyState(VK_BACK) >> 15;
    sft_input_keys[sft_key_Delete] |= GetAsyncKeyState(VK_DELETE) >> 15;
    sft_input_keys[sft_key_End] |= GetAsyncKeyState(VK_END) >> 15;
    sft_input_keys[sft_key_Home] |= GetAsyncKeyState(VK_HOME) >> 15;
    sft_input_keys[sft_key_Insert] |= GetAsyncKeyState(VK_INSERT) >> 15;
    sft_input_keys[sft_key_PrintScr] |= GetAsyncKeyState(VK_SNAPSHOT) >> 15;
    sft_input_keys[sft_key_PageUp] |= GetAsyncKeyState(VK_PRIOR) >> 15;
    sft_input_keys[sft_key_PageDown] |= GetAsyncKeyState(VK_NEXT) >> 15;
    sft_input_keys[sft_key_Up] |= GetAsyncKeyState(VK_UP) >> 15;
    sft_input_keys[sft_key_Down] |= GetAsyncKeyState(VK_DOWN) >> 15;
    sft_input_keys[sft_key_Left] |= GetAsyncKeyState(VK_LEFT) >> 15;
    sft_input_keys[sft_key_Right] |= GetAsyncKeyState(VK_RIGHT) >> 15;

    // Symbols
    sft_input_keys[sft_key_Space] |= GetAsyncKeyState(VK_SPACE) >> 15;
    sft_input_keys[sft_key_Apostr] |= GetAsyncKeyState(VK_OEM_7) >> 15;
    sft_input_keys[sft_key_Comma] |= GetAsyncKeyState(VK_OEM_COMMA) >> 15;
    sft_input_keys[sft_key_Minus] |= GetAsyncKeyState(VK_OEM_MINUS) >> 15;
    sft_input_keys[sft_key_Period] |= GetAsyncKeyState(VK_OEM_PERIOD) >> 15;
    sft_input_keys[sft_key_FSlash] |= GetAsyncKeyState(VK_OEM_2) >> 15;
    sft_input_keys[sft_key_Equal] |= GetAsyncKeyState(VK_OEM_PLUS) >> 15;
    sft_input_keys[sft_key_Semicolon] |= GetAsyncKeyState(VK_OEM_1) >> 15;
    sft_input_keys[sft_key_LBracket] |= GetAsyncKeyState(VK_OEM_4) >> 15;
    sft_input_keys[sft_key_BSlash] |= GetAsyncKeyState(VK_OEM_5) >> 15;
    sft_input_keys[sft_key_RBracket] |= GetAsyncKeyState(VK_OEM_6) >> 15;
    sft_input_keys[sft_key_Grave] |= GetAsyncKeyState(VK_OEM_3) >> 15;

}
