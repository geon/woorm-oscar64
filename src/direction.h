#ifndef DIRECTION_H
#define DIRECTION_H

#include <stdint.h>

typedef enum Direction
{
	Direction_first,
	Direction_up = 0,
	Direction_right,
	Direction_down,
	Direction_left,
	Direction_count
} Direction;

int8_t getPositionOffsetForDirection(Direction direction);

#endif
