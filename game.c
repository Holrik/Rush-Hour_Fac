#include "piece.c"
#include "game.h"

/**
 * @file game.c
 *
 * @brief This file describes the board of a rush-our game, the state of a game and all functions needed to manipulate it.
 **/

 
#define TAILLE_PLATEAU 6

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
typedef struct game_s{
	piece *pieces ;
	int nb_pieces ;
	int nb_moves ;
}


/**
 * @brief Creates a new game given a starting position defined by a set of pieces.
 * The pieces of the created game are copies of the ones given as argument.
 * The number of moves of the game is set to 0.
 * @param nb_pieces number of pieces g
 * @param pieces array of pieces. The pieces given here are not modified by this function.
 * @return a pointer toward the generated game
 */
game new_game_hr (int nb_pieces, piece *pieces){
	game g = malloc(sizeof(struct game_s)) ; // On alloue dynamiquement une structure game_s
	g->pieces = malloc(nb_pieces * sizeof(piece)) ; // On alloue dynamiquement un tableau des pièces
	if (g == NULL || g->pieces == NULL){ // Il faut vérifier que les allocations se sont faites correctement
		fprintf(stderr, "probleme d'allocation\n");
		return NULL ;
	}
	for (int i = 0 ; i < nb_pieces ; i++) { // On copie une à une les pièces données en paramètre vers la structure game_s
		*(g->pieces +i) = *(pieces+i) ;
	}
	g->nb_pieces = 0 ;
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
	if (game_nb_pieces(src) != game_nb_pieces(dst)) { // Si src et dst n'avaient pas le même nombre de pièces, 
		dst->pieces = (piece*) realloc(dst->pieces , nb_pieces * sizeof(piece)) ; // alors on réalloue de la mémoire pour copier les pièces.
		while (dst->pieces == NULL){ // Il faut vérifier que l'allocation s'est faite correctement
			dst->pieces = (piece*) realloc(dst->pieces , nb_pieces * sizeof(piece)) ;
		}
	}
	dst->nb_pieces = game_nb_pieces(src) ;
	dst->nb_moves = game_nb_moves(src) ;
	for (int i = 0 ; i < nb_pieces ; i++) { // On copie une à une les pièces données en paramètre vers la structure game_s
		copy_piece( *(src->pieces +i) , *(dst->pieces+i) ) ;
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
	if (piece_num >= game_nb_pieces(g) || piece_num < 0)
		return NULL ;
	return (cpiece) *(g->pieces + piece_num) ;
}


/**
 * @brief Test is the game is over (i.e. if the piece 0 has reached the exit).
 * @return true if the piece number 0 has coordinates (4,3)
*/
bool game_over_hr(cgame g){
	return get_y(game_piece(g, 0)) == 4 ; // A moins d'un bug, x vaut forcément 3, car la pièce est Horizontale et initialisée à x=3, y=0.
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
bool play_move(game g, int piece_num, dir d, int distance){
	if (distance < 1)
		return false ;
	
	// 1) Vérification que la pièce reste sur le plateau
	if (dir == RIGHT)
		if (get_y(game_piece(g, piece_num)) + get_width(game_piece(g, piece_num)) + distance > TAILLE_PLATEAU)
			return false ;
	else if (dir == LEFT)
		if (get_y(game_piece(g, piece_num)) - distance < 0)
			return false ;
	else if (dir == DOWN)
		if (get_x(game_piece(g, piece_num)) + get_height(game_piece(g, piece_num)) + distance > TAILLE_PLATEAU)
			return false ;
	else // dir == UP
		if (get_x(game_piece(g, piece_num)) + distance < 0)
			return false ;
	
	// 2) On vérifie que la direction est compatible
	if (is_horizontal(game_piece(g, piece_num)))
		if (dir != RIGHT && dir != LEFT)
			return false ;
	else
		if (dir != UP && dir != DOWN)
			return false ;
	
	// 3) Vérification des Intersections avec "bool intersect(cpiece p1, cpiece p2)"
	piece p = malloc(sizeof(struct piece_s)); // On alloue dynamiquement une structure piece_s
	if (p == NULL){ // Il faut vérifier que l'allocation s'est faite correctement
		fprintf(stderr, "probleme d'allocation\n");
		return NULL ;
	}
	copy_piece(game_piece(g, piece_num), p) ;
	for (i = 0 ; i < distance ; i++) {
		move_piece(p, dir, 1) ; // A chaque case traversée par la copie de notre pièce,
		int i = 0;
		while (i < piece_num) { // on vérifie si elle intersect une autre pièce
			if (intersect(p, piece_num))
				return false ;
			i++ ;
		}
		i++ ; // On évite de vérifier si la copie croise la pièce dont elle est issue
		while (i < game_nb_pieces(g)) {
			if (intersect(p, piece_num))
				return false ;
			i++ ;
		}
	}
	delete_piece(p) ;
	// Après les 3 vérifications, si tout est bon, on déplace la pièce
	move_piece(game_piece(g, piece_num), dir, distance) ;
	return true ;
}

/**
 * @brief Return the number of moves this the beginning of the game g.
 * Remind that move of a single piece of k cells in a single direction counts for k.
 */
int game_nb_moves(cgame g){
	return g->nb_moves ;
}

#endif