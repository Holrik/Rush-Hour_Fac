#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"
#include "game.h"


//retourne vrai si le game a bien était créé
bool test_new_game (){
game g = new new_game_hr (2, {new_piece_rh(0,1,true,true), new_piece_rh(2,4,false, true)});
return g != NULL;
}


//retourne vrai si le game a bien été supprimé
bool test_delete_game(){
game g = new new_game_hr (2, {new_piece_rh(0,1,true,true), new_piece_rh(2,4,false, true)});
delete_game(g);
return g == NULL;
}


//retourne vrai si la copie est bien la copie exact de l'original 
bool test_copy_game(){
game gsrc = new new_game_hr (3, {new_piece_rh(0,1,true,true), new_piece_rh(2,4,false, true),new_piece_rh(3,1,true,false)});
game gdst = new new_game_hr (2, {new_piece_rh(0,1,true,true), new_piece_rh(2,4,false, true)});
copy_game (gsrc,gdst);
if (gdst->nb_pieces != gsrc->nb_pieces){
return false;
}
for (int i = 0 ; i < gdst->nb_pieces; i++) { 
		if(*(gdst->pieces +i) != *(gsrc->pieces+i)) {
	  	return false;
		}
	}
return (gdst->nb_moves ==gsrc->nb_moves);
}

// retourne vrai si le nombre de pièces retourné par la fonction est correct
bool test_game_nb_pieces(){
game g = new new_game_hr (2, {new_piece_rh(0,1,true,true), new_piece_rh(2,4,false, true)});
return 2==game_nb_pieces(g);
}


bool test_game_piece(){
piece test = new_piece_rh(0,1,true,true);
game g = new new_game_hr (2, {test, new_piece_rh(2,4,false, true)});
return test == game_piece(g,2);
}


