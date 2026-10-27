#include "circular-buffer.h"

void circularBufferInit(CircularBuffer *circularBuffer, Direction *directions)
{
	circularBuffer->begin = 0;
	circularBuffer->end = 0;
	circularBuffer->directions = directions;
}

bool circularBufferPush(CircularBuffer *circularBuffer, Direction direction)
{
	if (circularBufferSize(circularBuffer) > 0xfe)
	{
		return false;
	}

	circularBuffer->directions[circularBuffer->end] = direction;
	++(circularBuffer->end);
	return true;
}

Direction circularBufferPop(CircularBuffer *circularBuffer)
{
	if (circularBufferSize(circularBuffer) == 0)
	{
		return Direction_count;
	}

	Direction direction = circularBuffer->directions[circularBuffer->begin];
	++(circularBuffer->begin);
	return direction;
}

uint8_t circularBufferSize(CircularBuffer *circularBuffer)
{
	return circularBuffer->end - circularBuffer->begin;
}

Direction circularBufferAtIndex(CircularBuffer *circularBuffer, uint8_t index)
{
	return circularBuffer->directions[circularBuffer->begin + index];
}

Direction circularBufferAtIndexReverse(CircularBuffer *circularBuffer, uint8_t index)
{
	return circularBuffer->directions[circularBuffer->end - 1 - index];
}

void circularBufferSetAtIndexReverse(CircularBuffer *circularBuffer, uint8_t index, Direction direction)
{
	circularBuffer->directions[circularBuffer->end - 1 - index] = direction;
}
