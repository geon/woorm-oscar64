#include "circular-buffer.test.h"
#include "coord.test.h"
#include "path-controller.test.h"
#include "test/test.h"

int main()
{

	beforeTests();

	pathControllerTest();
	circularBufferTest();
	coordTest();

	afterTests();

	return 0;
}
