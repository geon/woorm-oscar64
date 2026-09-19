#include "ai-controller.h"
#include "screen.h"
#include "worm.h"

Direction aiControllerGetDirection(uint8_t wormIndex)
{
	// Just keep moving forwards.
	Direction direction = wormCellDirectionsBuffer[wormIndex][wormCells[wormIndex].end - 1];

	return direction;
}