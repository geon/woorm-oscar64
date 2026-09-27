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

Coord coordFromDirection(Direction direction)
{
	switch (direction)
	{
		case Direction_up:
			return (Coord){0, -1};
		case Direction_down:
			return (Coord){0, 1};
		case Direction_left:
			return (Coord){-1, 0};
		case Direction_right:
			return (Coord){1, 0};
	}
}

Coord coordAdd(Coord a, Coord b)
{
	return (Coord){
		a.x + b.x,
		a.y + b.y,
	};
}

Coord coordSubtract(Coord a, Coord b)
{
	return (Coord){
		a.x - b.x,
		a.y - b.y,
	};
}

Coord coordScale(Coord coord, int8_t factor)
{
	return (Coord){
		coord.x * factor,
		coord.y * factor,
	};
}
