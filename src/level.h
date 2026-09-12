#ifndef LEVEL_H
#define LEVEL_H

#include "coord.h"
#include "direction.h"
#include "screen.h"
#include "worm.h"
#include <stdint.h>

typedef struct PlayerStart
{
	Coord position;
	Direction direction;
} PlayerStart;

typedef struct Level
{
	char *name;
	uint8_t multiColor1;
	uint8_t multiColor2;
	PlayerStart playerStarts[4];
	uint8_t *chars;
	uint8_t *colors;
	uint8_t *charset;
} Level;

void levelLoad(const Level *level);
void levelSetMultiColors(const Level *level);
void levelStart(const Level *level, uint8_t numWorms);

#endif
