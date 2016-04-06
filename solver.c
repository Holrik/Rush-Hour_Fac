#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "piece.h"
#include "game.h"
#include "gameover.h"

struct instance_Du_Jeu{
  instance pere ;
  game jeu_instance ;
  instance* fils ;
};

typedef struct instance_Du_Jeu* instance ;


static instance instanceInitiale(game g) {
  instance ins = malloc(sizeof(struct instance_Du_Jeu));
  ins->pere = NULL ;
  ins->fils = NULL ;
  game tmp = new_game(game_width(g), game_height(g), 0, NULL) ;
  copy_game(g, tmp) ;
  ins->jeu_instance = tmp ;
  return ins ;
}
