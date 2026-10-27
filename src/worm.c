#include "worm.h"
#include "circular-buffer.h"
#include "direction.h"
#include "screen.h"
#include "worm-char.h"
#include "worms.h"
#include <c64/vic.h>

void wormPushDirection(Worm *worm, Direction direction)
{
	circularBufferPush(&worm->cells, direction);
}

uint8_t wormGetIndex(Worm *worm)
{
	for (uint8_t wormIndex = 0; wormIndex < NUM_WORMS; ++wormIndex)
	{
		if (&worms[wormIndex] == worm)
		{
			return wormIndex;
		}
	}

	// Should never happen.
	assert(true);
	return 0xff;
}

void wormInit(Worm *worm, uint8_t color, uint16_t pos, Direction direction, Direction *cellDirectionsBuffer)
{
	worm->color = color;
	worm->state = WormState_alive;
	worm->opponent = &worms[(wormGetIndex(worm) + 1) % NUM_WORMS];
	worm->headPosition = pos;
	worm->tailPosition = pos - getPositionOffsetForDirection(direction) * 3;
	worm->controller = ControllerName_none;
	worm->pathController = nullptr;
	worm->headMicroStep = 3;
	worm->tailMicroStep = 0;
	worm->speed = 16;
	circularBufferInit(&worm->cells, cellDirectionsBuffer);

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

	for (uint8_t cellIndex = 0; cellIndex < circularBufferSize(&worm->cells) - 2; ++cellIndex)
	{
		const Direction direction = circularBufferAtIndex(&worm->cells, cellIndex);
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
	Direction direction = circularBufferAtIndexReverse(&worm->cells, 0);
	uint16_t nextPosition = worm->headPosition + getPositionOffsetForDirection(direction);

	Direction nextDirection;
	switch (worm->controller)
	{
		case ControllerName_path:
		{
			nextDirection = pathControllerGetDirection(worm->pathController);
			break;
		}

		default:
		{
			nextDirection = direction;
			break;
		}
	}

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
	circularBufferPop(&worm->cells);

	// Erase the worm from the tile it just left.
	screenChars[worm->tailPosition] = 0x00;

	worm->tailPosition += getPositionOffsetForDirection(circularBufferAtIndex(&worm->cells, 0));
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
		// Check is still blocked.
		Direction direction = circularBufferAtIndexReverse(&worm->cells, 0);
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
		circularBufferAtIndexReverse(&worm->cells, 1),
		circularBufferAtIndexReverse(&worm->cells, 0),
		worm->headMicroStep)];

	screenChars[worm->headPosition - getPositionOffsetForDirection(circularBufferAtIndexReverse(&worm->cells, 1))] = charsetLookup[wormCharPackBits(
		WormCharPlacement_after_head,
		circularBufferAtIndexReverse(&worm->cells, 2),
		circularBufferAtIndexReverse(&worm->cells, 1),
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
		circularBufferAtIndex(&worm->cells, 0),
		circularBufferAtIndex(&worm->cells, 1),
		worm->tailMicroStep)];

	screenChars[worm->tailPosition + getPositionOffsetForDirection(circularBufferAtIndex(&worm->cells, 1))] = charsetLookup[wormCharPackBits(
		WormCharPlacement_before_end,
		circularBufferAtIndex(&worm->cells, 1),
		circularBufferAtIndex(&worm->cells, 2),
		worm->tailMicroStep)];
}

void wormStep(Worm *worm)
{
	vic.color_border = worm->color;

	uint8_t growthRate = 1;
	uint8_t headSpeed = worm->speed;
	uint8_t blocked = worm->state == WormState_blocked;
	uint8_t tailSpeed = blocked ? 0 : headSpeed;

	wormMicroStepHead(worm, headSpeed);
	wormMicroStepTail(worm, tailSpeed);

	vic.color_border = VCOL_BLACK;
}

void wormSetNextDirection(Worm *worm, Direction wantedNextDirection)
{
	Direction currentDirection = circularBufferAtIndexReverse(&worm->cells, 1);
	if (isValidNextDirection(worm->headPosition, wantedNextDirection))
	{
		circularBufferSetAtIndexReverse(&worm->cells, 0, wantedNextDirection);
	}
}