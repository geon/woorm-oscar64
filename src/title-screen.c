#include "controller.h"
#include "screen.h"
#include "worm.h"
#include "worms.h"
#include <c64/vic.h>
#include <stdint.h>

void titleScreen(void)
{
	uint16_t pathStartA = 40 * 10 + 10;
	uint16_t pathStartB = 40 * 10 + 40 - 1 - 10;

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

	PathController pathControllers[2];

	pathControllerInit(&pathControllers[0], pathA, sizeof(pathA));
	pathControllerInit(&pathControllers[1], pathB, sizeof(pathB));

	wormInit(
		&worms[0],
		wormColors[1],
		pathStartA,
		Direction_up,
		wormCellDirectionsBuffers[0]);

	wormInit(
		&worms[1],
		wormColors[2],
		pathStartB,
		Direction_up,
		wormCellDirectionsBuffers[1]);

	// TODO: Add method for this.
	worms[0].controller = ControllerName_path;
	worms[1].controller = ControllerName_path;
	worms[0].pathController = &pathControllers[0];
	worms[1].pathController = &pathControllers[1];

	for (;;)
	{
		vic_waitFrame();

		wormStep(&worms[0]);
		wormStep(&worms[1]);
	}
}
