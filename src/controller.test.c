#include "controller.h"
#include "coord.h"
#include "test/test.h"
#include "worm.h"
#include "worms.h"

void controllerTest()
{

	beginTest("Path Controller");
	{
		Direction path[] = {
			Direction_right,
			Direction_left,
		};
		PathController pathController;
		pathControllerInit(&pathController, path, sizeof(path));

		assertByte("Single step.", pathControllerGetDirection(&pathController), Direction_right);
		assertByte("Multiple steps.", pathControllerGetDirection(&pathController), Direction_left);
		assertByte("Loop steps.", pathControllerGetDirection(&pathController), Direction_right);
	}
	endTest();

	beginTest("getOpponent");
	{
		for (int wormIndex = 0; wormIndex < NUM_WORMS; ++wormIndex)
		{
			Worm *worm = &worms[wormIndex];
			wormInit(
				worm,
				wormColors[wormIndex],
				coordToPos(coordCreate(1, 1)),
				Direction_up,
				wormCellDirectionsBuffers[wormIndex]);
		}

		Worm *player = &worms[0];
		Worm *firstOpponent = getOpponent(player);

		assertTrue("Someone else is the opponent.", firstOpponent != player);

		firstOpponent->state = WormState_dead;
		Worm *secondOpponent = getOpponent(player);

		assertTrue("The opponent changes when it dies.", secondOpponent != firstOpponent);
		assertTrue("To someone else.", secondOpponent != player);
	}
	endTest();
}
