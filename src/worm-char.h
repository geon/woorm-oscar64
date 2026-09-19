#ifndef WORM_CHAR_H
#define WORM_CHAR_H

#include "direction.h"
#include <stdint.h>

typedef enum WormCharPlacement
{
	WormCharPlacement_head,
	WormCharPlacement_after_head,
	WormCharPlacement_before_end,
	WormCharPlacement_end,
} WormCharPlacement;

uint8_t wormCharPackBits(WormCharPlacement placement, Direction lastDirection, Direction direction, uint8_t microStep);

extern const uint8_t charsetLookup[256];

#endif
