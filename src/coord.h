#ifndef COORD_H
#define COORD_H

#include "direction.h"
#include <stdint.h>

typedef struct Coord
{
	uint8_t x;
	uint8_t y;
} Coord;

Coord coordCreate(uint8_t x, uint8_t y);
uint16_t coordToPos(Coord coord);
Coord coordFromPos(uint16_t pos);

#endif
