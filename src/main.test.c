#include "circular-buffer.test.h"
#include "controller.test.h"
#include "coord.test.h"
#include "test/test.h"
#include "worm.test.h"

int main()
{

	beforeTests();

	controllerTest();
	circularBufferTest();
	coordTest();
	wormTest();

	afterTests();

	return 0;
}
