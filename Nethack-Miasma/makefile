CC = gcc
CFLAGS = -lncursesw -I$(IDIR)
IDIR  = ./include/
SRCDIR = ./src/
SOURCES = $(SRCDIR)*.c
all: Nethack-Miasma run clean
Nethack-Miasma:
	$(CC) $(SOURCES) -o $@ $(CFLAGS)
run:
	./Nethack-Miasma
clean:
	rm -f Nethack-Miasma