#include "level.h"
#include "../generated/charset-static-size.h"
#include "worms.h"
#include <c64/joystick.h>
#include <c64/vic.h>

void levelLoad(const Level *level)
{
	// The dynamic per-level chars must be loaded after the statically allocated chars.
	oscar_expand_lzo((uint8_t *)0x2000 + CHARSET_STATIC_SIZE * 8, level->charset);
	oscar_expand_lzo(screenColors, level->colors);
	oscar_expand_lzo(screenChars, level->chars);
}

void levelSetMultiColors(const Level *level)
{
	vic.color_back1 = level->multiColor1;
	vic.color_back2 = level->multiColor2;
}

void levelStart(const Level *level)
{
	levelSetMultiColors(level);
	levelLoad(level);
}

Direction getPlayerInput(uint8_t playerIndex)
{
	if (playerIndex < 2)
	{
		joy_poll(playerIndex);
		if (joyx[playerIndex] == -1)
		{
			return Direction_left;
		}
		else if (joyx[playerIndex] == 1)
		{
			return Direction_right;
		}
		else if (joyy[playerIndex] == -1)
		{
			return Direction_up;
		}
		else if (joyy[playerIndex] == 1)
		{
			return Direction_down;
		}
	}

	return Direction_count;
}

void levelPlay(const Level *level, uint8_t numWorms)
{
	for (;;)
	{
		vic_waitFrame();

		for (uint8_t wormIndex = 0; wormIndex < numWorms; ++wormIndex)
		{
			Direction playerInput = getPlayerInput(wormIndex);
			if (playerInput < Direction_count)
			{
				// The player input can change the direction at any time, in order to feel responsive.
				wormSetNextDirection(&worms[wormIndex], playerInput);
			}
			wormStep(&worms[wormIndex]);
		}

		joy_poll(0);
		if (joyb[0])
		{
			break;
		}
	}
}
