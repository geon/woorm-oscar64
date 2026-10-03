#include "coord.h"
#include "direction.h"
#include "screen.h"
#include <stdint.h>

Coord coordCreate(int8_t x, int8_t y)
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

Coord coordFromPos(uint16_t pos)
{
	Coord coord;
	coord.x = (int8_t)(pos % SCREEN_WIDTH);
	coord.y = (int8_t)(pos / SCREEN_WIDTH);
	return coord;
}
