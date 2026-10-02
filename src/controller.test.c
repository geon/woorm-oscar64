#include "controller.h"
#include "test/test.h"
#include "worm.h"

void controllerTest()
{
	beginTest("Path Controller");
	{
		Direction path[] = {
			Direction_right,
			Direction_left,
		};
		pathControllerInit(0, path, sizeof(path));

		assertByte("Single step.", controllerAllGetDirection[ControllerName_path](0), Direction_right);
		assertByte("Multiple steps.", controllerAllGetDirection[ControllerName_path](0), Direction_left);
		assertByte("Loop steps.", controllerAllGetDirection[ControllerName_path](0), Direction_right);
	}
	endTest();

	beginTest("getOpponent");
	{
		for (int index = 0; index < NUM_WORMS; ++index)
		{
			wormInit(index, 0, Direction_up, controllerAllGetDirection[ControllerName_up]);
		}

		uint8_t playerIndex = 0;
		uint8_t firstOpponentIndex = getOpponent(playerIndex);

		assertTrue("Someone else is the opponent.", firstOpponentIndex != playerIndex);

		wormState[firstOpponentIndex] = WormState_dead;
		uint8_t secondOpponentIndex = getOpponent(playerIndex);

		assertTrue("The opponent changes when it dies.", secondOpponentIndex != firstOpponentIndex);
		assertTrue("To someone else.", secondOpponentIndex != playerIndex);
	}
	endTest();

	beginTest("turnIfOpposite");
	{
		assertByte("Up", turnIfOpposite(Direction_up, Direction_up), Direction_up);
		assertByte("Right", turnIfOpposite(Direction_up, Direction_right), Direction_right);
		assertTrue("down", turnIfOpposite(Direction_up, Direction_down) != Direction_up);
		assertByte("Left", turnIfOpposite(Direction_up, Direction_left), Direction_left);
	}
	endTest();
}
