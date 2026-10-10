#include "worm.h"
#include "circular-buffer.h"
#include "direction.h"
#include "minmax.h"
#include "screen.h"
#include "worm-char.h"
#include "worms.h"
#include <c64/vic.h>

void wormPushDirection(Worm *worm, Direction direction)
{
	uint8_t segmentIndex;
	circularBufferPush(&worm->cells, &segmentIndex);
	worm->cellDirectionsBuffer[segmentIndex] = direction;
}

void wormInit(Worm *worm, uint8_t index, uint8_t color, uint16_t pos, Direction direction, Direction *cellDirectionsBuffer)
{
	worm->index = index;
	worm->color = color;
	worm->state = WormState_alive;
	worm->opponentIndex = (index + 1) % NUM_WORMS;
	worm->headPosition = pos;
	worm->tailPosition = pos - getPositionOffsetForDirection(direction) * 3;
	worm->controllerGetDirection = nullptr;
	worm->headMicroStep = 3;
	worm->tailMicroStep = 0;
	worm->speed = 16;
	circularBufferInit(&worm->cells);
	worm->cellDirectionsBuffer = cellDirectionsBuffer;

	wormPushDirection(worm, direction);
	wormPushDirection(worm, direction);
	wormPushDirection(worm, direction);
	wormPushDirection(worm, direction);
	wormPushDirection(worm, direction);

	wormDraw(worm);
}

void wormDraw(Worm *worm)
{
	const uint8_t color = worm->color + 8;
	uint16_t position = worm->tailPosition;

	screenChars[position] = 1;
	screenColors[position] = color;

	for (uint8_t iterator = worm->cells.begin; iterator < worm->cells.end - 2; ++iterator)
	{
		const Direction direction = worm->cellDirectionsBuffer[iterator];
		position += getPositionOffsetForDirection(direction);

		screenChars[position] = 1;
		screenColors[position] = color;
	}
}

bool isValidNextDirection(uint16_t nextPosition, Direction nextDirection)
{
	uint16_t nextNextPosition = nextPosition + getPositionOffsetForDirection(nextDirection);

	bool isOccupied = screenChars[nextNextPosition];

	return !isOccupied;
}

void wormFullStepHead(Worm *worm)
{
	Direction direction = worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 0)];
	uint16_t nextPosition = worm->headPosition + getPositionOffsetForDirection(direction);
	Direction nextDirection = worm->controllerGetDirection ? worm->controllerGetDirection(worm->index) : worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 0)];

	if (screenChars[nextPosition])
	{
		// Only move forward if the tile is not blocked.
		worm->state = WormState_blocked;
		return;
	}

	// Try the requested direction.
	if (!isValidNextDirection(nextPosition, nextDirection))
	{
		// Otherwise, try forward.
		nextDirection = direction;
		if (!isValidNextDirection(nextPosition, nextDirection))
		{
			// Or clockwise.
			nextDirection = (direction + 1) % Direction_count;
			if (!isValidNextDirection(nextPosition, nextDirection))
			{
				// Or counter clockwise.
				nextDirection = (direction + Direction_count - 1) % Direction_count;
				if (!isValidNextDirection(nextPosition, nextDirection))
				{
					// No valid next direction, so just move straight forward.
					nextDirection = direction;
				}
			}
		}
	}

	worm->headPosition = nextPosition;
	wormPushDirection(worm, nextDirection);
	screenColors[nextPosition] = worm->color + 8;
}

void wormFullStepTail(Worm *worm)
{
	uint8_t segmentIndex;
	circularBufferPop(&worm->cells, &segmentIndex);

	// Erase the worm from the tile it just left.
	screenChars[worm->tailPosition] = 0x00;

	worm->tailPosition += getPositionOffsetForDirection(worm->cellDirectionsBuffer[circularBufferAtIndex(&worm->cells, 0)]);
}

void wormMicroStepHead(Worm *worm, uint8_t numMicroSteps)
{
	uint8_t old = worm->headMicroStep;
	uint8_t new = old + numMicroSteps;
	bool overflowed = old > new;

	if (overflowed)
	{
		wormFullStepHead(worm);
	}

	if (worm->state == WormState_blocked)
	{
		// TODO: Also check all possible directions.
		// TODO: Refactor with isValidNextDirection
		// Check is still blocked.
		Direction direction = worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 0)];
		uint16_t nextPosition = worm->headPosition + getPositionOffsetForDirection(direction);
		if (screenChars[nextPosition])
		{
			return;
		}
		worm->state = WormState_alive;
	}

	worm->headMicroStep = new;

	// Head:
	// Zero index is the first visible tile, and index 3 is completely filled.
	// On overflow, the head immediately occupies 2 pixels in the new tile.

	// End:
	// Zero index is full, and index 3 is the last visible tile. Reverse of the head.
	// On overflow, the end tile used to only occupy 2 pixels, and is erased.

	// Draw the worm.
	screenChars[worm->headPosition] = charsetLookup[wormCharPackBits(
		WormCharPlacement_head,
		worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 1)],
		worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 0)],
		worm->headMicroStep)];

	screenChars[worm->headPosition - getPositionOffsetForDirection(worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 1)])] = charsetLookup[wormCharPackBits(
		WormCharPlacement_after_head,
		worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 2)],
		worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 1)],
		worm->headMicroStep)];
}

void wormMicroStepTail(Worm *worm, uint8_t numMicroSteps)
{
	uint8_t old = worm->tailMicroStep;
	uint8_t new = old + numMicroSteps;
	bool overflowed = old > new;

	if (overflowed)
	{
		wormFullStepTail(worm);
	}

	worm->tailMicroStep = new;

	// Draw the worm.
	screenChars[worm->tailPosition] = charsetLookup[wormCharPackBits(
		WormCharPlacement_end,
		worm->cellDirectionsBuffer[circularBufferAtIndex(&worm->cells, 0)],
		worm->cellDirectionsBuffer[circularBufferAtIndex(&worm->cells, 1)],
		worm->tailMicroStep)];

	screenChars[worm->tailPosition + getPositionOffsetForDirection(worm->cellDirectionsBuffer[circularBufferAtIndex(&worm->cells, 1)])] = charsetLookup[wormCharPackBits(
		WormCharPlacement_before_end,
		worm->cellDirectionsBuffer[circularBufferAtIndex(&worm->cells, 1)],
		worm->cellDirectionsBuffer[circularBufferAtIndex(&worm->cells, 2)],
		worm->tailMicroStep)];
}

void wormErase(Worm *worm)
{
	uint16_t position = worm->tailPosition;
	for (uint8_t iterator = worm->cells.begin + 1; iterator < worm->cells.end; ++iterator)
	{
		screenChars[position] = 0x00;
		const Direction direction = worm->cellDirectionsBuffer[iterator];
		position += getPositionOffsetForDirection(direction);
	}
}

void wormStep(Worm *worm)
{
	if (worm->state == WormState_dead)
	{
		return;
	}

	vic.color_border = worm->color;

	int8_t growthRate = 3;
	int8_t headSpeed = worm->speed;
	int8_t tailSpeed = 0;
	switch (worm->state)
	{
		case WormState_alive:
		{
			tailSpeed = MAX(0, headSpeed - growthRate);
			break;
		}

		case WormState_blocked:
		{
			tailSpeed = headSpeed * 2;
			break;
		}

		case WormState_titleScreen:
		{
			tailSpeed = headSpeed;
			break;
		}
	}

	wormMicroStepHead(worm, headSpeed);
	wormMicroStepTail(worm, tailSpeed);

	if (circularBufferSize(&worm->cells) <= 4)
	{
		worm->state = WormState_dead;
		wormErase(worm);
	}

	vic.color_border = VCOL_BLACK;
}

void wormSetNextDirection(Worm *worm, Direction wantedNextDirection)
{
	Direction currentDirection = worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 1)];
	if (isValidNextDirection(worm->headPosition, wantedNextDirection))
	{
		worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 0)] = wantedNextDirection;
	}
}