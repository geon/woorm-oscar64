#ifndef WORM_H
#define WORM_H

#include "circular-buffer.h"
#include "direction.h"
#include <stdint.h>

#define NUM_WORMS 4

uint16_t wormHeadPosition[NUM_WORMS];
uint16_t wormTailPosition[NUM_WORMS];
CircularBuffer wormCells[NUM_WORMS];
Direction wormCellDirectionsBuffer[NUM_WORMS][0x100];
#pragma align(wormCellDirectionsBuffer, 256)

extern const uint8_t playerColors[NUM_WORMS];

void wormInit(uint8_t wormIndex, uint16_t pos, Direction direction);
void wormDraw(uint8_t wormIndex);

#endif
