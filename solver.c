#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "piece.h"
#include "game.h"
#include "gameover.h"

config* c_played_moves ;
int c_played_size ;
int c_played_actual ;

// Cell of a tree : Each cell has 1 père(father) ans nb_fils fils(sons), and corresponds to one particular configuration of a game
// (this config being from the game given as a parameter to the solver)
struct configuration_Du_Jeu{
  config pere ;
  int game_type ;
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

static int config_game_type(config c) {
  return c->game_type ;
}

// Checks if the c parameter is in a game_over state
static bool has_game_over(config c) {
  return game_over(c->jeu_config, game_type(c));
}


// Creates a new config with the game g as jeu_config
static config new_config(cgame g, int game_type) {
  config c = malloc(sizeof(struct configuration_Du_Jeu)) ;
  // If malloc didn't work correctly
  if (c == NULL)
    return NULL ;
  
  c->pere = NULL ;
  c->fils = NULL ;
  c->game_type = game_type ;
  
  game tmp = new_game(game_width(g), game_height(g), 0, NULL) ;
  copy_game(g, tmp) ;
  c->jeu_config = tmp ;
  free(tmp);
  
  return c ;
}

// Deletes the config given as a parameter and all the configs under it, in recursion with delete_config_Array
static void delete_config(config c) {
  if (c == NULL)
    return;
  
  delete_game(c->jeu_config) ;

  // Delete the fils array
  delete_config_Array(c->fils, config_nb_fils(c));
  
  free(c);
}

// Constructs a config array with only one config inside, being the one created from the game parameter
static config* new_config_Array(int taille) {
  config* c_array = malloc(taille*sizeof(config)) ;
  // If malloc didn't work correctly
  if (c_array == NULL)
    return NULL ;
  
  return c_array ;
}

// Deletes the config_Array given as a parameter and all the configs contained, in recursion with delete_config_Array
static void delete_config_Array(config* c_array, int taille) {
  if(c_array == NULL)
    return;
  for (int i = 0 ; i < taille ; i++) {
     delete_config(*(c_array +i)) ;
  }
  free(c_array);
}

// Resizes c_played_moves if the number of configs inside is equal its size
static void c_played_resize() {
  if (c_played_actual == c_played_size) {
    c_played_size *= 2 ;
    c_played_moves = realloc(c_played_moves, c_played_size*sizeof(config)) ;
  }
}

static void c_played_add_c(config c) {
  c_played_resize();
  *(c_played_moves + c_played_actual) = c ;
}

static cgame config_game(config c) {
  return (cgame)c->jeu_config ;
}


// We determine the possible fils depending on each piece of the game and its movements
// And we check after each movement if the state of the new game is different of the original one
// TODOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
static void determine_fils(config c) {
  game g = c->jeu_config ;
  for(int i = 0 ; i < game_nb_pieces(g) ; i++) {
    game g_tmp1 = new_game(game_width(g), game_height(g), 0, NULL) ;
    game g_tmp2 = new_game(game_width(g), game_height(g), 0, NULL) ;
    game g_tmp3 = new_game(game_width(g), game_height(g), 0, NULL) ;
    game g_tmp4 = new_game(game_width(g), game_height(g), 0, NULL) ;
    copy_game(g, g_tmp1) ;
    copy_game(g, g_tmp2) ;
    copy_game(g, g_tmp3) ;
    copy_game(g, g_tmp4) ;
    bool b1 = play_move(g_tmp1, i, UP, 1);
    bool b2 = play_move(g_tmp2, i, LEFT, 1);
    bool b3 = play_move(g_tmp3, i, DOWN, 1);
    bool b4 = play_move(g_tmp4, i, RIGHT, 1);
  }
}

// TODOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
/* 
 * TODO :
 * - Take the config, check if the move has been done already :
 *   -- If yes, quit this branch.
 * --------- Move this ^ part to determine_fils in the determination of the valids fils
 *
 * - Check if it has a Game Over :
 *   -- If yes, return the moves required.
 *   -- If no, check its fils
*/
static config* find_best_path(config c, int nb_moves) {
  for (int i = 0 ; i < c_played_actual ; i++) {
    ////////////////////////////////////////// Need to create function game_compare
    if (game_compare(config_game(c), config_game(*(c_played_moves +i)) ))
      return NULL;
  }
  c_played_add_c(c);
  
  if (has_game_over(c))
    return new_config_Array(nb_moves+1) ;
  determine_fils(c);
}

// TODOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
// TODO - Initialize c_old_size to 0
int solver(game g, int game_type) {
  c_played_moves = new_config_Array(100) ;
  config c_actuelle = new_config(g, game_type) ;
  
}
