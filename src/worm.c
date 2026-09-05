#include "worm.h"
#include "circular-buffer.h"
#include "direction.h"
#include "screen.h"

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
	wormHeadMicroStep[wormIndex] = 0;
	wormTailMicroStep[wormIndex] = 0;
	wormSpeed[wormIndex] = 16;
	circularBufferInit(&wormCells[wormIndex].begin, &wormCells[wormIndex].end);

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
	circularBufferForEach(wormCells[wormIndex].begin, wormCells[wormIndex].end, iterator)
	{
		const Direction direction = wormCellDirectionsBuffer[wormIndex][iterator];
		position += getPositionOffsetForDirection(direction);

		screenChars[position] = 1;
		screenColors[position] = color;
	}
}

void wormFullStepHead(uint8_t wormIndex)
{
	Direction direction = wormControllerGetDirection[wormIndex](wormController[wormIndex]);
	wormHeadPosition[wormIndex] += getPositionOffsetForDirection(direction);
	wormPushDirection(wormIndex, direction);

	// Draw the worm in the tile it just entered.
	screenChars[wormHeadPosition[wormIndex]] = 1;
	screenColors[wormHeadPosition[wormIndex]] = playerColors[wormIndex];
}

void wormFullStepTail(uint8_t wormIndex)
{
	// Erase the worm from the tile it just left.
	screenChars[wormTailPosition[wormIndex]] = 0x00;

	wormTailPosition[wormIndex] += getPositionOffsetForDirection(wormCellDirectionsBuffer[wormIndex][wormCells[wormIndex].begin]);
	uint8_t segmentIndex;
	circularBufferPop(&wormCells[wormIndex].begin, wormCells[wormIndex].end, &segmentIndex);
}

void wormMicroStepHead(uint8_t wormIndex, uint8_t numMicroSteps)
{
	uint8_t old = wormHeadMicroStep[wormIndex];
	uint8_t new = wormHeadMicroStep[wormIndex] += numMicroSteps;
	bool overflowed = old > new;

	if (overflowed)
	{
		wormFullStepHead(wormIndex);
	}
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
}

void wormStep(uint8_t wormIndex)
{
	uint8_t growthRate = 1;
	uint8_t headSpeed = wormSpeed[wormIndex];
	uint8_t tailSpeed = headSpeed;

	wormMicroStepHead(wormIndex, headSpeed);
	wormMicroStepTail(wormIndex, tailSpeed);
}
