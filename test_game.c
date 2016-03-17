#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"
#include "game.h"
#include "gameover.h"

// Retourne vrai si le game a bien été crée
bool test_new_game (){

  // On crée les pièces
  piece* p = malloc(2*sizeof(piece));
  *p = new_piece(0, 3, 3, 1, true, true);
  *(p+1) = new_piece(2, 4, 1, 2, true, true);

  // On crée le game avec les deux pièces
  game g = new_game(6, 6, 2, p);
  bool b = (g != NULL);
  
  delete_game(g);
  free(p);
  
  return b;
}

//-----------------------------------------------------------------//

// Retourne vrai si les deux pièces sont identiques
bool pieces_identiques(cpiece p1, cpiece p2) {
  
  return get_x(p1) == get_x(p2)
    && get_y(p1) == get_y(p2)
    && get_height(p1) == get_height(p2)
    && get_width(p1) == get_width(p2) ;
}

//-----------------------------------------------------------------//

// Retourne vrai si la copie est bien la copie exact de l'original 
bool test_copy_game(){

  // Création pièces Src
  piece* psrc = malloc(3*sizeof(piece));
  *psrc = new_piece(0, 3, 3, 1, true, true);
  *(psrc+1) = new_piece(2, 4, 1, 2, true, true);
  *(psrc+2) = new_piece(3, 1, 2, 1, true, true);

  // Création pièces Dst
  piece* pdst = malloc(2*sizeof(piece)) ;
  *pdst = new_piece(0, 3, 3, 1, true, true);
  *(pdst+1) = new_piece(2, 4, 1, 2, true, true);
  *(pdst+2) = new_piece(3, 1, 2, 1, true, true);

  // Création de deux games
  game gsrc = new_game(6, 6, 3, psrc);
  game gdst = new_game(4, 4, 3, pdst);

  // On copie game Src dans game Dst
  copy_game (gsrc, gdst);

  // Si le nombre de pièces de game Src et game Dst est différent
  if (game_nb_pieces(gdst) != game_nb_pieces(gsrc)){
    return false;
  }

  // Si les pièces de game Src et game Dst sont différentes
  for (int i = 0 ; i < game_nb_pieces(gdst); i++) { 
    if(!pieces_identiques(game_piece(gdst, i), game_piece(gsrc, i))) {
      return false;
    }
  }
  
  bool b = (game_nb_moves(gdst) == game_nb_moves(gsrc));
  
  delete_game(gdst);
  delete_game(gsrc);
  free(psrc);
  free(pdst);
  
  return b;
}

//-----------------------------------------------------------------//

// Retourne vrai si le nombre de pièces retourné par la fonction est correct
bool test_game_nb_pieces(){

  // Création de deux pièces
  piece* p = malloc(2*sizeof(piece)) ;
  *p = new_piece(0, 3, 3, 1, true, true);
  *(p+1) = new_piece(2, 4, 1, 2, true, true);

  // Création du game avec les deux pièces
  game g = new_game(6, 6, 2, p);

  // On vérifie la présence des deux pièces dans le game
  bool b = (2 == game_nb_pieces(g));
  
  delete_game(g);
  free(p);
  
  return b;
}

//-----------------------------------------------------------------//

// Retourne vrai si la pièce est bien récupérée
bool test_game_piece(){

  // Création de la pièce à récupérer
  piece test = new_piece(0, 3, 3, 1, true, true);
  
  piece* p = malloc(2*sizeof(piece));
  *p = test;
  *(p+1) = new_piece(2, 4, 1, 2, true, true);
  
  game g = new_game(6, 6, 2, p);

  // On compare la pièce de test à la première dans p
  bool b = (test == game_piece(g, 0));
  
  delete_game(g);
  free(p) ;
  
  return b ;
}

//-----------------------------------------------------------------//

// Retourne vrai si le game_over_hr return true pour la voiture rouge ayant les coordonnées (4, 3)
bool test_game_over_hr(){
  
  piece* p = malloc(sizeof(piece));
  *p = new_piece(4, 3, 2, 1, true, true);
	
  game g = new_game(6, 6, 1, p);

  // Si la pièce est arrivée à la fin
  bool b = game_over(g, 1);
  
  delete_game(g);
  free(p);
  
  return b;
}

//-----------------------------------------------------------------//

// Retourne vrai si le game_over_ar return true pour la voiture rouge ayant les coordonnées (4, 3)
bool test_game_over_ar(){
  
  piece* p = malloc(sizeof(piece)) ;
  *p = new_piece(1, 0, 2, 2, true, true) ;
	
  game g = new_game(4, 5, 1, p);

  // Si la pièce est arrivée à la fin
  bool b = game_over(g, 0);
  
  delete_game(g) ;
  free(p) ;
  
  return b ;
}

//-----------------------------------------------------------------//

// Retourne vrai si les mouvements valides s'effectuent et non pas les mouvements invalides
bool test_play_move(){
  
  piece* p = malloc(2*sizeof(piece)) ;
  *p = new_piece(0, 3, 3, 1, true, true);
  *(p+1) = new_piece(2, 4, 1, 2, true, true);
	
  game g = new_game(6, 6, 2, p);

  // On effectue des mouvements sur les deux pièces
  bool b = play_move(g, 0, RIGHT, 2) ;
  b = b && !play_move(g, 1, UP, 1) ;
  b = b && !play_move(g, 0, UP, 1) ;
  
  delete_game(g) ;
  free(p) ;
  
  return b ;
}

//-----------------------------------------------------------------//

// Retourne vrai si le nombre de mouvements retournés correspond au nombre de moves
bool test_game_nb_moves() {
  
  piece* p = malloc(2*sizeof(piece)) ;
  *p = new_piece(0, 3, 3, 1, true, true);
  *(p+1) = new_piece(2, 4, 1, 2, true, true);
  
  game g = new_game(6, 6, 2, p);

  // On vérifie qu'aucun mouvement n'a été effectué
  bool b = (game_nb_moves(g) == 0) ;

  // On bouge une pièce de 2 cases
  play_move(g, 0, RIGHT, 2) ;

  // On vérifie que le nombre de move est bien à deux
  b = b && (game_nb_moves(g) == 2) ;
  
  delete_game(g) ;
  free(p) ;
  
  return b ;
}

//-----------------------------------------------------------------//

bool test_equality_bool(bool expected, bool value, char * msg) {
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

//-----------------------------------------------------------------//

int main() {
  
  bool result = true ;
  
  result = result && test_equality_bool(true, test_new_game(), "new_game");
  result = result && test_equality_bool(true, test_copy_game(), "copy_game");
  result = result && test_equality_bool(true, test_game_nb_pieces(), "game_nb_pieces");
  result = result && test_equality_bool(true, test_game_piece(), "game_piece");
  result = result && test_equality_bool(true, test_game_over_hr(), "game_over_hr");
  result = result && test_equality_bool(true, test_game_over_ar(), "game_over_ar");
  result = result && test_equality_bool(true, test_play_move(), "play_move");
  result = result && test_equality_bool(true, test_game_nb_moves(), "game_nb_moves");
	
  if (result) {
    
    printf("Youpi !\n");
    return EXIT_SUCCESS ;
    
  } else {
    
    return EXIT_FAILURE ;
    
  }
  
}
