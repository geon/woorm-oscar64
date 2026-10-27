#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "direction.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct CircularBuffer
{
	uint8_t begin;
	uint8_t end;
	Direction *directions;
} CircularBuffer;

void circularBufferInit(CircularBuffer *circularBuffer, Direction *directions);
bool circularBufferPush(CircularBuffer *circularBuffer, Direction direction);
Direction circularBufferPop(CircularBuffer *circularBuffer);
uint8_t circularBufferSize(CircularBuffer *circularBuffer);
Direction circularBufferAtIndex(CircularBuffer *circularBuffer, uint8_t index);
Direction circularBufferAtIndexReverse(CircularBuffer *circularBuffer, uint8_t index);
void circularBufferSetAtIndexReverse(CircularBuffer *circularBuffer, uint8_t index, Direction direction);

#endif
