#include "input.h"

sft_key sft_input_keys[sft_key_Count];
sft_key sft_input_clicks[sft_click_Count];
sft_key sft_input_clicks[sft_click_Count];

void sft_input_updateInput()
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
	_sft_input_updateInput();
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


bool sft_input_clickState(sft_key button)
{
	if (button >= sft_click_Count)
		return false;
	return sft_input_clicks[button] & 1;
}

bool sft_input_clickReleased(sft_key button)
{
	if (button >= sft_click_Count)
		return false;
	return !sft_input_clickState(button) && sft_input_clickLast(button);
}

bool sft_input_clickPressed(sft_key button)
{
	if (button >= sft_click_Count)
		return false;
	return sft_input_clickState(button) && !sft_input_clickLast(button);
}

bool sft_input_clickLast(sft_key button)
{
	if (button >= sft_click_Count)
		return false;
	return (sft_input_clicks[button] >> 1) & 1;
}
