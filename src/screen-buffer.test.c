#include "screen.h"
#include <stdint.h>

// Buffer for testing.
uint8_t _screenChars[SCREEN_SIZE];
uint8_t _screenColors[SCREEN_SIZE];

uint8_t *const screenChars = _screenChars;
uint8_t *const screenColors = _screenColors;
