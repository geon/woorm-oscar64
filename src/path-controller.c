#include "path-controller.h"
#include <assert.h>

void pathControllerInit(PathController *pathController, Direction path[], uint8_t pathLength)
{
	assert(pathLength > 0);

	pathController->path = path;
	pathController->currentPathStep = 0;
}

Direction pathControllerGetDirection(PathController *pathController)
{
	Direction direction = pathController->path[pathController->currentPathStep];

	++(pathController->currentPathStep);

	return direction;
}
