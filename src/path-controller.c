#include "path-controller.h"
#include <assert.h>

void pathControllerInit(PathController *pathController, Direction path[], uint8_t pathLength)
{
	assert(pathLength > 0);

	pathController->path = path;
}

Direction pathControllerGetDirection(PathController *pathController)
{
	Direction direction = pathController->path[0];

	return direction;
}
