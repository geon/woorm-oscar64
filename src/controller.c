#include "controller.h"
#include "worm.h"
#include "worms.h"
#include <assert.h>

Direction getHeadingOfWorm(Worm *worm)
{
	return circularBufferAtIndexReverse(&worm->cells, 0);
}

Worm *getOpponent(Worm *worm)
{
	Worm *opponent = worm->opponent;
	if (opponent->state != WormState_dead)
	{
		return opponent;
	}

	// Try all worms.
	for (uint8_t index = 0; index < NUM_WORMS; ++index)
	{
		opponent = &worms[index];
		if (opponent != worm && opponent->state != WormState_dead)
		{
			return opponent;
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

void pathControllerInit(PathController *pathController, Direction path[], uint8_t pathLength)
{
	assert(pathLength > 0);

	pathController->path = path;
	pathController->pathLength = pathLength;
	pathController->currentPathStep = 0;
}

Direction pathControllerGetDirection(PathController *pathController)
{
	Direction direction = pathController->path[pathController->currentPathStep];

	++(pathController->currentPathStep);
	if (pathController->currentPathStep >= pathController->pathLength)
	{
		pathController->currentPathStep = 0;
	}

	return direction;
}

Direction aimlessControllerGetDirection(Worm *worm)
{
	// Just keep moving forwards.
	return getHeadingOfWorm(worm);
}
