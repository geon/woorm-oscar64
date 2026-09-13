#include "path-controller.h"
#include <assert.h>

PathController pathControllers[4];

void pathControllerInit(uint8_t wormIndex, Direction path[], uint8_t pathLength)
{
	assert(pathLength > 0);

	pathControllers[wormIndex].path = path;
}

Direction pathControllerGetDirection(uint8_t wormIndex)
{
	Direction direction = pathControllers[wormIndex].path[0];

	return direction;
}
