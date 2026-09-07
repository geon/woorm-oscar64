#include "worm.h"
#include "circular-buffer.h"
#include "direction.h"
#include "screen.h"
#include "worm-char.h"

void wormPushDirection(uint8_t wormIndex, Direction direction)
{
	uint8_t segmentIndex;
	circularBufferPush(wormCells[wormIndex].begin, &wormCells[wormIndex].end, &segmentIndex);
	wormCellDirectionsBuffer[wormIndex][segmentIndex] = direction;
}

void wormInit(uint8_t wormIndex, uint16_t pos, Direction direction, void *controller, WormControllerGetDirection controllerGetDirection)
{
	wormHeadPosition[wormIndex] = pos;
	wormTailPosition[wormIndex] = pos - getPositionOffsetForDirection(direction) * 3;
	wormController[wormIndex] = controller;
	wormControllerGetDirection[wormIndex] = controllerGetDirection;
	wormHeadMicroStep[wormIndex] = 3;
	wormTailMicroStep[wormIndex] = 0;
	wormSpeed[wormIndex] = 16;
	circularBufferInit(&wormCells[wormIndex].begin, &wormCells[wormIndex].end);

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
	circularBufferForEach(wormCells[wormIndex].begin, wormCells[wormIndex].end - 1, iterator)
	{
		const Direction direction = wormCellDirectionsBuffer[wormIndex][iterator];
		position += getPositionOffsetForDirection(direction);

		screenChars[position] = 1;
		screenColors[position] = color;
	}
}

void wormFullStepHead(uint8_t wormIndex)
{
	Direction direction = wormCellDirectionsBuffer[wormIndex][wormCells[wormIndex].end];
	wormHeadPosition[wormIndex] += getPositionOffsetForDirection(direction);
	wormPushDirection(wormIndex, direction);
	wormCellDirectionsBuffer[wormIndex][wormCells[wormIndex].end] = wormControllerGetDirection[wormIndex](wormController[wormIndex]);
}

void wormFullStepTail(uint8_t wormIndex)
{
	// Erase the worm from the tile it just left.
	screenChars[wormTailPosition[wormIndex]] = 0x00;

	uint8_t segmentIndex;
	circularBufferPop(&wormCells[wormIndex].begin, wormCells[wormIndex].end, &segmentIndex);
	wormTailPosition[wormIndex] += getPositionOffsetForDirection(wormCellDirectionsBuffer[wormIndex][wormCells[wormIndex].begin]);
}

void wormMicroStepHead(uint8_t wormIndex, uint8_t numMicroSteps)
{
	uint8_t old = wormHeadMicroStep[wormIndex];
	uint8_t new = wormHeadMicroStep[wormIndex] += numMicroSteps;
	bool overflowed = old > new;

	if (overflowed)
	{
		wormFullStepHead(wormIndex);
		// Overflowed into new tile, so color it.
		screenColors[wormHeadPosition[wormIndex]] = playerColors[wormIndex] + 8;
	}

	// Head:
	// Zero index is the first visible tile, and index 3 is completely filled.
	// On overflow, the head immediately occupies 2 pixels in the new tile.

	// End:
	// Zero index is full, and index 3 is the last visible tile. Reverse of the head.
	// On overflow, the end tile used to only occupy 2 pixels, and is erased.

	// Draw the worm.
	screenChars[wormHeadPosition[wormIndex]] = charsetLookup[wormCharPackBits(
		WormCharPlacement_head,
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].end - 1)],
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].end - 0)],
		wormHeadMicroStep[wormIndex])];

	screenChars[wormHeadPosition[wormIndex] - getPositionOffsetForDirection(wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].end - 1)])] = charsetLookup[wormCharPackBits(
		WormCharPlacement_after_head,
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].end - 2)],
		wormCellDirectionsBuffer[wormIndex][(uint8_t)(wormCells[wormIndex].end - 1)],
		wormHeadMicroStep[wormIndex])];
}

void wormMicroStepTail(uint8_t wormIndex, uint8_t numMicroSteps)
{
	uint8_t old = wormTailMicroStep[wormIndex];
	uint8_t new = wormTailMicroStep[wormIndex] += numMicroSteps;
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

void wormStep(uint8_t wormIndex)
{
	uint8_t growthRate = 1;
	uint8_t headSpeed = wormSpeed[wormIndex];
	uint8_t tailSpeed = headSpeed;

	wormMicroStepHead(wormIndex, headSpeed);
	wormMicroStepTail(wormIndex, tailSpeed);
}
