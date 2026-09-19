#include "../generated/levels/levels.h"
#include "coord.h"
#include "level.h"
#include "path-controller.h"
#include "screen.h"
#include "worm.h"
#include <c64/vic.h>
#include <oscar.h>
#include <stdint.h>

Direction pathA[] = {
	Direction_right,
	Direction_right,
	Direction_down,
	Direction_down,
	Direction_left,
	Direction_left,
	Direction_up,
	Direction_up,
};
Direction pathB[] = {
	Direction_right,
	Direction_right,
	Direction_down,
	Direction_down,
	Direction_down,
	Direction_left,
	Direction_left,
	Direction_up,
	Direction_up,
	Direction_up,
};

void titleScreen(void)
{
	extern const Level level_title_screen;

	uint8_t numWorms = 2;
	levelStart(&level_title_screen);

	pathControllerInit(0, pathA, sizeof(pathA));
	pathControllerInit(1, pathB, sizeof(pathB));

	wormInit(0, coordToPos(level_title_screen.playerStarts[0].position), level_title_screen.playerStarts[0].direction, pathControllerGetDirection);
	wormInit(1, coordToPos(level_title_screen.playerStarts[1].position), level_title_screen.playerStarts[1].direction, pathControllerGetDirection);
	wormSpeed[0] = 255;
	wormSpeed[1] = 64;

	for (;;)
	{
		vic_waitFrame();

		vic.color_border = playerColors[0];
		wormStep(0);
		vic.color_border = VCOL_BLACK;

		vic.color_border = playerColors[1];
		wormStep(1);
		vic.color_border = VCOL_BLACK;
	}
}
