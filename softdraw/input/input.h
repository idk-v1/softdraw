#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "../util.h"
#include "../window/window.h"
#include <stdint.h>

/**
* \brief Returns the mouse position relative to the window client area
* \param window [optional] The window client area relative to
*/
sft_point sft_input_mousePos(const sft_window* window);

typedef uint8_t sft_key;

enum
{
	sft_key_Null = '\0',
	sft_key_Capslock,
	sft_key_Numlock,

	sft_key_Control,
	sft_key_Shift,
	sft_key_Alt,
	sft_key_System,
	sft_key_Escape,
	sft_key_BackSp,
	sft_key_Delete,
	sft_key_End,
	sft_key_Home,
	sft_key_Insert,
	sft_key_PrintScr,
	sft_key_PageUp,
	sft_key_PageDown,
	sft_key_Up,
	sft_key_Down,
	sft_key_Left,
	sft_key_Right,

	sft_key_Fn1,
	sft_key_Fn2,
	sft_key_Fn3,
	sft_key_Fn4,
	sft_key_Fn5,
	sft_key_Fn6,
	sft_key_Fn7,
	sft_key_Fn8,
	sft_key_Fn9,
	sft_key_Fn10,
	sft_key_Fn11,
	sft_key_Fn12,

	sft_key_0 = '0',
	sft_key_1 = '1',
	sft_key_2 = '2',
	sft_key_3 = '3',
	sft_key_4 = '4',
	sft_key_5 = '5',
	sft_key_6 = '6',
	sft_key_7 = '7',
	sft_key_8 = '8',
	sft_key_9 = '9',

	sft_key_A = 'A',
	sft_key_B = 'B',
	sft_key_C = 'C',
	sft_key_D = 'D',
	sft_key_E = 'E',
	sft_key_F = 'F',
	sft_key_G = 'G',
	sft_key_H = 'H',
	sft_key_I = 'I',
	sft_key_J = 'J',
	sft_key_K = 'K',
	sft_key_L = 'L',
	sft_key_M = 'M',
	sft_key_N = 'N',
	sft_key_O = 'O',
	sft_key_P = 'P',
	sft_key_Q = 'Q',
	sft_key_R = 'R',
	sft_key_S = 'S',
	sft_key_T = 'T',
	sft_key_U = 'U',
	sft_key_V = 'V',
	sft_key_W = 'W',
	sft_key_X = 'X',
	sft_key_Y = 'Y',
	sft_key_Z = 'Z',

	sft_key_Space = ' ',
	sft_key_Apostr = '\'',
	sft_key_Comma = ',',
	sft_key_Minus = '-',
	sft_key_Period = '.',
	sft_key_FSlash = '/',
	sft_key_Equal = '=',
	sft_key_Semicolon = ';',
	sft_key_LBracket = '[',
	sft_key_BSlash = '\\',
	sft_key_RBracket = ']',
	sft_key_Grave = '`',

	sft_key_NumDiv,
	sft_key_NumMult,
	sft_key_NumSub,
	sft_key_NumAdd,
	sft_key_NumEnter,
	sft_key_NumPeriod,

	sft_key_Num0,
	sft_key_Num1,
	sft_key_Num2,
	sft_key_Num3,
	sft_key_Num4,
	sft_key_Num5,
	sft_key_Num6,
	sft_key_Num7,
	sft_key_Num8,
	sft_key_Num9,

	sft_key_Count, // Some spaces were skipped, but this is easier
};

/**
* \brief Internal keyboard state, perfectly fine to read this
*/
extern sft_key sft_input_keys[sft_key_Count];

/**
* \brief Gets the new state of the keyboard and replaces the last state
*/
void sft_input_updateKeys();
/**
* \brief Internal function to gets the new state of the keyboard
*/
void _sft_input_updateKeys();

/**
* \brief Gets the current state of the key
* \param key The key to get
*/
bool sft_input_keyState(sft_key key);
/**
* \brief Gets the last state of the key
* \param key The key to get
*/
bool sft_input_keyLast(sft_key key);
/**
* \brief Returns true if the key was just released
* \param key The key to get
*/
bool sft_input_keyReleased(sft_key key);
/**
* \brief Returns true if the key was just pressed
* \param key The key to get
*/
bool sft_input_keyPressed(sft_key key);

#ifdef __cplusplus
}
#endif