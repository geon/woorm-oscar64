#include "../generated/levels/levels.h"
#include "controller.h"
#include "coord.h"
#include "level.h"
#include "screen.h"
#include "worm.h"
#include "worms.h"
#include <c64/vic.h>
#include <oscar.h>
#include <stdint.h>

void titleScreen(void)
{
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

	extern const Level level_title_screen;

	uint8_t numWorms = 2;
	levelStart(&level_title_screen);

	PathController pathControllers[2];

	pathControllerInit(&pathControllers[0], pathA, sizeof(pathA));
	pathControllerInit(&pathControllers[1], pathB, sizeof(pathB));

	wormInit(
		&worms[0],
		wormColors[1],
		coordToPos(level_title_screen.playerStarts[0].position),
		level_title_screen.playerStarts[0].direction,
		wormCellDirectionsBuffers[0]);

	wormInit(
		&worms[1],
		wormColors[2],
		coordToPos(level_title_screen.playerStarts[1].position),
		level_title_screen.playerStarts[1].direction,
		wormCellDirectionsBuffers[1]);

	worms[0].controller = ControllerName_path;
	worms[1].controller = ControllerName_path;
	worms[0].pathController = &pathControllers[0];
	worms[1].pathController = &pathControllers[1];
	worms[0].speed = 64;
	worms[1].speed = 64;

	for (;;)
	{
		vic_waitFrame();

		for (uint8_t wormIndex = 0; wormIndex < numWorms; ++wormIndex)
		{
			wormStep(&worms[wormIndex]);
		}

		joy_poll(0);
		if (joyb[0])
		{
			break;
		}
	}
}
