#include "screen.h"

void screenClear(uint8_t tile)
{
	for (uint16_t index = 0; index < SCREEN_SIZE; ++index)
	{
		screenChars[index] = tile;
	}
}
