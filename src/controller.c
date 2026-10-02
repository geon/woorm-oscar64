#include "controller.h"
#include "worm.h"
#include <assert.h>

Direction getHeadingOfWorm(uint8_t wormIndex)
{
	return wormCellDirectionsBuffer[wormIndex][circularBufferGetLastIndex(&wormCells[wormIndex])];
}

uint8_t getOpponent(uint8_t wormIndex)
{
	uint8_t opponentIndex = wormOpponentIndex[wormIndex];
	if (wormState[opponentIndex] != WormState_dead)
	{
		return opponentIndex;
	}

	// Try all worms.
	for (uint8_t index = 0; index < NUM_WORMS; ++index)
	{
		uint8_t opponentIndex = index;
		if (opponentIndex != wormIndex && wormState[opponentIndex] != WormState_dead)
		{
			return opponentIndex;
		}
	}

	return 0;
}

Direction turnIfOpposite(Direction currentDirection, Direction wantedDirection)
{
	// When going in the opposite direction, first turn to the side.
	if (currentDirection == (wantedDirection + 2) % Direction_count)
	{
		return (currentDirection + 1) % Direction_count;
	}
	return wantedDirection;
}

typedef struct PathController
{
	Direction *path;
	uint8_t pathLength;
	uint8_t currentPathStep;
} PathController;

PathController pathControllers[4];

void pathControllerInit(uint8_t wormIndex, Direction path[], uint8_t pathLength)
{
	assert(pathLength > 0);

	pathControllers[wormIndex].path = path;
	pathControllers[wormIndex].pathLength = pathLength;
	pathControllers[wormIndex].currentPathStep = 0;
}

Direction controllerGetDirectionPath(uint8_t wormIndex)
{
	Direction direction = pathControllers[wormIndex].path[pathControllers[wormIndex].currentPathStep];

	++(pathControllers[wormIndex].currentPathStep);
	if (pathControllers[wormIndex].currentPathStep >= pathControllers[wormIndex].pathLength)
	{
		pathControllers[wormIndex].currentPathStep = 0;
	}

	return direction;
}

Direction controllerGetDirectionUp(uint8_t wormIndex)
{
	return Direction_up;
}

Direction controllerGetDirectionAimless(uint8_t wormIndex)
{
	// Just keep moving forwards.
	return getHeadingOfWorm(wormIndex);
}

ControllerGetDirection controllerAllGetDirection[ControllerName_count] = {
	controllerGetDirectionPath,
	controllerGetDirectionUp,
	controllerGetDirectionAimless,
};
