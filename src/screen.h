#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 25
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

extern uint8_t *const screenChars;
extern uint8_t *const screenColors;

void screenClear(uint8_t tile);

#endif
