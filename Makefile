
CC?=gcc
CFLAGS=$(shell paste -sd " " compile_flags.txt)
LDFLAGS=-lm

SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=build/%.o)

.PHONY: clean

build/melisma: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

build/%.o: src/%.c
	mkdir -p build/
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf melisma build/

