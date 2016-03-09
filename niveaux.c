#include "niveaux.h"

game choixNiveaux(int jeu){
  // si jeu vaux 1  alors on lance le sélectionneur de niveau
  // du Rush hour sinon si il vaux 0 c'est celui de l'âne rouge

  switch(jeu){
    case 1:
          choixNiveauxRH();
    break;

  case 0:
         choixNiveauxAR();
      break;
  default:
    printf("choix du jeu incorrect");
  }
}


game choixNiveauxRH(){

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
      // *p = new_piece(0,3,true,true) ;
        *p = new_piece(0,3,2,1,true,false) ;
	//*(p+1) = new_piece(1,0,true, false) ;
	*(p+1) = new_piece(1,0,1,2,false, true) ;
	//*(p+2) = new_piece(2,1,true, true) ;
	*(p+2) = new_piece(2,1,2,1,true, false) ;
	//*(p+3) = new_piece(3,0,true, true) ;
	*(p+3) = new_piece(3,0,2,1,true, false) ;
	//*(p+4) = new_piece(3,3,false, false) ;
	*(p+3) = new_piece(3,0,1,3,false, true) ;
	//*(p+5) = new_piece(5,1,false, false) ;
	*(p+5) = new_piece(5,1,1,3,false, true) ;

    break;
  
  case 2 :

        //*p = new_piece(0,3,true,true) ;
        *p = new_piece(0,3,2,1,true,false) ;
	//*(p+1) = new_piece(1,0,true, false) ;
	*(p+1) = new_piece(1,0,1,2,false, true) ;
	//*(p+2) = new_piece(2,1,true, true) ;
	*(p+2) = new_piece(2,1,2,1,true, false) ;
	//*(p+3) = new_piece(2,0,true, true) ;
	*(p+3) = new_piece(2,0,2,1,true, false) ;
	//*(p+4) = new_piece(3,2,false, false) ;
	*(p+4) = new_piece(3,2,1,3,false, true) ;
	//*(p+5) = new_piece(4,0,false, false) ;
	*(p+5) = new_piece(4,0,1,3,false, true) ;

    break;
    
  case 3 :
    
        // *p = new_piece(0,3,true,true) ;
        *p = new_piece(0,3,2,1,true,false) ;
	//*(p+1) = new_piece(1,0,true, false) ;
	*(p+1) = new_piece(1,0,1,2,false, true) ;
	//*(p+2) = new_piece(2,1,true, true) ;
	*(p+2) = new_piece(2,1,2,1,true, false) ;
	//*(p+3) = new_piece(4,1,true, false) ;
	*(p+3) = new_piece(4,1,1,2,false, true) ;
	//*(p+4) = new_piece(5,0,false, false) ;
	*(p+4) = new_piece(5,0,1,3,false, true) ;
	//*(p+5) = new_piece(3,3,false, false) ;
	*(p+5) = new_piece(3,3,1,3,false, true) ;
    
    break;
    
  default:
    printf("Niveau incorrect");
  }

  game g = new_game_hr (6, p);
  free(p) ;

  return g;

}


game choixNiveauxAR(){

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
