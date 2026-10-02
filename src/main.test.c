#include "circular-buffer.test.h"
#include "controller.test.h"
#include "test/test.h"

int main()
{

	beforeTests();

	controllerTest();
	circularBufferTest();

	afterTests();

	return 0;
}
