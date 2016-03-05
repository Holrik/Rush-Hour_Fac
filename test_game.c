#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"
#include "game.h"


//retourne vrai si le game a bien été crée
bool test_new_game (){
	piece* p = malloc(2*sizeof(piece)) ;
	*p = new_piece_rh(0,3,true,true) ;
	*(p+1) = new_piece_rh(2,4,false, true) ;
	//piece p[] = {new_piece_rh(0,3,true,true), new_piece_rh(2,4,false, true)} ; // peut aussi être instancié ainsi, mais rend le delete plus compliqué(free d'un tableau)
	
	game g = new_game_hr (2, p);
	bool b = (g != NULL);
	delete_game(g) ;
	free(p) ;
	return b;
}


//retourne vrai si le game a bien été supprimé
/*bool test_delete_game(){
	piece* p = malloc(2*sizeof(piece)) ;
	*p = new_piece_rh(0,3,true,true) ;
	*(p+1) = new_piece_rh(2,4,false, true) ;
	
	game g = new_game_hr (2, p);
	delete_game(g);
	return g == NULL;
}*/

bool pieces_identiques(cpiece p1, cpiece p2) {
	return get_x(p1) == get_x(p2)
		  && get_y(p1) == get_y(p2)
		  && get_height(p1) == get_height(p2)
	       	  && get_width(p1) == get_width(p2) ;
}


//retourne vrai si la copie est bien la copie exact de l'original 
bool test_copy_game(){
	piece* psrc = malloc(3*sizeof(piece)) ;
	*psrc = new_piece_rh(0,3,true,true) ;
	*(psrc+1) = new_piece_rh(2,4,false, true) ;
	*(psrc+2) = new_piece_rh(3,1,false, true) ;
	piece* pdst = malloc(2*sizeof(piece)) ;
	*pdst = new_piece_rh(0,3,true,true) ;
	*(pdst+1) = new_piece_rh(2,4,false, true) ;
	
	game gsrc = new_game_hr (3, psrc);
	game gdst = new_game_hr (2, pdst);
        
	copy_game (gsrc, gdst);
	if (game_nb_pieces(gdst) != game_nb_pieces(gsrc)){
		return false;
	}
	for (int i = 0 ; i < game_nb_pieces(gdst); i++) { 
		if(!pieces_identiques(game_piece(gdst, i), game_piece(gsrc, i))) {
	  		return false;
		}
	}
	bool b = (game_nb_moves(gdst) == game_nb_moves(gsrc));
	delete_game(gdst);
	delete_game(gsrc);
	free(psrc) ;
	free(pdst) ;
	return b ;
}

// retourne vrai si le nombre de pièces retourné par la fonction est correct
bool test_game_nb_pieces(){
	piece* p = malloc(2*sizeof(piece)) ;
	*p = new_piece_rh(0,3,true,true) ;
	*(p+1) = new_piece_rh(2,4,false, true) ;
	
	game g = new_game_hr (2, p);
	bool b = (2 == game_nb_pieces(g));
	delete_game(g);
	free(p) ;
	return b ;
}


// retourne true si la pièce est bien récupérée
bool test_game_piece(){
	piece test = new_piece_rh(0,3,true,true);
	piece* p = malloc(2*sizeof(piece)) ;
	*p = test ;
	*(p+1) = new_piece_rh(2,4,false, true) ;
	game g = new_game_hr (2, p);
	bool b = (test == game_piece(g, 0));
	delete_game(g);
	free(p) ;
	return b ;
}


// retourne true si le game_over_hr return true pour la voiture rouge ayant les coordonnées (4, 3)
bool test_game_over_hr(){
	piece* p = malloc(sizeof(piece)) ;
	*p = new_piece_rh(4,3,true,true) ;
	
	game g = new_game_hr (1, p);
	bool b = game_over_hr(g) ;
	delete_game(g) ;
	free(p) ;
	return b ;
}


// retourne true si les movements valides s'effectuent et pas les movements invalides
bool test_play_move(){
	piece* p = malloc(2*sizeof(piece)) ;
	*p = new_piece_rh(0,3,true,true) ;
	*(p+1) = new_piece_rh(2,4,false, true) ;
	
	game g = new_game_hr (2, p);
	bool b = play_move(g, 0, RIGHT, 2) ;
	b = b && !play_move(g, 1, UP, 1) ;
	b = b && !play_move(g, 0, UP, 1) ;
	delete_game(g) ;
	free(p) ;
	return b ;
}


// retourne true si le nb de mouvements retournés correspond au nb de moves
bool test_game_nb_moves() {
	piece* p = malloc(2*sizeof(piece)) ;
	*p = new_piece_rh(0,3,true,true) ;
	*(p+1) = new_piece_rh(2,4,false, true) ;
	
	game g = new_game_hr (2, p);
	bool b = (game_nb_moves(g) == 0) ;
	play_move(g, 0, RIGHT, 2) ;
	b = b && (game_nb_moves(g) == 2) ;
	delete_game(g) ;
	free(p) ;
	return b ;
	}



bool test_equality_bool(bool expected, bool value, char * msg) {
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

int main() {
	bool result = true ;
	result = result && test_equality_bool(true, test_new_game(), "new_game");
	//result = result && test_equality_bool(true, test_delete_game(), "delete_game");
	result = result && test_equality_bool(true, test_copy_game(), "copy_game");
	result = result && test_equality_bool(true, test_game_nb_pieces(), "game_nb_pieces");
	result = result && test_equality_bool(true, test_game_piece(), "game_piece");
	result = result && test_equality_bool(true, test_game_over_hr(), "game_over_hr");
	result = result && test_equality_bool(true, test_play_move(), "play_move");
	result = result && test_equality_bool(true, test_game_nb_moves(), "game_nb_moves");
	
	if (result) {
		printf("Youpi !\n");
		return EXIT_SUCCESS ;
	} else
		return EXIT_FAILURE ;
}
