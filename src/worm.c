#include "worm.h"
#include "circular-buffer.h"
#include "direction.h"
#include "screen.h"
#include "worm-char.h"
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
	worm->headPosition = pos;
	worm->tailPosition = pos - getPositionOffsetForDirection(direction) * 3;
	worm->controllerGetDirection = nullptr;
	worm->headMicroStep = 0;
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

void wormFullStepHead(Worm *worm)
{
	Direction direction = worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 0)];
	uint16_t nextPosition = worm->headPosition + getPositionOffsetForDirection(direction);
	Direction nextDirection = worm->controllerGetDirection ? worm->controllerGetDirection(worm->index) : worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 0)];

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

void wormStep(Worm *worm)
{
	vic.color_border = worm->color;

	uint8_t growthRate = 1;
	uint8_t headSpeed = worm->speed;
	uint8_t tailSpeed = headSpeed;

	wormMicroStepHead(worm, headSpeed);
	wormMicroStepTail(worm, tailSpeed);

	vic.color_border = VCOL_BLACK;
}
