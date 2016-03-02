CFLAGS = -g -Wall
CPPFLAGS =
LDFLAGS =

all: test_piece1 test_game


test_piece1: piece.c test_piece1.c
	gcc $(CFLAGS) $^ -o $@


test_game: piece.c game.c test_game.c
	gcc $(CFLAGS) $^ -o $@


#: piece.c game.c test_game.c
#	gcc $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	-rm -f test_piece1 test_game
