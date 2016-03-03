ROOT = .
LIBS = game
LIBDIR = -L $(ROOT)
CFLAGS = -g -Wall
CPPFLAGS = -I$(ROOT)
LDFLAGS = -lgame

SRCS=$(wildcard *.c) # tous les .c
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)

all: libgame.a test_piece1 test_game rush-hour_1


libgame.a: piece.o game.o
	for i in $^ ; do \
		ar -rs $@ $$i ; \
	done

test_piece1: test_piece1.o
	$(CC) $^ $(LIBDIR) $(LDFLAGS)  -o $@

test_game: test_game.o
	$(CC) $^ $(LIBDIR) $(LDFLAGS) -o $@


rush-hour_1 : rush-hour_1.c niveaux.o affichage.o
	$(CC) $(CFLAGS) $^ $(LIBDIR) $(LDFLAGS) -o $@

%.d: %.c
	$(CC) -MM $(CPPFLAGS) $< > $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -f test_piece1 test_game rush-hour_1
	rm -f libgame.a
	rm -f $(DEPS) $(OBJS)  *~
