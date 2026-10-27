#ifndef WORM_H
#define WORM_H

#include "circular-buffer.h"
#include "direction.h"
#include <stdint.h>

typedef struct Worm
{
	uint8_t color;
	uint16_t headPosition;
	uint16_t tailPosition;
	CircularBuffer cells;
} Worm;

void wormInit(Worm *worm, uint8_t color, uint16_t pos, Direction direction, Direction *cellDirectionsBuffer);
void wormDraw(Worm *worm);
void wormFullStepHead(Worm *worm);
void wormFullStepTail(Worm *worm);
void wormStep(Worm *worm);

#endif
