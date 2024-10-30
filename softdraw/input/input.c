#include "input.h"

sft_key sft_input_keys[sft_key_Count];

void sft_input_updateKeys()
{
	for (sft_key i = 0; i < sft_key_Count; i++)
	{
		sft_input_keys[i] &= 1;
		sft_input_keys[i] <<= 1;
	}
	_sft_input_updateKeys();
}

bool sft_input_keyState(sft_key key)
{
	return sft_input_keys[key] & 1;
}

bool sft_input_keyReleased(sft_key key)
{
	return !sft_input_keyState(key) && sft_input_keyLast(key);
}

bool sft_input_keyPressed(sft_key key)
{
	return sft_input_keyState(key) && !sft_input_keyLast(key);
}

bool sft_input_keyLast(sft_key key)
{
	return (sft_input_keys[key] >> 1) & 1;
}
