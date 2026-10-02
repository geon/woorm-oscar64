#include "controller.h"
#include "coord.h"
#include "screen.h"
#include "worm.h"
#include "worms.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

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

Coord getCoordOfWorm(Worm *worm)
{
	return coordFromPos(worm->headPosition);
}

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CLAMP(value, min, max) MIN(MAX(value, min), max)
Coord clipCoordToScreen(Coord coord)
{
	return (Coord){
		CLAMP(coord.x, 0, SCREEN_WIDTH),
		CLAMP(coord.y, 0, SCREEN_HEIGHT),
	};
}

Coord getCoordInFrontOfWorm(Coord wormCoord, Direction wormHeading, uint8_t distance)
{
	return clipCoordToScreen(coordAdd(
		wormCoord,
		coordScale(
			coordFromDirection(wormHeading),
			distance)));
}

Direction getDirectionOfTarget(Coord wormCoord, Coord targetCoord)
{
	Coord diff = coordSubtract(targetCoord, wormCoord);

	Direction direction;
	if (abs(diff.x) > abs(diff.y))
	{
		direction = (diff.x > 0) ? Direction_right : Direction_left;
	}
	else
	{
		direction = (diff.y > 0) ? Direction_down : Direction_up;
	}

	return direction;
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

Direction controllerGetDirectionAttack(Worm *worm)
{
	Worm *opponent = getOpponent(worm);
	if (!opponent)
	{
		return aimlessControllerGetDirection(nullptr, worm);
	}

	Coord opponentCoord = getCoordOfWorm(opponent);
	Coord wormCoord = getCoordOfWorm(worm);

	Direction wantedDirection = getDirectionOfTarget(
		wormCoord,
		opponentCoord);

	// When going in the opposite direction, first turn to the side.
	return turnIfOpposite(getHeadingOfWorm(worm), wantedDirection);
}

Direction controllerGetDirectionBlock(Worm *worm)
{
	Worm *opponent = getOpponent(worm);
	if (!opponent)
	{
		return aimlessControllerGetDirection(nullptr, worm);
	}

	Coord targetCoord = getCoordInFrontOfWorm(
		getCoordOfWorm(opponent),
		getHeadingOfWorm(opponent),
		8);

	Coord wormCoord = getCoordOfWorm(worm);
	Direction wantedDirection = getDirectionOfTarget(wormCoord, targetCoord);

	// When going in the opposite direction, first turn to the side.
	return turnIfOpposite(getHeadingOfWorm(worm), wantedDirection);
}
