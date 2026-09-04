#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char *lastMessageStringPointer = NULL;

void beforeTests(void)
{
	printf("Running tests:\n");
	printf("----------------------------------------\n");
}

void afterTests(void)
{
	// Display test result.
	printf("----------------------------------------\n");
	printf("All tests passed.\n");

	exit(0);
}

void fail(const char *messageString, const char *result, const char *okValue)
{
	printf("========================================\n");
	printf("Test failed:\n");
	printf("* %s\n", lastMessageStringPointer);
	printf("Assertion: %s\n", messageString);
	printf("Expected:  %s\n", okValue);
	printf("Actual:    %s\n", result);

	exit(1);
}

void beginTest(const char *messageString)
{
	lastMessageStringPointer = messageString;
}

void endTest(void)
{
	printf("* %s\n", lastMessageStringPointer);
}

void assertWord(const char *messageString, uint16_t result, uint16_t okValue)
{
	if (result != okValue)
	{
		char resultBuffer[7], okBuffer[7]; // 6 chars + null
		sprintf(resultBuffer, "0x%.4x", result);
		sprintf(okBuffer, "0x%.4x", okValue);
		fail(messageString, resultBuffer, okBuffer);
	}
}

void assertByte(const char *messageString, uint8_t result, uint8_t okValue)
{
	if (result != okValue)
	{
		char resultBuffer[5], okBuffer[5]; // 4 chars + null
		sprintf(resultBuffer, "0x%.2x", result);
		sprintf(okBuffer, "0x%.2x", okValue);
		fail(messageString, resultBuffer, okBuffer);
	}
}

void assertWordDecimal(const char *messageString, uint16_t result, uint16_t okValue)
{
	if (result != okValue)
	{
		char resultBuffer[6], okBuffer[6]; // 5 chars + null
		sprintf(resultBuffer, "%*i", 5, result);
		sprintf(okBuffer, "%*i", 5, okValue);
		fail(messageString, resultBuffer, okBuffer);
	}
}

void assertByteDecimal(const char *messageString, uint8_t result, uint8_t okValue)
{
	if (result != okValue)
	{
		char resultBuffer[4], okBuffer[4]; // 3 chars + null
		sprintf(resultBuffer, "%*i", 3, result);
		sprintf(okBuffer, "%*i", 3, okValue);
		fail(messageString, resultBuffer, okBuffer);
	}
}

void assertTrue(const char *messageString, bool success)
{
	if (!success)
	{
		fail(messageString, "false", "true");
	}
}

void assertIntDecimal(const char *messageString, int result, int okValue)
{
	if (result != okValue)
	{
		char resultBuffer[8], okBuffer[8]; // 7 chars + null
		sprintf(resultBuffer, "%*i", 7, result);
		sprintf(okBuffer, "%*i", 7, okValue);
		fail(messageString, resultBuffer, okBuffer);
	}
}
