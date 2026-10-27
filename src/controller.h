#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "coord.h"
#include "direction.h"
#include <stdint.h>

typedef struct Worm;

typedef enum ControllerName
{
	ControllerName_first,
	ControllerName_none = 0,
	ControllerName_path,
	ControllerName_aimless,
	ControllerName_attack,
	ControllerName_count
} ControllerName;

typedef struct PathController
{
	Direction *path;
	uint8_t pathLength;
	uint8_t currentPathStep;
} PathController;

void pathControllerInit(PathController *pathController, Direction path[], uint8_t pathLength);
Direction pathControllerGetDirection(PathController *pathController);

Worm *getOpponent(Worm *worm);
Direction turnIfOpposite(Direction currentDirection, Direction wantedDirection);
Direction getDirectionOfTarget(Coord wormCoord, Coord targetCoord);

#endif
