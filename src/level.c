#include "level.h"
#include "../generated/charset-static-size.h"
#include "path-controller.h"
#include <c64/joystick.h>
#include <c64/vic.h>

void levelLoad(const Level *level)
{
	// The dynamic per-level chars must be loaded after the statically allocated chars.
	oscar_expand_lzo((uint8_t *)(0x2000 + CHARSET_STATIC_SIZE * 8), level->charset);
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

void levelPlay(const Level *level, uint8_t numWorms)
{
	for (;;)
	{
		vic_waitFrame();

		for (uint8_t wormIndex = 0; wormIndex < numWorms; ++wormIndex)
		{
			vic.color_border = playerColors[wormIndex];
			wormStep(wormIndex);
			vic.color_border = VCOL_BLACK;
		}

		joy_poll(0);
		if (joyb[0])
		{
			break;
		}
	}
}
