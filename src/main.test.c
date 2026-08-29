#include "circular-buffer.test.h"
#include "path-controller.test.h"
#include "test/test.h"

int main()
{

	beforeTests();

	pathControllerTest();
	circularBufferTest();

	afterTests();

	return 0;
}
