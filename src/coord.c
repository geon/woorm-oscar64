#include "coord.h"
#include "direction.h"
#include "screen.h"
#include <stdint.h>

Coord coordCreate(uint8_t x, uint8_t y)
{
	Coord coord;
	coord.x = x;
	coord.y = y;
	return coord;
}

uint16_t coordToPos(Coord coord)
{
	return coord.x + coord.y * SCREEN_WIDTH;
}

Coord posToCoord(uint16_t pos)
{
	Coord coord;
	coord.x = (uint8_t)(pos % SCREEN_WIDTH);
	coord.y = (uint8_t)(pos / SCREEN_WIDTH);
	return coord;
}
