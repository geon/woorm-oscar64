#ifndef WORMS_H
#define WORMS_H

#include "circular-buffer.h"
#include "direction.h"
#include "worm.h"
#include <c64/vic.h>
#include <stdint.h>

#define NUM_WORMS 4

Worm worms[NUM_WORMS];
Direction wormCellDirectionsBuffers[NUM_WORMS][0x100];
#pragma align(wormCellDirectionsBuffers, 256);

const uint8_t playerColors[NUM_WORMS] = {
	VCOL_YELLOW,
	VCOL_CYAN,
	VCOL_GREEN,
	VCOL_RED,
};

#endif
