#include "controller.h"
#include "screen.h"
#include "worm.h"
#include "worms.h"
#include <c64/vic.h>
#include <stdint.h>

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

void titleScreen(void)
{
	pathControllerInit(0, pathA, sizeof(pathA));
	pathControllerInit(1, pathB, sizeof(pathB));

	wormInit(&worms[0], 0, playerColors[1], pathStartA, Direction_up, wormCellDirectionsBuffers[0]);
	wormInit(&worms[1], 1, playerColors[2], pathStartB, Direction_up, wormCellDirectionsBuffers[1]);
	worms[0].controllerGetDirection = controllerAllGetDirection[ControllerName_path];
	worms[1].controllerGetDirection = controllerAllGetDirection[ControllerName_path];
	worms[0].speed = 64;
	worms[1].speed = 64;

	for (;;)
	{
		vic_waitFrame();

		wormStep(&worms[0]);
		wormStep(&worms[1]);
	}
}
