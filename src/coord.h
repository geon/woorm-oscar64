#ifndef COORD_H
#define COORD_H

#include "direction.h"
#include <stdint.h>

typedef struct Coord
{
	int8_t x;
	int8_t y;
} Coord;

Coord coordCreate(int8_t x, int8_t y);
uint16_t coordToPos(Coord coord);
Coord coordFromPos(uint16_t pos);
Coord coordAdd(Coord a, Coord b);
Coord coordSubtract(Coord a, Coord b);
Coord coordScale(Coord coord, int8_t factor);

#endif
