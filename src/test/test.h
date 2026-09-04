#include <stdbool.h>
#include <stdint.h>

void beforeTests(void);
void afterTests(void);
void beginTest(const char *messageString);
void endTest(void);

void assertWord(const char *messageString, uint16_t result, uint16_t okValue);
void assertByte(const char *messageString, uint8_t result, uint8_t okValue);
void assertWordDecimal(const char *messageString, uint16_t result, uint16_t okValue);
void assertByteDecimal(const char *messageString, uint8_t result, uint8_t okValue);
void assertTrue(const char *messageString, bool success);
void assertIntDecimal(const char *messageString, int result, int okValue);

void fail(const char *messageString, const char *result, const char *okValue);
