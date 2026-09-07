emulator := /Applications/vice-arm64-gtk3-3.6.1/bin/x64sc
debugger := /Applications/Retro\ Debugger/Retro\ Debugger.app/Contents/MacOS/Retro\ Debugger
oscar64 := ../oscar64/bin/oscar64
inc := ../oscar64/include

prg := build/woorm.prg

src_files := \
	src/main.c \
	src/screen-buffer.c \
	src/screen.c \
	src/screen.h \
	src/direction.c \
	src/direction.h \
	src/path-controller.c \
	src/path-controller.h \
	src/title-screen.c \
	src/title-screen.h \
	src/worm.c \
	src/worm.h \
	src/circular-buffer.c \
	src/circular-buffer.h \
	src/worm-char.c \
	src/worm-char.h \

.PHONY: verify
verify: clean test $(prg)

.DELETE_ON_ERROR:
$(prg): Makefile $(src_files) src/worm-charset.inc
	$(oscar64) -o=$(prg) -i=$(inc) -strict $(src_files)

.PHONY: clean
clean:
	rm -f $(prg)
	make --makefile=test-makefile clean

.PHONY: run
run: $(prg)
	$(emulator) $(prg) 1> /dev/null

.PHONY: test
test:
	make --makefile=test-makefile
