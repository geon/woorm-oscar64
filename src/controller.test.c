#include "controller.h"
#include "coord.h"
#include "test/custom-asserts.h"
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

	beginTest("getCoordInFrontOfWorm");
	{
		assertCoord("Up", getCoordInFrontOfWorm(coordCreate(3, 7), Direction_up, 6), coordCreate(3, 1));
		assertCoord("Clipped By Screen", getCoordInFrontOfWorm(coordCreate(3, 1), Direction_up, 6), coordCreate(3, 0));
	}
	endTest();

	beginTest("getDirectionOfTarget");
	{
		assertByte("Up", getDirectionOfTarget(coordCreate(3, 3), coordCreate(3, 0)), Direction_up);
		assertByte("Right", getDirectionOfTarget(coordCreate(3, 3), coordCreate(7, 3)), Direction_right);
		assertByte("down", getDirectionOfTarget(coordCreate(3, 3), coordCreate(3, 7)), Direction_down);
		assertByte("Left", getDirectionOfTarget(coordCreate(3, 3), coordCreate(0, 3)), Direction_left);
	}
	endTest();

	// beginTest("controllerGetDirectionBlock");
	// {
	// 	wormInit(0, coordToPos(coordCreate(0, 0)), Direction_up, controllerAllGetDirection[ControllerName_up]);
	// 	wormInit(1, coordToPos(coordCreate(2, 0)), Direction_up, controllerAllGetDirection[ControllerName_up]);

	// 	{
	// 		Direction direction = controllerAllGetDirection[ControllerName_block](0);
	// 		assertByte("close", direction, Direction_up);
	// 	}
	// 	wormInit(1, coordToPos(coordCreate(7, 0)), Direction_up, controllerAllGetDirection[ControllerName_up]);
	// 	{
	// 		Direction direction = controllerAllGetDirection[ControllerName_block](0);
	// 		assertByte("far", direction, Direction_right);
	// 	}
	// }
	// endTest();
}
