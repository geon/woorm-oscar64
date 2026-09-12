#include "direction.h"
#include "level.h"
#include "screen.h"
#include "title-screen.h"
#include <c64/cia.h>
#include <c64/memmap.h>
#include <c64/vic.h>
#include <stdint.h>
#include <stdio.h>

// Config the regions and sections.

// Create a "lower" region before the charset.
#pragma region( lower, 0x0a00, 0x2000, , , {code, data} )
// Create a "charset" section.
#pragma section(charset, 0)
// Create a "charset" region to contain the "charset" section.
// Note: The charset and screen must be in the same 16k vic bank.
#pragma region( charset, 0x2000, 0x2800, , , {charset} )
// Adjust the "main" region to start after the "charset" region.
#pragma region( main, 0x2800, 0xa000, , , {code, data, bss, heap, stack} )

// Store the charset in the "charset" section.
#pragma data(charset)
char charset[2048] = {
#include "worm-charset.inc"
};
// End "charset" section.
#pragma data(data)

const uint8_t playerColors[4] = {
	VCOL_CYAN,
	VCOL_GREEN,
	VCOL_YELLOW,
	VCOL_RED,
};

void setup(void)
{
	// Clear interrupts set by basic/kernal, or it will crash when it is unmapped
	cia_init();
	// Unmap basic/kernal/rom-charsets.
	mmap_set(MMAP_NO_ROM);
	vic_setmode(VICM_TEXT_MC, screenChars, charset);

	vic.color_border = VCOL_BLACK;
	vic.color_back = VCOL_BLACK;

	vic.color_back1 = VCOL_WHITE;
	vic.color_back2 = VCOL_BROWN;
}

int main()
{
	setup();
	screenClear(0);
	titleScreen();

	return 0;
}
