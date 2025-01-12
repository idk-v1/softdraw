#include "input.h"

sft_key sft_input_keys[sft_key_Count] = { 0 };
sft_key sft_input_clicks[sft_click_Count] = { 0 };

sft_key sft_input_typed = 0;

char sft_input_typedChar()
{
	bool shift = sft_input_keyState(sft_key_Shift);
	bool caps = sft_input_keyState(sft_key_Capslock);

	// Lower / upper case
	if (sft_input_typed >= 'A' && sft_input_typed <= 'Z')
		return sft_input_typed + (32 * ((!shift) ^ caps));

	if (sft_input_typed >= sft_key_Num0 && sft_input_typed <= sft_key_Num9)
		return sft_input_typed - sft_key_Num0 + '0';

	switch (sft_input_typed)
	{
		// Numbers
	case '0': return shift ? ')' : '0';
	case '1': return shift ? '!' : '1';
	case '2': return shift ? '@' : '2';
	case '3': return shift ? '#' : '3';
	case '4': return shift ? '$' : '4';
	case '5': return shift ? '%' : '5';
	case '6': return shift ? '^' : '6';
	case '7': return shift ? '&' : '7';
	case '8': return shift ? '*' : '8';
	case '9': return shift ? '(' : '9';

		// Symbols
	case '`': return shift ? '~' : '`';
	case '-': return shift ? '_' : '-';
	case '=': return shift ? '+' : '=';
	case '[': return shift ? '{' : '[';
	case ']': return shift ? '}' : ']';
	case '\\':return shift ? '|' : '\\';
	case ';': return shift ? ':' : ';';
	case '\'':return shift ? '"' : '\'';
	case ',': return shift ? '<' : ',';
	case '.': return shift ? '>' : '.';
	case '/': return shift ? '?' : '/';

		// Numpad
	case sft_key_NumDiv: return '/';
	case sft_key_NumMult: return '*';
	case sft_key_NumSub: return '-';
	case sft_key_NumAdd: return '+';
	case sft_key_NumEnter: return '\n';
	case sft_key_NumPeriod: return '.';

		// No change
	case ' ':
	case '\t':
	case '\n':
		return sft_input_typed;
	}

	return 0;
}

void sft_input_update()
{
	for (sft_key i = 0; i < sft_key_Count; i++)
	{
		sft_input_keys[i] &= 1;
		sft_input_keys[i] <<= 1;
	}
	for (sft_key i = 0; i < sft_click_Count; i++)
	{
		sft_input_clicks[i] &= 1;
		sft_input_clicks[i] <<= 1;
	}
	_sft_input_update();

	for (sft_key i = sft_key_Control; i < sft_key_Count; i++)
	{
		if (sft_input_keyPressed(i))
			sft_input_typed = i;
		else if (sft_input_typed == i)
			sft_input_typed = 0;
	}
}

bool sft_input_keyState(sft_key key)
{
	if (key >= sft_key_Count)
		return false;
	return sft_input_keys[key] & 1;
}

bool sft_input_keyReleased(sft_key key)
{
	if (key >= sft_key_Count)
		return false;
	return !sft_input_keyState(key) && sft_input_keyLast(key);
}

bool sft_input_keyPressed(sft_key key)
{
	if (key >= sft_key_Count)
		return false;
	return sft_input_keyState(key) && !sft_input_keyLast(key);
}

bool sft_input_keyLast(sft_key key)
{
	if (key >= sft_key_Count)
		return false;
	return (sft_input_keys[key] >> 1) & 1;
}


bool sft_input_clickState(sft_click button)
{
	if (button >= sft_click_Count)
		return false;
	return sft_input_clicks[button] & 1;
}

bool sft_input_clickReleased(sft_click button)
{
	if (button >= sft_click_Count)
		return false;
	return !sft_input_clickState(button) && sft_input_clickLast(button);
}

bool sft_input_clickPressed(sft_click button)
{
	if (button >= sft_click_Count)
		return false;
	return sft_input_clickState(button) && !sft_input_clickLast(button);
}

bool sft_input_clickLast(sft_click button)
{
	if (button >= sft_click_Count)
		return false;
	return (sft_input_clicks[button] >> 1) & 1;
}
