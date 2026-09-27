#include "worm.h"
#include "controller.h"
#include "screen.h"
#include "test/test.h"
#include <stdint.h>

// For debugging.
void printScreen()
{
	for (uint16_t y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (uint16_t x = 0; x < SCREEN_WIDTH; ++x)
		{
			printf("%i ", screenChars[x + y * SCREEN_WIDTH]);
		}
		printf("\n");
	}
	printf("\n");
}

Direction upController(uint8_t wormImdex)
{
	return Direction_up;
}

const uint8_t playerColors[4] = {1, 2, 3, 4};

bool Tile_filled = true;
uint8_t wall = 0xff;

uint8_t wormIndex = 0;

void wormTest(void)
{
	beginTest("A worm is drawn in 4 tiles on init.");
	{
		screenClear(0);

		wormInit(wormIndex, coordToPos(coordCreate(1, 1)), Direction_up, controllerAllGetDirection[ControllerName_up]);

		assertTrue("End", screenChars[coordToPos(coordCreate(1, 4))]);
		assertTrue("Before end", screenChars[coordToPos(coordCreate(1, 3))]);
		assertTrue("After head", screenChars[coordToPos(coordCreate(1, 2))]);
		assertTrue("Head", screenChars[coordToPos(coordCreate(1, 1))]);
	}
	endTest();

	beginTest("A worm stops when blocked.");
	{
		screenClear(0);

		wormInit(wormIndex, coordToPos(coordCreate(3, 3)), Direction_up, upController);
		// Block the path of the worm.
		screenChars[coordToPos(coordCreate(3, 2))] = wall;
		// Force a full step.
		wormSpeed[wormIndex] = 0xff;
		wormStep(wormIndex);

		assertByte("The wall is still there.", screenChars[coordToPos(coordCreate(3, 2))], wall);
	}
	endTest();
}
