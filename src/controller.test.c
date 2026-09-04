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
		PathController pathController;
		pathControllerInit(&pathController, path, sizeof(path));

		assertByte("Single step.", pathControllerGetDirection(&pathController), Direction_right);
		assertByte("Multiple steps.", pathControllerGetDirection(&pathController), Direction_left);
		assertByte("Loop steps.", pathControllerGetDirection(&pathController), Direction_right);
	}
	endTest();
}
