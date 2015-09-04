HEADER_FILES=aeon.h
SOURCE_FILES=aeon.c test.c
GCC_OPTIONS=-lfreetype $(shell freetype-config --cflags) -lm

test: $(HEADER_FILES) $(SOURCE_FILES)
	gcc $(SOURCE_FILES) $(GCC_OPTIONS) -o bin/test
