#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "direction.h"
#include <stdint.h>

typedef Direction (*ControllerGetDirection)(uint8_t wormIndex);

typedef enum ControllerName
{
	ControllerName_first,
	ControllerName_path = 0,
	ControllerName_count
} ControllerName;

extern ControllerGetDirection controllerAllGetDirection[ControllerName_count];

void pathControllerInit(uint8_t wormIndex, Direction path[], uint8_t pathLength);

#endif
