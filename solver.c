#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "piece.h"
#include "game.h"
#include "gameover.h"
#include "affichage.h"
#include "niveaux.h"

// Cell of a tree : Each cell has 1 père(father) ans nb_fils fils(sons), and corresponds to one particular configuration of a game
// (this config being from the game given as a parameter to the solver)
typedef struct configuration_Du_Jeu* config ;
struct configuration_Du_Jeu{
  config pere ;
  int game_type ;
  game jeu_config ;
};


// Array of the moves already played by the solver
// c_played_size is the length of the full array,
// and c_played_actual is the last added config in the array
config* c_played_moves ;
int c_played_size ;
int c_played_actual ;

// find_shortest_path defines and uses it and solver_shortest_path uses it too
int nb_moves ;


// Random mode of the solver : Should work somehow but the code's performance is disgusting
int random_Solver(game g, int game_type) {
  while (!game_over(g, game_type))
    play_move(g, rand()%game_nb_pieces(g), rand()%4, 1) ;
  return game_nb_moves(g);
}


static int config_game_type(config c) {
  return c->game_type ;
}

static cgame config_game(config c) {
  return (cgame)c->jeu_config ;
}

// Checks if the c parameter is in a game_over state
static bool has_game_over(config c) {
  return game_over(c->jeu_config, config_game_type(c));
}


// Creates a new config with the game g as jeu_config
static config new_config(cgame g, int game_type) {
  config c = malloc(sizeof(struct configuration_Du_Jeu)) ;
  // If malloc didn't work correctly
  if (c == NULL)
    return NULL ;
  
  c->pere = NULL ;
  c->game_type = game_type ;
  
  game tmp = new_game(game_width(g), game_height(g), 0, NULL) ;
  copy_game(g, tmp) ;
  c->jeu_config = tmp ;
  
  return c ;
}

// Deletes the config given as a parameter and all the configs under it, in recursion with delete_config_Array
static void delete_config(config c) {
  if (c == NULL)
    return;
  
  delete_game(c->jeu_config) ;
  
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
    c_played_size = c_played_size*2 +1 ;
    c_played_moves = realloc(c_played_moves, c_played_size*sizeof(config)) ;
  }
}

static void c_played_add_c(config c) {
  c_played_resize();
  *(c_played_moves + c_played_actual) = c ;
  c_played_actual++ ;
}

// Compares 2 pieces and checks if they are similar
// /!\ No need to compare move_x and move_y, since they are determined by the game_type and by the height and width for the RH, and are always true for the AR
static bool pieces_are_equals(cpiece p1, cpiece p2) {
  return get_x(p1) == get_x(p2)
    && get_y(p1) == get_y(p2)
    && get_height(p1) == get_height(p2)
    && get_width(p1) == get_width(p2) ;
}

// Compares 2 game states and checks if the pieces configuration is similar
// /!\ The height and width of the game supposed similar for the solver, we don't verify it for efficiency purposes
//     We don't need nb_moves either
static bool games_are_equals(cgame g1, cgame g2) {
  if (g1 == NULL) {
    return g2 == NULL ;
  }
  if (g2 == NULL)
    return false ;
  int nb_p = game_nb_pieces(g1) ;
  if (nb_p != game_nb_pieces(g2))
    return false ;
  // We do not need to compare all pieces at complexity n², since only few pieces from AR can exchange place
  // TO IMPROVE
  for (int i = 0 ; i < nb_p ; i++) {
    if(!pieces_are_equals(game_piece(g1, i), game_piece(g2, i)))
      return false ;
  }
  return true ;
}


// We determine the possible fils of c depending on each piece of the game and its movements
// And we check after each movement if the state of the new game is different of moves already done
static void shortest_determine_fils(config c) {
  game g = c->jeu_config ;
  for(int i = 0 ; i < game_nb_pieces(g) ; i++) {
    // We do it once per direction, the directions being defined from 0 to 3
    for( int d = 0 ; d < 4 ; d++) {
      game g_tmp = new_game(game_width(g), game_height(g), 0, NULL) ;
      copy_game(g, g_tmp) ;
	  // b == true if the piece has been moved
      bool b = play_move(g_tmp, i, d, 1);
	  // We check that the move played doesn't equal the moves previously played
      for (int i = 0 ; b && i < c_played_actual ; i++) {
        b = b && !(games_are_equals( g_tmp, config_game(*(c_played_moves +i)) )) ;
      }
	  // If the move has never been played, we add it to the played_moves and put c as it's previous configuration(pere/dad)
      if (b) {
        config c_tmp = new_config(g_tmp, config_game_type(c));
        c_played_add_c(c_tmp) ;
        c_tmp->pere = c ;
      }
      delete_game(g_tmp);
    }
  }
}


config* find_shortest_path(void) {
  // Variable that points to the next config to read in c_played_moves.
  int i_actual = 0 ;
  // Until we find a game_over or there is no more playable move, we search the next possible moves
  while(i_actual < c_played_actual && *(c_played_moves +i_actual) != NULL
      && !has_game_over(*(c_played_moves +i_actual))) {
    shortest_determine_fils(*(c_played_moves +i_actual)) ;
    i_actual++ ;
  }
  if (i_actual >= c_played_actual || *(c_played_moves +i_actual) == NULL)
    return NULL;
  
  config c_tmp = *(c_played_moves +i_actual) ;
  nb_moves = game_nb_moves(config_game(c_tmp)) ;
  config* path_taken = new_config_Array(nb_moves) ;
  for (int i = nb_moves ; i >= 0 ; i--) {
    *(path_taken + i) = c_tmp ;
    c_tmp = c_tmp->pere ;
  }
  // At the end of this loop, c_tmp = NULL
  return path_taken ;
}


int solver_shortest_path(game g, int game_type) {
  c_played_moves = new_config_Array(100) ;
  c_played_add_c(new_config(g, game_type));
  
  config* c_resultat = find_shortest_path() ;

  //afficher(config_game(*(c_resultat +nb_moves)), game_type);
  
  delete_config_Array(c_played_moves, c_played_size);
  free(c_resultat);
  return nb_moves+1 ;
}


int main(int argc, char *argv[]){
  if (argc != 3) {
    printf("Mauvais nombre d'arguments : Il en faut deux !\n");
    return EXIT_FAILURE ;
  }
  
  char* typeJeu = argv[1];

  if (strcmp(typeJeu, "a") && strcmp(typeJeu, "r")) {
    printf("Le type de jeu entré est incorrect\n");
    return EXIT_FAILURE ;
  }

  int jeu = 1;
  if (!strcmp(typeJeu, "a")) {
    jeu = 0;
  }
  
  game g = new_game_from_file(typeJeu, argv[2]);

  printf("%d\n\n", solver_shortest_path(g, jeu));
  delete_game(g);
  return EXIT_SUCCESS ;
  
}
