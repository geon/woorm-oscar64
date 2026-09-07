#include "coord.h"
#include "test/custom-asserts.h"
#include "test/test.h"
#include <stdio.h>

void coordTest(void)
{
	beginTest("Create coord.");
	{
		assertByteDecimal("coord.x", coordCreate(10, 20).x, 10);
		assertByteDecimal("coord.y", coordCreate(10, 20).y, 20);
	}
	endTest();

	beginTest("Convert coord and position.");
	{
		assertCoord("coordFromPos 1", coordFromPos(coordToPos(coordCreate(10, 10))), coordCreate(10, 10));
		assertCoord("coordFromPos 2", coordFromPos(coordToPos(coordCreate(34, 12))), coordCreate(34, 12));
		assertWordDecimal("coordToPos 1", coordToPos(coordFromPos(0)), 0);
		assertWordDecimal("coordToPos 2", coordToPos(coordFromPos(999)), 999);
		assertWordDecimal("coordToPos 3", coordToPos(coordFromPos(410)), 410);
		assertWordDecimal("coordToPos 4", coordToPos(coordFromPos(321)), 321);
	}
	endTest();
}
