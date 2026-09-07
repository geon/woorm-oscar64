#include "path-controller.h"
#include "screen.h"
#include "worm.h"
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
	PathController pathControllerA;
	PathController pathControllerB;
	pathControllerInit(&pathControllerA, pathA, sizeof(pathA));
	pathControllerInit(&pathControllerB, pathB, sizeof(pathB));

	wormInit(0, pathStartA, Direction_up, &pathControllerA, pathControllerGetDirection);
	wormInit(1, pathStartB, Direction_up, &pathControllerB, pathControllerGetDirection);

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
