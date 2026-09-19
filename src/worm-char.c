#include "worm-char.h"
#include "direction.h"
#include <stdint.h>

uint8_t wormCharPackBits(WormCharPlacement placement, Direction lastDirection, Direction direction, uint8_t microStep)
{
	return (
		(0b11000000 & microStep) |
		(0b00110000 & (placement << 4)) |
		(0b00001100 & (lastDirection << 2)) |
		(0b00000011 & direction));
}

const uint8_t charsetLookup[256] = {
#embed "../generated/worm-charset-lookup.bin"
};