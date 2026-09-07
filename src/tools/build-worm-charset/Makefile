emulator := /Applications/vice-arm64-gtk3-3.6.1/bin/x64sc
debugger := /Applications/Retro\ Debugger/Retro\ Debugger.app/Contents/MacOS/Retro\ Debugger
oscar64 := ../../../../oscar64/bin/oscar64
inc := ../oscar64/include

prg := build/test.prg

src_files := \
	worm-char-layout.c \
	../../worm-char.c \

.DELETE_ON_ERROR:
$(prg): Makefile $(src_files)
	$(oscar64) -o=$(prg) -i=$(inc) -strict $(src_files) -e
