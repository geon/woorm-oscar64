#include "worm.h"
#include "controller.h"
#include "screen.h"
#include "test/test.h"
#include "worms.h"
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

bool Tile_filled = true;
uint8_t wall = 0xff;

uint8_t wormIndex = 0;

void wormTest(void)
{
	Worm *worm = &worms[wormIndex];

	beginTest("A worm is drawn in 4 tiles on init.");
	{
		screenClear(0);

		wormInit(
			&worms[wormIndex],
			wormColors[wormIndex],
			coordToPos(coordCreate(1, 1)),
			Direction_up,
			wormCellDirectionsBuffers[wormIndex]);

		assertTrue("End", screenChars[coordToPos(coordCreate(1, 4))]);
		assertTrue("Before end", screenChars[coordToPos(coordCreate(1, 3))]);
		assertTrue("After head", screenChars[coordToPos(coordCreate(1, 2))]);
		assertTrue("Head", screenChars[coordToPos(coordCreate(1, 1))]);
	}
	endTest();

	beginTest("A worm is blocked by non-empty tiles.");
	{
		screenClear(0);

		wormInit(
			worm,
			wormColors[wormIndex],
			coordToPos(coordCreate(3, 3)),
			Direction_up,
			wormCellDirectionsBuffers[wormIndex]);

		// Block the path of the worm.
		screenChars[coordToPos(coordCreate(3, 2))] = wall;
		// Force a full step.
		worm->speed = 0xff;
		wormStep(worm);

		assertByte("The worm is blocked.", worm->state, WormState_blocked);
	}
	endTest();
}
