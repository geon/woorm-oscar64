#ifndef WORM_H
#define WORM_H

#include "circular-buffer.h"
#include "controller.h"
#include "direction.h"
#include <stdint.h>

typedef enum WormState
{
	WormState_first,
	WormState_alive = 0,
	WormState_blocked,
	WormState_dead,
	WormState_count
} WormState;

typedef struct Worm
{
	uint8_t index;
	uint8_t color;
	WormState state;
	uint8_t opponentIndex;
	uint16_t headPosition;
	uint16_t tailPosition;
	ControllerGetDirection controllerGetDirection;
	uint8_t headMicroStep;
	uint8_t tailMicroStep;
	uint8_t speed;
	CircularBuffer cells;
	Direction *cellDirectionsBuffer;
} Worm;

void wormInit(Worm *worm, uint8_t index, uint8_t color, uint16_t pos, Direction direction, Direction *cellDirectionsBuffer);
void wormDraw(Worm *worm);
void wormFullStepHead(Worm *worm);
void wormFullStepTail(Worm *worm);
void wormMicroStepHead(Worm *worm, uint8_t numMicroSteps);
void wormMicroStepTail(Worm *worm, uint8_t numMicroSteps);
void wormStep(Worm *worm);
void wormSetNextDirection(Worm *worm, Direction direction);

#endif
