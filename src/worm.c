#include "worm.h"
#include "circular-buffer.h"
#include "direction.h"
#include "screen.h"
#include <c64/vic.h>

void wormPushDirection(Worm *worm, Direction direction)
{
	uint8_t segmentIndex;
	circularBufferPush(&worm->cells, direction);
}

void wormInit(Worm *worm, uint8_t color, uint16_t pos, Direction direction, Direction *cellDirectionsBuffer)
{
	worm->color = color;
	worm->headPosition = pos;
	worm->tailPosition = pos - getPositionOffsetForDirection(direction) * 3;
	worm->controller = ControllerName_none;
	worm->pathController = nullptr;
	circularBufferInit(&worm->cells, cellDirectionsBuffer);

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

	for (uint8_t cellIndex = 0; cellIndex < circularBufferSize(&worm->cells); ++cellIndex)
	{
		const Direction direction = circularBufferAtIndex(&worm->cells, cellIndex);
		position += getPositionOffsetForDirection(direction);

		screenChars[position] = 1;
		screenColors[position] = color;
	}
}

void wormFullStepHead(Worm *worm)
{
	Direction direction;
	switch (worm->controller)
	{
		case ControllerName_path:
		{
			direction = pathControllerGetDirection(worm->pathController);
			break;
		}

		default:
		{
			direction = circularBufferAtIndexReverse(&worm->cells, 0);
			break;
		}
	}

	uint16_t nextPosition = worm->headPosition + getPositionOffsetForDirection(direction);

	wormPushDirection(worm, direction);
	worm->headPosition = nextPosition;

	wormDraw(worm);
}

void wormFullStepTail(Worm *worm)
{
	screenChars[worm->tailPosition] = 0x00;

	worm->tailPosition += getPositionOffsetForDirection(circularBufferAtIndex(&worm->cells, 0));
	circularBufferPop(&worm->cells);
}

void wormStep(Worm *worm)
{
	vic.color_border = worm->color;

	wormFullStepHead(worm);
	wormFullStepTail(worm);

	vic.color_border = VCOL_BLACK;
}
