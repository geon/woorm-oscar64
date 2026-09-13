#include "path-controller.h"
#include "test/test.h"

void pathControllerTest()
{
	beginTest("PathController");
	{
		Direction path[] = {
			Direction_right,
			Direction_left,
		};
		pathControllerInit(0, path, sizeof(path));

		assertByte("Single step.", pathControllerGetDirection(0), Direction_right);
		assertByte("Multiple steps.", pathControllerGetDirection(0), Direction_left);
	}
	endTest();
}
