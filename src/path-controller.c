#include "path-controller.h"
#include <assert.h>

PathController pathControllers[4];

void pathControllerInit(uint8_t wormIndex, Direction path[], uint8_t pathLength)
{
	assert(pathLength > 0);

	pathControllers[wormIndex].path = path;
	pathControllers[wormIndex].currentPathStep = 0;
}

Direction pathControllerGetDirection(uint8_t wormIndex)
{
	Direction direction = pathControllers[wormIndex].path[pathControllers[wormIndex].currentPathStep];

	++(pathControllers[wormIndex].currentPathStep);

	return direction;
}
