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
		PathController x;
		pathControllerInit(&x, path, sizeof(path));

		assertByte("Single step.", pathControllerGetDirection(&x), Direction_right);
		assertByte("Multiple steps.", pathControllerGetDirection(&x), Direction_left);
		assertByte("Loop steps.", pathControllerGetDirection(&x), Direction_right);
	}
	endTest();
}
