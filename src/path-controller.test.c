#include "path-controller.h"
#include "test/test.h"

void pathControllerTest()
{
	beginTest("PathController");
	{
		Direction path[] = {
			Direction_right,
		};
		PathController x;
		pathControllerInit(&x, path, sizeof(path));

		assertByte("Single step.", pathControllerGetDirection(&x), Direction_right);
	}
	endTest();
}
