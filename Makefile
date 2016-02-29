CFLAGS = -g -Wall
CPPFLAGS =
LDFLAGS =

all: test_piece1 test_game
	make $^

test_piece1: piece.h piece.c test_piece1.c
	gcc $(CFLAGS) $^ -o $@


test_game: piece.h piece.c game.h test_piece1.c
	gcc $(CFLAGS) $^ -o $@


clean:
	-rm -f test_piece1 test_game
