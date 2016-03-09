#include <stdlib.h>
#include <stdio.h>
#include "piece.h"


/**
 * @file piece.c
 *
 * @brief A piece represents a vehicle placed on the board of the game rush-hour.
 *
 **/

/**
 * @struct piece_s
 * @brief A piece represents a vehicle of the game rush hour placed on the board.
 * A piece is characterized by its position, its shape and its ability to move vertically or horizontally.
 *
 * piece is a pointer to the structure that describes a vehicle on the board.
 *
 * cpiece is a pointer toward a constant piece.
 */
struct piece_s {
  int x ;
  int y ;
  int width;
  int height;
  bool move_x;
  bool move_y;
};

/**
 * @enum dir_e
 * @brief The enumeration of possible directions of a move
 * typedef enum dir_e {UP, LEFT, DOWN, RIGHT} dir;
 */

/**
 * @brief Creates a new piece.
 * @param x,y coordinates of the lower-left corner (Remark: x-axe is oriented from bottom to top and y-axe is oriented from left to right).
 * @param small indicates if the vehicle is of size 2 (small=true) or 3 (small=false)
 * @param horizontal indicates whether the vehicle can move horizontally or vertically
 * @return a pointer toward the generated piece
 */

piece new_piece_rh (int x, int y, bool small, bool horizontal){
  // V1
  /*
	piece p = malloc(sizeof(struct piece_s)); // On alloue dynamiquement une structure piece_s
	
	if (p == NULL){ // Il faut vérifier que l'allocation s'est faite correctement
		fprintf(stderr, "probleme d'allocation\n");
		return NULL ;
	}
	
	// Tout s'est bien passé, on définit donc la pièce
	p->x = x ;
	p->y = y ;
	p->small = small;
	p->horizontal = horizontal;
*/	
	return NULL ;

}


/**
 * @brief Destroys the piece and frees allocated memory
 * @param p the piece to destroy
 */
void delete_piece (piece p){ // Supprimer la pièce
	free(p) ;
}

/**
 * @brief Clones the piece src into the piece dst.
 * @param[out] src the piece to copy
 * @param[in]  dst the copied piece
 */
void copy_piece (cpiece src, piece dst){ // On copie les données qui définissent la pièce
  dst->x  = get_x(src) ;
  dst->y  = get_y(src) ;
  dst->width  = get_width(src) ;
  dst->height = get_height(src);
  dst->move_x = can_move_x(src);
  dst->move_y = can_move_y(src);
}

/**
 *
 * @brief Tries to move the piece p in direction d with distance steps.
 * If the direction is LEFT or RIGHT and the piece is not allowed to move horizontally, then the piece is not moved.
 * Similarly, if the direction is UP or DOWN and the piece is not allowed to move vertically, then the piece is not moved.
 *
 */
void move_piece (piece p, dir d, int distance){ // On suppose que rien ne bloque la pièce

  // On vérifie d'abord la direction entrée
  if(d == LEFT){
    if(can_move_x(p)){ // Ensuite si la pièce peut effectuer ce mouvement
      p->x -= distance;
    }
  } else if(d == RIGHT){
    if(can_move_x(p)){
      p->x += distance;
    }
  } else if(d == UP){
    if(can_move_y(p)){
      p->x += distance;
    }
  } else if(d == DOWN){
    if(can_move_y(p)){
      p->x -= distance;
    }
  }
  
}

/**
 * @brief tests whether or not pieces p1 and p2 overlap.
 * @return true if pieces p1 and p2 have at least one cell in common and false otherwise.
 */
bool intersect(cpiece p1, cpiece p2){

  for(int y1 = get_y(p1); y1 < get_y(p1) + get_height(p1); y1++){ // y de p1

    for(int x1 = get_x(p1); x1 < get_x(p1) + get_width(p1); x1++){ // x de p1

      for(int y2 = get_y(p2); y2 < get_y(p2) + get_height(p2); y2++){ // y de p2

	for(int x2 = get_x(p2); x2 < get_x(p2) + get_width(p2); x2++){ // x de p2

	  if(x1 == x2 && y1 == y2){
	    return false;
	  }
	  
	}
      }
    }
  }

  return true;

  // V1
  /*
	int size_p1 = 2 ;
	int size_p2 = 2 ;
	if (!p1->small)
		size_p1 = 3 ;
	if (!p2->small)
		size_p2 = 3 ;
	if (is_horizontal(p1)) {
		if (is_horizontal(p2)) { // Si les 2 sont Horizontales, on vérifie si elles se croisent
			if (get_y(p1) != get_y(p2)) // Leurs coordonnées verticales
				return false ;
			if (get_x(p1) == get_x(p2)) // Leurs coordonnées horizontales
				return true ;
			if (get_x(p1) > get_x(p2)) 
				return get_x(p1) < get_x(p2) + size_p2 ; // On vérifie que le point de gauche de p1 est contenu dans p2
			return get_x(p1) + size_p1 > get_x(p2) ; // On vérifie que le point de gauche de p2 est contenu dans p1
		} else { // p1 horizontal, p2 verticalbool can_move_x(cpiece p);
bool can_move_y(cpiece p);
			return get_y(p1) >= get_y(p2) && get_y(p1) < get_y(p2) + size_p2 // On vérifie que l'ordonnée du point du bas de p1 est contenue dans p2,
				&& get_x(p2) >= get_x(p1) && get_x(p2) < get_x(p1) + size_p1 ; // et que l'abscisse du point de gauche de p2 est contenue dans p1
		}
	} else {
		if (!is_horizontal(p2)) { // Si les 2 sont Verticales, on vérifie si elles se croisent
			if (get_x(p1) != get_x(p2)) // Leurs coordonnées horizontales
				return false ;
			if (get_y(p1) == get_y(p2)) // Leurs coordonnées verticales
				return true ;
			if (get_y(p1) > get_y(p2)) 
				return get_y(p1) < get_y(p2) + size_p2 ; // On vérifie que le point du de p1 est contenu dans p2
			return get_y(p1) + size_p1 > get_y(p2) ; // On vérifie que le point du bas de p2 est contenu dans p1
		} else { // p1 vertical, p2 horizontal
			return get_x(p1) >= get_x(p2) && get_x(p1) < get_x(p2) + size_p2 // On vérifie que l'abscisse du point de gauche de p1 est contenue dans p2,
				&& get_y(p2) >= get_y(p1) && get_y(p2) < get_y(p1) + size_p1 ; // et que l'ordonnée du point du bas de p2 est contenue dans p1
		}
	}*/

}

/**
 * @brief Returns the abscissa of leftmost point of the piece p.
 */
int get_x(cpiece p){
  return p->x ;
}

/**
 * @brief Returns the ordinate of lowest point of the piece p.
 */
int get_y(cpiece p){
  return p->y ;
}

/**
 * @brief Returns the different of ordinates of the uppermost and the lowest points of the piece p.
 */
int get_height(cpiece p){
  return p->height;
}

/**
 * @brief Returns the different of abscissas of the leftmost and the rightmost points of the piece p.
 */
int get_width(cpiece p){
  return p->width;
}

/**
 * @brief Returns true if the piece is
 */
bool is_horizontal(cpiece p){
  //return p->horizontal ; // V1
  return 0;
}



/////////////////// VERSION 2 /////////////////////////////

piece new_piece (int x, int y, int width, int height, bool move_x, bool move_y){
  
  piece p = malloc(sizeof(struct piece_s)); // On alloue dynamiquement une structure piece_s
	
  if (p == NULL){ // Il faut vérifier que l'allocation s'est faite correctement
    fprintf(stderr, "probleme d'allocation\n");
    return NULL ;
  }
	
  // Tout s'est bien passé, on définit donc la pièce
  p->x = x ;
  p->y = y ;
  p->width = width;
  p->height = height;
  p->move_x = move_x;
  p->move_y = move_y;
	
  return p ;
}

bool can_move_x(cpiece p){
  return p->move_x;
}

bool can_move_y(cpiece p){
  return p->move_y;
}



