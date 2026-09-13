#include "path-controller.h"
#include "test/test.h"

void pathControllerTest()
{
	beginTest("PathController");
	{
		Direction path[] = {
			Direction_right,
		};
		pathControllerInit(0, path, sizeof(path));

		assertByte("Single step.", pathControllerGetDirection(0), Direction_right);
	}
	endTest();
}
