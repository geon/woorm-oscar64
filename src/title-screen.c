#include "../generated/levels/levels.h"
#include "controller.h"
#include "coord.h"
#include "level.h"
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

	wormInit(0, coordToPos(level_title_screen.playerStarts[0].position), level_title_screen.playerStarts[0].direction, controllerAllGetDirection[ControllerName_path]);
	wormInit(1, coordToPos(level_title_screen.playerStarts[1].position), level_title_screen.playerStarts[1].direction, controllerAllGetDirection[ControllerName_path]);
	wormSpeed[0] = 64;
	wormSpeed[1] = 64;

	for (;;)
	{
		vic_waitFrame();

		for (uint8_t wormIndex = 0; wormIndex < numWorms; ++wormIndex)
		{
			wormStep(wormIndex);
		}
	}
}
