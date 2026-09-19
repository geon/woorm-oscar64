#include "worm.h"
#include "circular-buffer.h"
#include "direction.h"
#include "screen.h"
#include "worm-char.h"

void wormPushDirection(uint8_t wormIndex, Direction direction)
{
	uint8_t segmentIndex;
	circularBufferPush(&wormCells[wormIndex], &segmentIndex);
	wormCellDirectionsBuffer[wormIndex][segmentIndex] = direction;
}

void wormInit(uint8_t wormIndex, uint16_t pos, Direction direction, WormControllerGetDirection controllerGetDirection)
{
	wormHeadPosition[wormIndex] = pos;
	wormTailPosition[wormIndex] = pos - getPositionOffsetForDirection(direction) * 3;
	wormControllerGetDirection[wormIndex] = controllerGetDirection;
	wormHeadMicroStep[wormIndex] = 3;
	wormTailMicroStep[wormIndex] = 0;
	wormSpeed[wormIndex] = 16;
	wormTailSpeed[wormIndex] = wormSpeed[wormIndex] + 1;
	wormBlocked[wormIndex] = false;
	circularBufferInit(&wormCells[wormIndex]);

	wormPushDirection(wormIndex, direction);
	wormPushDirection(wormIndex, direction);
	wormPushDirection(wormIndex, direction);
	wormPushDirection(wormIndex, direction);
	wormPushDirection(wormIndex, direction);

	wormDraw(wormIndex);
}

void wormDraw(uint8_t wormIndex)
{
	const uint8_t color = playerColors[wormIndex] + 8;
	uint16_t position = wormTailPosition[wormIndex];

	screenChars[position] = 1;
	screenColors[position] = color;

	uint8_t iterator;
	circularBufferForEach((&wormCells[wormIndex]), iterator)
	{
		if (iterator == (uint8_t)(wormCells[wormIndex].end - 2))
		{
			break;
		}

		const Direction direction = wormCellDirectionsBuffer[wormIndex][iterator];
		position += getPositionOffsetForDirection(direction);

		screenChars[position] = 1;
		screenColors[position] = color;
	}
}

bool isValidNextDirection(uint8_t wormIndex, uint16_t nextPosition, Direction nextDirection)
{
	uint16_t nextNextPosition = nextPosition + getPositionOffsetForDirection(nextDirection);

	bool isOccupied =
		// screenChars[nextPosition] ||
		screenChars[nextNextPosition];

	return !isOccupied;
}

void wormFullStepHead(uint8_t wormIndex)
{
	Direction direction = wormCellDirectionsBuffer[wormIndex][wormCells[wormIndex].end - 1];
	uint16_t nextPosition = wormHeadPosition[wormIndex] + getPositionOffsetForDirection(direction);
	Direction nextDirection = wormControllerGetDirection[wormIndex](wormIndex);

	if (screenChars[nextPosition])
	{
		// Only move forward if the tile is not blocked.
		wormBlocked[wormIndex] = true;
		return;
	}

	// Try the requested direction.
	if (!isValidNextDirection(wormIndex, nextPosition, nextDirection))
	{
		// Otherwise, try forward.
		nextDirection = direction;
		if (!isValidNextDirection(wormIndex, nextPosition, nextDirection))
		{
			// Or clockwise.
			nextDirection = (direction + 1) % Direction_count;
			if (!isValidNextDirection(wormIndex, nextPosition, nextDirection))
			{
				// Or counter clockwise.
				nextDirection = (direction + Direction_count - 1) % Direction_count;
				if (!isValidNextDirection(wormIndex, nextPosition, nextDirection))
				{
					// No valid next direction, so just move straight forward.
					nextDirection = direction;
				}
			}
		}
	}

	wormHeadPosition[wormIndex] = nextPosition;
	wormPushDirection(wormIndex, nextDirection);
	screenColors[nextPosition] = playerColors[wormIndex] + 8;
}

void wormFullStepTail(uint8_t wormIndex)
{
	// Erase the worm from the tile it just left.
	screenChars[wormTailPosition[wormIndex]] = 0x00;

	uint8_t segmentIndex;
	circularBufferPop(&wormCells[wormIndex], &segmentIndex);
	wormTailPosition[wormIndex] += getPositionOffsetForDirection(wormCellDirectionsBuffer[wormIndex][wormCells[wormIndex].begin]);
}

void wormMicroStepHead(uint8_t wormIndex, uint8_t numMicroSteps)
{
	uint8_t old = wormHeadMicroStep[wormIndex];
	uint8_t new = wormHeadMicroStep[wormIndex] + numMicroSteps;
	bool overflowed = old > new;

	if (overflowed)
	{
		wormFullStepHead(wormIndex);
	}

	if (wormBlocked[wormIndex])
	{
		return;
	}

	wormHeadMicroStep[wormIndex] = new;

	// Head:
	// Zero index is the first visible tile, and index 3 is completely filled.
	// On overflow, the head immediately occupies 2 pixels in the new tile.

	// End:
	// Zero index is full, and index 3 is the last visible tile. Reverse of the head.
	// On overflow, the end tile used to only occupy 2 pixels, and is erased.

	// Draw the worm.
	screenChars[wormHeadPosition[wormIndex]] = charsetLookup[wormCharPackBits(
		WormCharPlacement_head,
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].end - 2)],
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].end - 1)],
		wormHeadMicroStep[wormIndex])];

	screenChars[wormHeadPosition[wormIndex] - getPositionOffsetForDirection(wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].end - 2)])] = charsetLookup[wormCharPackBits(
		WormCharPlacement_after_head,
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].end - 3)],
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].end - 2)],
		wormHeadMicroStep[wormIndex])];
}

void wormMicroStepTail(uint8_t wormIndex, uint8_t numMicroSteps)
{
	uint8_t old = wormTailMicroStep[wormIndex];
	uint8_t new = wormTailMicroStep[wormIndex] + numMicroSteps;
	wormTailMicroStep[wormIndex] = new;
	bool overflowed = old > new;

	if (overflowed)
	{
		wormFullStepTail(wormIndex);
	}

	// Draw the worm.
	screenChars[wormTailPosition[wormIndex]] = charsetLookup[wormCharPackBits(
		WormCharPlacement_end,
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].begin + 0)],
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].begin + 1)],
		wormTailMicroStep[wormIndex])];

	screenChars[wormTailPosition[wormIndex] + getPositionOffsetForDirection(wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].begin + 1)])] = charsetLookup[wormCharPackBits(
		WormCharPlacement_before_end,
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].begin + 1)],
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].begin + 2)],
		wormTailMicroStep[wormIndex])];
}

int8_t max(int8_t a, int8_t b)
{
	return a > b ? a : b;
}

void wormStep(uint8_t wormIndex)
{
	uint8_t headSpeed = wormSpeed[wormIndex];
	uint8_t tailSpeed = wormTailSpeed[wormIndex];

	if (!wormBlocked[wormIndex])
	{
		wormMicroStepHead(wormIndex, headSpeed);
		wormMicroStepTail(wormIndex, tailSpeed);
	}
}

// void setSpeed(){
// 	  uint8_t tailSpeed = blocked ? 0 : max(0, headSpeed - growthRate);
// }
