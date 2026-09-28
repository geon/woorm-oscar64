#include "controller.h"
#include "test/test.h"

void controllerTest()
{
	beginTest("PathController");
	{
		Direction path[] = {
			Direction_right,
		};
		pathControllerInit(0, path, sizeof(path));

		assertByte("Single step.", controllerAllGetDirection[ControllerName_path](0), Direction_right);
	}
	endTest();
}
