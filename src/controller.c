#include "controller.h"
#include <assert.h>

typedef struct PathController
{
	Direction *path;
} PathController;

PathController pathControllers[4];

void pathControllerInit(uint8_t wormIndex, Direction path[], uint8_t pathLength)
{
	assert(pathLength > 0);

	pathControllers[wormIndex].path = path;
}

Direction controllerGetDirectionPath(uint8_t wormIndex)
{
	Direction direction = pathControllers[wormIndex].path[0];

	return direction;
}

ControllerGetDirection controllerAllGetDirection[ControllerName_count] = {
	controllerGetDirectionPath,
};
