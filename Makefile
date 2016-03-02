CFLAGS = -g -Wall
CPPFLAGS =
LDFLAGS =

all: test_piece1 test_game jeu_edition_1


test_piece1: piece.c test_piece1.c
	gcc $(CFLAGS) $^ -o $@


test_game: piece.c game.c test_game.c
	gcc $(CFLAGS) $^ -o $@


jeu_edition_1 : piece.c game.c jeu_edition_1.c
	gcc $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	-rm -f test_piece1 test_game
