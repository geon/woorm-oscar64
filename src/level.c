#include "level.h"
#include "path-controller.h"
#include <c64/joystick.h>
#include <c64/vic.h>

void levelLoad(const Level *level)
{
	oscar_expand_lzo((uint8_t *)0x2000, level->charset);
	oscar_expand_lzo(screenColors, level->colors);
	oscar_expand_lzo(screenChars, level->chars);
}

void levelSetMultiColors(const Level *level)
{
	vic.color_back1 = level->multiColor1;
	vic.color_back2 = level->multiColor2;
}

void levelStart(const Level *level, uint8_t numWorms)
{
	levelSetMultiColors(level);
	levelLoad(level);
}
