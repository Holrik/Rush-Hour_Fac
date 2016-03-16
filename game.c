#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
#include "mygame.h"
#include "game.h"

/**
 * @file game.c
 *
 * @brief This file describes the board of a rush-our game, the state of a game and all functions needed to manipulate it.
 **/


/**
 * @struct game_s
 * @brief The state of the game is described by the position of the pieces (i.e. vehicles) on the board and the number of moves since the beginning of the game.
 *
 * The game board is a 6*6 grid. The lower left corner has coordinates (0,0).
 * The piece number 0 represents the "red car" that needs to be moved away from the parking.
 * Its initial position is (0,3).
 * A winning game (state) is when the red car touches the right border of the game board (i.e. when its position is (4,3)).
 *
 * cgame is a pointer toward a constant game.
 *
 **/
struct game_s{
  piece *pieces;
  int nb_pieces;
  int width ;
  int height ;
  int nb_moves;
};


/**
 * @brief Creates a new game given a starting position defined by a set of pieces.
 * The pieces of the created game are copies of the ones given as argument.
 * The number of moves of the game is set to 0.
 * @param nb_pieces number of pieces g
 * @param pieces array of pieces. The pieces given here are not modified by this function.
 * @return a pointer toward the generated game
 */
game new_game_hr (int nb_pieces, piece *pieces){
  // On alloue dynamiquement une structure game_s
  game g = malloc(sizeof(struct game_s)) ;
  // Il faut vérifier que l'allocation s'est faite correctement
  if (g == NULL){
    fprintf(stderr, "probleme d'allocation\n");
    return NULL ;
  }
  
  // On alloue dynamiquement un tableau de pièces
  g->pieces = malloc(nb_pieces * sizeof(piece)) ;
  // Il faut vérifier que l'allocation s'est faite correctement
  if (g->pieces == NULL){
    fprintf(stderr, "probleme d'allocation\n");
    return NULL ;
  }
  
  // On copie une à une les pièces données en paramètre vers la structure game_s
  for (int i = 0 ; i < nb_pieces ; i++) {
    *(g->pieces +i) = *(pieces+i) ;
  }
  
  g->nb_pieces = nb_pieces ;
  g->nb_moves = 0 ;
  return g ;
}

/**
 * @brief Destroys the game and free allocated memory
 * @param g the game to destroy
 */
void delete_game (game g){
  for (int i = 0 ; i < game_nb_pieces(g) ; i++)
    delete_piece(*(g->pieces+i)) ;
  free(g->pieces) ;
  free(g) ;
}

/**
 * @brief Clone the game dst into the game dst.
 * @param src the game to copy
 * @param dst the copied game.
 */
void copy_game (cgame src, game dst){
  // Si src et dst n'avaient pas le même nombre de pièces,
  if (game_nb_pieces(src) != game_nb_pieces(dst)) {
    int ecart_nb_pieces = game_nb_pieces(src) - game_nb_pieces(dst);
    int nb_pieces = game_nb_pieces(dst);
    
    // Si dst est plus grand que src, on supprime les pièces en trop,
    for (int i = 0 ; i < -ecart_nb_pieces ; i++){
      delete_piece(*(dst->pieces + nb_pieces + i));
    }
		
    // et on réalloue de la mémoire de la taille de src pour copier ses pièces.
    dst->pieces = (piece*) realloc(dst->pieces , game_nb_pieces(src) * sizeof(piece)) ;
    // Il faut vérifier que l'allocation s'est faite correctement
    if (dst->pieces == NULL){
      fprintf(stderr, "probleme d'allocation\n");
      return ;
    }
		
    // Si dst était plus petit que src
    for (int i = 0 ; i < ecart_nb_pieces ; i++){
      *(dst->pieces + nb_pieces + i) = new_piece(0, 0, 1, 1, true, true);
    }
  }
  
  dst->nb_pieces = game_nb_pieces(src) ;
  dst->nb_moves = game_nb_moves(src) ;
  // On copie une à une les pièces données en paramètre vers la structure game_s
  for (int i = 0 ; i < game_nb_pieces(dst) ; i++) {
    copy_piece( game_piece(src, i) , *(dst->pieces+i) ) ;
  }
}


/**
 * @brief Return the number of pieces on the game board g
 */
int game_nb_pieces(cgame g){
  return g->nb_pieces ;
}


/**
 * @brief Return the piece of g with number bum
 * @param piece_num the num of the piece. This value must be between 0 and game_nb_pieces(g)-1.
 */
cpiece game_piece(cgame g, int piece_num){
  // Il faut vérifier que la pièce existe avant de la renvoyer
  if (piece_num >= game_nb_pieces(g) || piece_num < 0)
    return NULL ;
  return (cpiece) *(g->pieces + piece_num) ;
}


/**
 * @brief Test is the game is over (i.e. if the piece 0 has reached the exit).
 * @return true if the piece number 0 has coordinates (4,3)
 */
bool game_over_hr(cgame g){
  // A moins d'un bug, y vaut forcément 3, car la pièce est Horizontale et initialisée à x=0, y=3.
  return get_x(game_piece(g, 0)) == 4 ;
}


/**
 * @brief Tries to move the piece of number piece_num in direction d for distance cells.
 *
 * If the move is valid, then corresponding piece is moved, the number of moves of the game is incremented by distance and the returned value is true.
 * If the move is not valid, the game g remains unchanged and the function returns false.
 * A move is valid if:
 *   1) the piece stays in the game board,
 *   2) the direction is compatible is the type of the piece,
 *   3) the piece do not cross any other piece during its movement.
 * @param distance length of the move. This value must be strictly positive.
 * @param piece_num the number of the piece to move. This value must be between 0 and game_nb_pieces(g)-1.
 * @return true if the move is valid, false otherwise.
 */

static void  real_move(game g, int piece_num, dir d, int distance){
  move_piece((piece)game_piece(g, piece_num), d, distance) ;
  g->nb_moves += distance ;
}

static int end_target(int x, int y, int distance){
  return x+y+distance;
}

static int somme_target(cpiece p, int (*f)(cpiece p),int (*g)(cpiece p), int distance ) {
  if (g == NULL)
    return end_target(f(p), 0, distance);
  return end_target(f(p), g(p), distance);
}


bool static verification_one(game g, cpiece p, dir d, int distance){
  if (d == RIGHT) {
    if (somme_target(p, get_x, get_width, distance) >game_width(g)){
      return false ;
    }
  }else if (d==LEFT){
    if (somme_target(p, get_x, NULL, -distance)<0){
      return false;
    }
  }  else if (d == UP) {
    if (somme_target(p, get_y, get_height, distance) >game_width(g)){
      return false ;
    }
  } else { // d == DOWN
    if (somme_target(p, get_y, NULL, -distance)<0){
      return false ;
    }
  }
  return true; 
}

bool play_move(game g, int piece_num, dir d, int distance){
  if (distance < 1)
    return false ;

  cpiece p1 = game_piece(g, piece_num);
	
  if(!verification_one(g,p1,d,distance)){
    return false;
  }
  /*	
  // 1) Vérification que la pièce reste sur le plateau
  if (d == RIGHT) {
  if (get_x(game_piece(g, piece_num)) + get_width(game_piece(g, piece_num)) + distance >game_width(g) )
  return false ;
  } else if (d == LEFT) {
  if (get_x(game_piece(g, piece_num)) - distance < 0)
  return false ;
  } else if (d == UP) {
  if (get_y(game_piece(g, piece_num)) + get_height(game_piece(g, piece_num)) + distance > game_height(g))
  return false ;
  } else { // d == DOWN
  if (get_y(game_piece(g, piece_num)) - distance < 0)
  return false ;
  }
  */
  
  // 2) On vérifie que la direction est compatible

  // Si Droite ou Gauche, on vérifie horizontalement
  if(d == RIGHT || d == LEFT){
    if(!can_move_x(p1)){ 
      return false ;
    }
  // Sinon, verticalement
  // On suppose que la vérification des directions a été faite correctement
  } else {
    if(!can_move_y(p1)){
      return false ;
    }
  }
	
  /*if (is_horizontal(game_piece(g, piece_num))) {
    if (d != RIGHT && d != LEFT)
    return false ;
    } else {
    if (d != UP && d != DOWN)
    return false ;
    }*/
	
  // 3) Vérification des Intersections avec "bool intersect(cpiece p1, cpiece p2)"
  piece p = new_piece(0, 0, 1, 1, true, true) ;
  copy_piece(game_piece(g, piece_num), p) ;

  for (int j = 0; j < distance; j++) {
    // A chaque case traversée par la copie de notre pièce,
    move_piece(p, d, 1);
    int i = 0;
    while (i < game_nb_pieces(g)) {
      // On vérifie pour chaque pièce du jeu si elle intersect la copie
      if (intersect(p, game_piece(g, i)) && i != piece_num) {
	delete_piece(p) ;
	return false;
      }
      i++;
    }
  }


  delete_piece(p) ;
  real_move(g, piece_num, d, distance);
  return true ;
}

/**
 * @brief Return the number of moves this the beginning of the game g.
 * Remind that move of a single piece of k cells in a single direction counts for k.
 */
int game_nb_moves(cgame g){
  return g->nb_moves ;
}




///////////// version 2 /////////////////


game new_game (int width, int height, int nb_pieces, piece *pieces){
  // On alloue dynamiquement une structure game_s
  game g = malloc(sizeof(struct game_s)) ;
  // Il faut vérifier que l'allocation s'est faite correctement
  if (g == NULL){
    fprintf(stderr, "probleme d'allocation\n");
    return NULL ;
  }
  
  // On alloue dynamiquement un tableau de pièces
  g->pieces = malloc(nb_pieces * sizeof(piece)) ;
  // Il faut vérifier que l'allocation s'est faite correctement
  if (g->pieces == NULL){
    fprintf(stderr, "probleme d'allocation\n");
    return NULL ;
  }

  
  // On copie une à une les pièces données en paramètre vers la structure game_s
  for (int i = 0 ; i < nb_pieces ; i++) {
    *(g->pieces +i) = *(pieces+i) ;
  }
  g->nb_pieces = nb_pieces ;
  g->width = width ;
  g->height = height ;
  g->nb_moves = 0 ;
  return g ;
}


/**
 *@brief return the width of the grid
 */
int game_width(cgame g){
  return g->width ;
}

/**
 *@brief return the height of the grid
 */
int game_height(cgame g){
  return g->height ;
}

/**
 * @brief return the number of then piece located on this square (-1 if no piece is present)
 * @param game
 * @param x-coor of the square
 * @param y-coor of the square
 */
int game_square_piece (game g, int x, int y){
  piece p = new_piece(x, y, 1, 1, true, true) ;
  for (int i = 0 ; i < game_nb_pieces(g) ; i++) {
    if (intersect(p, game_piece(g, i))) { // on vérifie pour chaque pièce du jeu si elle intersect la copie
      delete_piece(p) ;
      return false;
    }
  }
  delete_piece(p) ;
  return true ;
}


bool game_over_ar(cgame g){
  return get_x(game_piece(g, 0)) == 1 && get_y(game_piece(g, 0))==0;
}

bool game_over(cgame g, int jeu){
  // jeu étant la valeur entrée par le joueur pour choisir le type de jeu,
  // Si jeu vaut 1 alors on lance le sélectionneur de Game Over du Rush-Hour
  // Sinon, si il vaut 0, on lance celui de l'Âne Rouge

  switch(jeu){
  case 1:
    return game_over_hr(g);
    break;

  case 0:
    return game_over_ar(g);
    break;
      
  default:
    printf("choix du jeu incorrect");
    return NULL ;
  }
}
