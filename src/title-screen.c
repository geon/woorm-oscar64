#include "controller.h"
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
	pathControllerInit(0, pathA, sizeof(pathA));
	pathControllerInit(1, pathB, sizeof(pathB));

	wormInit(0, pathStartA, Direction_up, controllerAllGetDirection[ControllerName_path]);
	wormInit(1, pathStartB, Direction_up, controllerAllGetDirection[ControllerName_path]);

	for (;;)
	{
		vic_waitFrame();

		wormStep(0);
		wormStep(1);
	}
}
