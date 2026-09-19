#include "circular-buffer.test.h"
#include "coord.test.h"
#include "path-controller.test.h"
#include "test/test.h"
#include "worm.test.h"

int main()
{

	beforeTests();

	pathControllerTest();
	circularBufferTest();
	coordTest();
	wormTest();

	afterTests();

	return 0;
}
