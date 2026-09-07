#ifndef WORM_H
#define WORM_H

#include "circular-buffer.h"
#include "direction.h"
#include <stdint.h>

#define NUM_WORMS 4

typedef Direction (*WormControllerGetDirection)(void *controller);

uint16_t wormHeadPosition[NUM_WORMS];
uint16_t wormTailPosition[NUM_WORMS];
void *wormController[NUM_WORMS];
WormControllerGetDirection wormControllerGetDirection[NUM_WORMS];
CircularBuffer wormCells[NUM_WORMS];
Direction wormCellDirectionsBuffer[NUM_WORMS][0x100];
#pragma align(wormCellDirectionsBuffer, 256)

extern const uint8_t playerColors[NUM_WORMS];

void wormInit(uint8_t wormIndex, uint16_t pos, Direction direction, void *controller, WormControllerGetDirection controllerGetDirection);
void wormDraw(uint8_t wormIndex);
void wormFullStepHead(uint8_t wormIndex);
void wormFullStepTail(uint8_t wormIndex);
void wormStep(uint8_t wormIndex);

#endif
