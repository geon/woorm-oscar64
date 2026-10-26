#include "controller.h"
#include "test/test.h"

void controllerTest()
{
	beginTest("PathController");
	{
		Direction path[] = {
			Direction_right,
		};
		PathController pathController;
		pathControllerInit(&pathController, path, sizeof(path));

		assertByte("Single step.", pathControllerGetDirection(&pathController), Direction_right);
	}
	endTest();
}
