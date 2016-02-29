CFLAGS = -g -Wall
CPPFLAGS =
LDFLAGS =

all: test_piece1 test_game
	make $^


test_piece1: piece.h piece.c test_piece1.c
	gcc $(CFLAGS) $^ -o $@


test_game: piece.h piece.c game.h game.c test_game.c
	gcc $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	-rm -f test_piece1 test_game
