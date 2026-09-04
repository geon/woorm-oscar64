#include "test/test.h"

int main()
{

	beforeTests();

	beginTest("Passing test.");
	{
		assertByte("Compare bytes.", 0x12, 0x12);
		assertWord("Compare word.", 0x1234, 0x1234);
	}
	endTest();

	afterTests();

	return 0;
}
