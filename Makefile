LIBS = game
CFLAGS = -g -Wall
CPPFLAGS =
LDFLAGS = -lgame

SRCS=$(wildcard *.c) # tous les .c
DEPS=$(SRCS:.c=.d)

all: libgame.a test_piece1 test_game jeu_edition_1


libgame.a: piece.o game.o
	for i in $^ ; do \
		ar -rs $@ $$i ; \
	done

test_piece1: test_piece1.o
	$(CC) $^ -L. $(LDFLAGS)  -o $@

test_game: piece.c game.c test_game.c
	$(CC) $(CFLAGS) $^ -o $@


jeu_edition_1 : jeu_edition_1.c
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

%.d: %.c
	$(CC) -MM $(CPPFLAGS) $< > $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -f test_piece1 test_game
	rm -f $(DEPS) $(OBJS)  *~
