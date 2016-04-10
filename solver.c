#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "piece.h"
#include "game.h"
#include "gameover.h"


// Cell of a tree : Each cell has 1 père(father) ans nb_fils fils(sons), and corresponds to one particular configuration of a game
// (this config being from the game given as a parameter to the solver)
struct configuration_Du_Jeu{
  config pere ;
  game jeu_config ;
  int nb_fils ;
  config* fils ;
};
typedef struct configuration_Du_Jeu* config ;


// Random mode of the solver : Should work somehow but the code's performance is disgusting
int random_Solver(game g) {
  while (!gameover)
    play_move(g, rand()%game_nb_pieces(g), rand()%4, 1) ;
  return game_nb_moves(g);
}


static int config_nb_fils(config c) {
  return c->nb_fils ;
}

// Creates a new config with the game g as jeu_config
static config new_config(cgame g) {
  config c = malloc(sizeof(struct configuration_Du_Jeu)) ;
  // If malloc didn't work correctly
  if (c == NULL)
    return NULL ;
  
  c->pere = NULL ;
  c->fils = NULL ;
  game tmp = new_game(game_width(g), game_height(g), 0, NULL) ;
  copy_game(g, tmp) ;
  c->jeu_config = tmp ;
  free(tmp);
  return c ;
}

// Deletes the config given as a parameter and all the configs under it, in recursion
static void delete_config(config c) {
  if (c == NULL)
    return;
  
  delete_game(c->jeu_config) ;
  
  if (c->fils != NULL) {
    for (int i = 0 ; i < config_nb_fils(c) ; i++) {
      delete_config(*(c->fils +i)) ;
    }
	free(c->fils);
  }
  free(c);
}

// Constructs a config array with only one config inside, being the one created from the game parameter
static config* config_Array_Initial(cgame g) {
  config* c_array = malloc(sizeof(configuration)) ;
  // If malloc didn't work correctly
  if (c_array == NULL)
    return NULL ;
  
  *c_array = new_config(g) ;
  return c_array ;
}


/* 
 * TODO - By rounds, take the config*, analyse if one of the configs has a Game Over :
 *   -- If yes, return the number of moves (or even the moves themselves) required.
 *   -- If no, find all the possible fils of the actual configs in config*, put them on its place in the config*, and do it again, until we get to a Game Over
*/
int solver(game g) {
  
}