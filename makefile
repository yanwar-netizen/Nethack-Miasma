CC = gcc
CFLAGS = -I$(IDIR) -lncursesw
IDIR  = ./include/
SRCDIR = ./src/
SOURCES = $(wildcard $(SRCDIR)*.c)

.PHONY: all clean run portable

all: clean Nethack-Miasma run

Nethack-Miasma:
	$(CC) $(SOURCES) -o $@ $(CFLAGS)

run:
	./Nethack-Miasma

clean:
	rm -f Nethack-Miasma Nethack-Miasma.tar.gz

portable: clean Nethack-Miasma
	mkdir -p Nethack-Miasma-Release
	cp Nethack-Miasma Nethack-Miasma-Release/
	tar -czf Nethack-Miasma.tar.gz Nethack-Miasma-Release
	rm -rf Nethack-Miasma-Release
