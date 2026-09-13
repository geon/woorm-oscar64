#ifndef PATH_CONTROLLER_H
#define PATH_CONTROLLER_H

#include "direction.h"
#include <stdint.h>

typedef struct PathController
{
	Direction *path;
	uint8_t currentPathStep;
} PathController;

void pathControllerInit(uint8_t wormIndex, Direction path[], uint8_t pathLength);
Direction pathControllerGetDirection(uint8_t wormIndex);

#endif
