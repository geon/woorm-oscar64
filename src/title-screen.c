#include "path-controller.h"
#include "screen.h"
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

	uint16_t positionA = pathStartA;
	uint16_t positionB = pathStartB;

	for (;;)
	{
		vic_waitFrame();

		vic.color_border = playerColors[0];
		screenChars[positionA] = 0x00;
		positionA += getPositionOffsetForDirection(pathControllerGetDirection(&pathControllerA));
		screenChars[positionA] = 0x01;
		screenColors[positionA] = playerColors[0];
		vic.color_border = VCOL_BLACK;

		vic.color_border = playerColors[1];
		screenChars[positionB] = 0x00;
		positionB += getPositionOffsetForDirection(pathControllerGetDirection(&pathControllerB));
		screenChars[positionB] = 0x01;
		screenColors[positionB] = playerColors[1];
		vic.color_border = VCOL_BLACK;
	}
}
