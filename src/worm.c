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

void wormInit(uint8_t wormIndex, uint16_t pos, Direction direction)
{
	wormHeadPosition[wormIndex] = pos;
	wormTailPosition[wormIndex] = pos - getPositionOffsetForDirection(direction) * 3;
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
