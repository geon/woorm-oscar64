#include "circular-buffer.test.h"
#include "controller.test.h"
#include "coord.test.h"
#include "test/test.h"

int main()
{

	beforeTests();

	controllerTest();
	circularBufferTest();
	coordTest();

	afterTests();

	return 0;
}
