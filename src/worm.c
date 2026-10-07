#include "worm.h"
#include "circular-buffer.h"
#include "direction.h"
#include "screen.h"
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
	circularBufferInit(&worm->cells);
	worm->cellDirectionsBuffer = cellDirectionsBuffer;

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

	for (uint8_t iterator = worm->cells.begin; iterator < worm->cells.end; ++iterator)
	{
		const Direction direction = worm->cellDirectionsBuffer[iterator];
		position += getPositionOffsetForDirection(direction);

		screenChars[position] = 1;
		screenColors[position] = color;
	}
}

void wormFullStepHead(Worm *worm)
{
	Direction direction = worm->controllerGetDirection ? worm->controllerGetDirection(worm->index) : worm->cellDirectionsBuffer[circularBufferAtIndexReverse(&worm->cells, 0)];
	uint16_t nextPosition = worm->headPosition + getPositionOffsetForDirection(direction);

	wormPushDirection(worm, direction);
	worm->headPosition = nextPosition;

	// Draw the worm in the tile it just entered.
	screenChars[worm->headPosition] = 1;
	screenColors[worm->headPosition] = worm->color;
}

void wormFullStepTail(Worm *worm)
{
	// Erase the worm from the tile it just left.
	screenChars[worm->tailPosition] = 0x00;

	worm->tailPosition += getPositionOffsetForDirection(worm->cellDirectionsBuffer[circularBufferAtIndex(&worm->cells, 0)]);
	uint8_t segmentIndex;
	circularBufferPop(&worm->cells, &segmentIndex);
}

void wormStep(Worm *worm)
{
	vic.color_border = worm->color;

	wormFullStepHead(worm);
	wormFullStepTail(worm);

	vic.color_border = VCOL_BLACK;
}
