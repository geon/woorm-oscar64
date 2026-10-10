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

	for (uint8_t wormIndex = 0; wormIndex < numWorms; ++wormIndex)
	{
		wormInit(
			&worms[wormIndex],
			wormColors[wormIndex + 1],
			coordToPos(level_title_screen.playerStarts[wormIndex].position),
			level_title_screen.playerStarts[wormIndex].direction,
			wormCellDirectionsBuffers[wormIndex]);

		worms[wormIndex].controller = ControllerName_path;
		worms[wormIndex].pathController = &pathControllers[wormIndex];
		worms[wormIndex].speed = 64;
	}

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
