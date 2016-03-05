#include "niveaux.h"

game choixNiveaux(){

  char s_niv[4] = "";

  piece* p = malloc(6*sizeof(piece)) ;

  printf("Veuillez choisir un niveau (1 à 3): ");


  while(fgets(s_niv, 4, stdin) == NULL
	|| (!isdigit(s_niv[0])
	|| s_niv[1] != '\n')
	|| atoi(s_niv) < 0
	|| atoi(s_niv) >= TAILLE_PLATEAU)
  {
    printf("Veuillez choisir un niveau CORRECT (1 à 3): ");
  }
    
  switch(atoi(s_niv)){

    case 1 :

        *p = new_piece_rh(0,3,true,true) ;
	*(p+1) = new_piece_rh(1,0,true, false) ;
	*(p+2) = new_piece_rh(2,1,true, true) ;
	*(p+3) = new_piece_rh(3,0,true, true) ;
	*(p+4) = new_piece_rh(3,3,false, false) ;
	*(p+5) = new_piece_rh(5,1,false, false) ;

    break;
  
  case 2 :

        *p = new_piece_rh(0,3,true,true) ;
	*(p+1) = new_piece_rh(1,0,true, false) ;
	*(p+2) = new_piece_rh(2,1,true, true) ;
	*(p+3) = new_piece_rh(2,0,true, true) ;
	*(p+4) = new_piece_rh(3,2,false, false) ;
	*(p+5) = new_piece_rh(4,0,false, false) ;

    break;
    
  case 3 :
    
        *p = new_piece_rh(0,3,true,true) ;
	*(p+1) = new_piece_rh(1,0,true, false) ;
	*(p+2) = new_piece_rh(2,1,true, true) ;
	*(p+3) = new_piece_rh(4,1,true, false) ;
	*(p+4) = new_piece_rh(5,0,false, false) ;
	*(p+5) = new_piece_rh(3,3,false, false) ;
    
    break;
    
  default:
    printf("Niveau incorrect");
  }

  game g = new_game_hr (6, p);
  free(p) ;

  return g;

}
