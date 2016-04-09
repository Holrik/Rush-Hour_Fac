#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "piece.h"
#include "game.h"
#include "gameover.h"

struct configuration_Du_Jeu{
  configuration pere ;
  game jeu_config ;
  configuration* fils ;
};

typedef struct configuration_Du_Jeu* configuration ;


static configuration configurationInitiale(game g) {
  configuration conf = malloc(sizeof(struct configuration_Du_Jeu));
  conf->pere = NULL ;
  conf->fils = NULL ;
  game tmp = new_game(game_width(g), game_height(g), 0, NULL) ;
  copy_game(g, tmp) ;
  conf->jeu_config = tmp ;
  return conf ;
}


int randomSolver(game g) {
  while (!gameover)
    play_move(g, rand()%game_nb_pieces(g), rand()%4, 1) ;
  return game_nb_moves(g);
}
