#include "controller.h"
#include "test/test.h"

void controllerTest()
{
	beginTest("Path Controller");
	{
		Direction path[] = {
			Direction_right,
			Direction_left,
		};
		pathControllerInit(0, path, sizeof(path));

		assertByte("Single step.", controllerAllGetDirection[ControllerName_path](0), Direction_right);
		assertByte("Multiple steps.", controllerAllGetDirection[ControllerName_path](0), Direction_left);
		assertByte("Loop steps.", controllerAllGetDirection[ControllerName_path](0), Direction_right);
	}
	endTest();
}
