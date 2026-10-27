#include "controller.h"
#include "screen.h"
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

	uint16_t positionA = pathStartA;
	uint16_t positionB = pathStartB;

	for (;;)
	{
		vic_waitFrame();

		vic.color_border = wormColors[1];
		screenChars[positionA] = 0x00;
		positionA += getPositionOffsetForDirection(pathControllerGetDirection(&pathControllers[0]));
		screenChars[positionA] = 0x01;
		screenColors[positionA] = wormColors[1];
		vic.color_border = VCOL_BLACK;

		vic.color_border = wormColors[2];
		screenChars[positionB] = 0x00;
		positionB += getPositionOffsetForDirection(pathControllerGetDirection(&pathControllers[1]));
		screenChars[positionB] = 0x01;
		screenColors[positionB] = wormColors[2];
		vic.color_border = VCOL_BLACK;
	}
}
