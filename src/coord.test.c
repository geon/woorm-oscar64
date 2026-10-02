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
		assertCoord("coordFromPos 1", coordFromPos(coordToPos(coordCreate(5, 5))), coordCreate(5, 5));
		assertCoord("coordFromPos 2", coordFromPos(coordToPos(coordCreate(3, 7))), coordCreate(3, 7));
		assertWordDecimal("coordToPos 1", coordToPos(coordFromPos(0)), 0);
		assertWordDecimal("coordToPos 2", coordToPos(coordFromPos(49)), 49);
	}

	beginTest("Add coords.");
	{
		assertCoord("Positive", coordAdd(coordCreate(5, 5), coordCreate(5, 5)), coordCreate(10, 10));
		assertCoord("Zero", coordAdd(coordCreate(5, 5), coordCreate(-5, -5)), coordCreate(0, 0));
		assertCoord("Negative", coordAdd(coordCreate(5, 5), coordCreate(-15, -15)), coordCreate(-10, -10));
	}

	beginTest("Subtract coords.");
	{
		assertCoord("Positive", coordSubtract(coordCreate(15, 15), coordCreate(5, 5)), coordCreate(10, 10));
		assertCoord("Zero", coordSubtract(coordCreate(5, 5), coordCreate(5, 5)), coordCreate(0, 0));
		assertCoord("Negative", coordSubtract(coordCreate(5, 5), coordCreate(15, 15)), coordCreate(-10, -10));
	}
	endTest();

	beginTest("Scale coords.");
	{
		assertCoord("Positive", coordScale(coordCreate(5, 5), 2), coordCreate(10, 10));
		assertCoord("Zero", coordScale(coordCreate(5, 5), 0), coordCreate(0, 0));
		assertCoord("Negative", coordScale(coordCreate(5, 5), -2), coordCreate(-10, -10));
	}
	endTest();
}
