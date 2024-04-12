
CC?=gcc
CFLAGS=$(shell paste -sd " " compile_flags.txt)
LDFLAGS=-lm

PYTHON?=python3
SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=build/%.o)

SCRIPTS=$(wildcard scripts/*.py)
HEADERS=$(SCRIPTS:scripts/%.py=include/melisma/%.h)

.PHONY: clean

build/melisma: headers $(OBJ) gitignore
	$(CC) $(LDFLAGS) $(OBJ) -o $@

build/%.o: src/%.c
	mkdir -p build/
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

headers: $(HEADERS)

include/melisma/%.h: scripts/%.py
	$(PYTHON) $< $@

gitignore: .gitignore.header $(HEADERS)
	cat .gitignore.header > .gitignore
	echo $(HEADERS) | tr " " "\n" >> .gitignore

clean:
	rm -rf melisma build/ $(HEADERS) .gitignore

