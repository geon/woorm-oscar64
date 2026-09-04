#include "controller.h"
#include <assert.h>

typedef struct PathController
{
	Direction *path;
	uint8_t pathLength;
	uint8_t currentPathStep;
} PathController;

PathController pathControllers[4];

void pathControllerInit(uint8_t wormIndex, Direction path[], uint8_t pathLength)
{
	assert(pathLength > 0);

	pathControllers[wormIndex].path = path;
	pathControllers[wormIndex].pathLength = pathLength;
	pathControllers[wormIndex].currentPathStep = 0;
}

Direction controllerGetDirectionPath(uint8_t wormIndex)
{
	Direction direction = pathControllers[wormIndex].path[pathControllers[wormIndex].currentPathStep];

	++(pathControllers[wormIndex].currentPathStep);
	if (pathControllers[wormIndex].currentPathStep >= pathControllers[wormIndex].pathLength)
	{
		pathControllers[wormIndex].currentPathStep = 0;
	}

	return direction;
}

ControllerGetDirection controllerAllGetDirection[ControllerName_count] = {
	controllerGetDirectionPath,
};
