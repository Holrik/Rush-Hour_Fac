#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"
#include "game.h"


//retourne vrai si le game a bien était créé
bool test_new_game (){
game g = new_game_hr (2, {new_piece_rh(0,3,true,true), new_piece_rh(2,4,false, true)});
bool b = (g != NULL);
delete_game(g) ;
return b;
}


//retourne vrai si le game a bien été supprimé
bool test_delete_game(){
game g = new_game_hr (2, {new_piece_rh(0,3,true,true), new_piece_rh(2,4,false, true)});
delete_game(g);
return g == NULL;
}


//retourne vrai si la copie est bien la copie exact de l'original 
bool test_copy_game(){
game gsrc = new_game_hr (3, {new_piece_rh(0,3,true,true), new_piece_rh(2,4,false, true),new_piece_rh(3,1,true,false)});
game gdst = new_game_hr (2, {new_piece_rh(0,3,true,true), new_piece_rh(2,4,false, true)});
copy_game (gsrc,gdst);
if (gdst->nb_pieces != gsrc->nb_pieces){
return false;
}
for (int i = 0 ; i < gdst->nb_pieces; i++) { 
		if(*(gdst->pieces +i) != *(gsrc->pieces+i)) {
	  	return false;
		}
	}
bool b = (gdst->nb_moves ==gsrc->nb_moves);
delete_game(gdst);
delete_game(gsrc);
return b ;
}

// retourne vrai si le nombre de pièces retourné par la fonction est correct
bool test_game_nb_pieces(){
game g = new_game_hr (2, {new_piece_rh(0,3,true,true), new_piece_rh(2,4,false, true)});
bool b = (2==game_nb_pieces(g));
delete_game(g);
return b ;
}


bool test_game_piece(){
piece test = new_piece_rh(0,1,true,true);
game g = new_game_hr (2, {test, new_piece_rh(2,4,false, true)});
bool b = (test == game_piece(g,2));
delete_game(g);
return b ;
}


bool test_game_over_hr(){
	game g = new_game_hr (2, {test, new_piece_rh(4,3,false, true)});
	bool b = game_over_hr(g) ;
	delete_game(g) ;
	return b ;
}


bool test_play_move(){
	game g = new_game_hr (2, {new_piece_rh(0,3,true,true), new_piece_rh(2,4,false, true)});
	bool b = play_move(g, 0, RIGHT, 2) ;
	b = b && !play_move(g, 1, UP, 1) ;
	b = b && !play_move(g, 0, UP, 1) ;
	delete_game(g) ;
	return b ;
}

bool game_nb_moves() {
	game g = new_game_hr (2, {new_piece_rh(0,3,true,true), new_piece_rh(2,4,false, true)});
	bool b = (game_nb_moves(g) == 0) ;
	play_move(g, 0, RIGHT, 2) ;
	b = b && (game_nb_moves(g) == 1) ;
	return b ;
}
