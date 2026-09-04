#ifndef PATH_CONTROLLER_H
#define PATH_CONTROLLER_H

#include "direction.h"
#include <stdint.h>

typedef struct PathController
{
	Direction *path;
	uint8_t currentPathStep;
} PathController;

void pathControllerInit(PathController *pathController, Direction path[], uint8_t pathLength);
Direction pathControllerGetDirection(PathController *pathController);

#endif
