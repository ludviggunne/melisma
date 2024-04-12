
CC?=gcc
CFLAGS=$(shell paste -sd " " compile_flags.txt)

SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=build/%.o)

.PHONY: clean

build/melisma: $(OBJ)
	$(CC) $(OBJ) -o $@

build/%.o: src/%.c
	mkdir -p build/
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf melisma build/

