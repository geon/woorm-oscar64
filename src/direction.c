#include "direction.h"
#include <stdint.h>

#define SCREEN_WIDTH 40

int8_t offsets[Direction_count] = {
	// Direction_up
	-SCREEN_WIDTH,
	// Direction_right
	1,
	// Direction_down
	SCREEN_WIDTH,
	// Direction_left
	-1};

int8_t getPositionOffsetForDirection(Direction direction)
{
	return offsets[direction];
}
