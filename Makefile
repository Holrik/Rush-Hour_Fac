ROOT = .
LIBS = game
LIBDIR = -L $(ROOT)
CFLAGS = -g -Wall
CPPFLAGS = -I$(ROOT)
LDFLAGS = -lgame

SRCS=$(wildcard *.c) # tous les .c
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)

all: libgame.a test_piece1 test_game jeu_rh_ar solver


libgame.a: piece.o game.o gameover.o
	for i in $^ ; do \
		ar -rs $@ $$i ; \
	done

test_piece1: test_piece1.o
	$(CC) $(CFLAGS) $^ $(LIBDIR) $(LDFLAGS)  -o $@

test_game: test_game.o 
	$(CC) $(CFLAGS) $^ $(LIBDIR) $(LDFLAGS) -o $@


jeu_rh_ar: jeu_rh_ar.c niveaux.o affichage.o
	$(CC) $(CFLAGS) $^ $(LIBDIR) $(LDFLAGS) -o $@


solver: solver.o niveaux.o affichage.o
	$(CC) $(CFLAGS) $^ $(LIBDIR) $(LDFLAGS) -o $@

%.d: %.c
	$(CC) -MM $(CPPFLAGS) $< > $@


-include $(DEPS)

.PHONY: clean test

test: libgame.a test_piece1 test_game
	./test_piece1
	./test_game

clean:
	rm -f test_piece1 test_game jeu_rh_ar solver
	rm -f libgame.a
	rm -f $(DEPS) $(OBJS)  *~
