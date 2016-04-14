#define TAILLE_MAX 1000
#include "niveaux.h"



game choixNiveauxRH(){

  char s_niv[4] = "";

  piece* p = NULL ;
  int nb_pieces ;

  printf("Veuillez choisir un niveau (1 à 3): ");


  while(fgets(s_niv, 4, stdin) == NULL
	|| (!isdigit(s_niv[0])
	    || s_niv[1] != '\n')
	|| atoi(s_niv) < 1
	|| atoi(s_niv) > 3 )
    {
      printf("Veuillez choisir un niveau CORRECT (1 à 3): ");
    }
    
  switch(atoi(s_niv)){

  case 1 :
    nb_pieces = 6 ;
    p = realloc(p, nb_pieces*sizeof(piece)) ;
    
    *p = new_piece(0,3,2,1,true,false) ;
    *(p+1) = new_piece(1,0,1,2,false, true) ;
    *(p+2) = new_piece(2,1,2,1,true, false) ;
    *(p+3) = new_piece(3,0,2,1,true, false) ;
    *(p+4) = new_piece(3,3,1,3,false, true) ;
    *(p+5) = new_piece(5,1,1,3,false, true) ;

    break;
  
  case 2 :
    nb_pieces = 6 ;
    p = realloc(p, nb_pieces*sizeof(piece)) ;
    
    *p = new_piece(0,3,2,1,true,false) ;
    *(p+1) = new_piece(1,0,1,2,false, true) ;
    *(p+2) = new_piece(2,1,2,1,true, false) ;
    *(p+3) = new_piece(2,0,2,1,true, false) ;
    *(p+4) = new_piece(3,2,1,3,false, true) ;
    *(p+5) = new_piece(4,0,1,3,false, true) ;

    break;
    
  case 3 :
    nb_pieces = 6 ;
    p = realloc(p, nb_pieces*sizeof(piece)) ;
    
    *p = new_piece(0,3,2,1,true,false) ;
    *(p+1) = new_piece(1,0,1,2,false, true) ;
    *(p+2) = new_piece(2,1,2,1,true, false) ;
    *(p+3) = new_piece(4,1,1,2,false, true) ;
    *(p+4) = new_piece(5,0,1,3,false, true) ;
    *(p+5) = new_piece(3,3,1,3,false, true) ;
    
    break;
    
  default:
    printf("Niveau incorrect");
    return NULL ;
  }

  game g = new_game (6, 6, nb_pieces, p);
  free(p) ;

  return g;

}


game choixNiveauxAR(){

  char s_niv[4] = "";

  piece* p = NULL ;
  int nb_pieces ;

  printf("Veuillez choisir un niveau (1 à 3): ");


  while(fgets(s_niv, 4, stdin) == NULL
	|| (!isdigit(s_niv[0])
	    || s_niv[1] != '\n')
	|| atoi(s_niv) < 1
	|| atoi(s_niv) > 3)
    {
      printf("Veuillez choisir un niveau CORRECT (1 à 3): ");
    }
    
  switch(atoi(s_niv)){

  case 1 :
    nb_pieces = 10 ;
    p = realloc(p, nb_pieces*sizeof(piece)) ;
    
    *p = new_piece(1,1, 2,2, true,true) ;
    *(p+1) = new_piece(0,0, 1,1, true, true) ;
    *(p+2) = new_piece(1,0, 1,1, true, true) ;
    *(p+3) = new_piece(2,0, 1,1, true, true) ;
    *(p+4) = new_piece(3,0, 1,1, true, true) ;
    *(p+5) = new_piece(0,1, 1,2, true, true) ;
    *(p+6) = new_piece(3,1, 1,2, true, true) ;
    *(p+7) = new_piece(0,3, 2,1, true, true) ;
    *(p+8) = new_piece(2,3, 2,1, true, true) ;
    *(p+9) = new_piece(1,4, 2,1, true, true) ;

    break;
  
  case 2 :
    nb_pieces = 10 ;
    p = realloc(p, nb_pieces*sizeof(piece)) ;
    
    *p = new_piece(1,2, 2,2, true,true) ;
    *(p+1) = new_piece(0,0, 1,1, true, true) ;
    *(p+2) = new_piece(3,0, 1,1, true, true) ;
    *(p+3) = new_piece(0,1, 1,1, true, true) ;
    *(p+4) = new_piece(3,1, 1,1, true, true) ;
    *(p+5) = new_piece(0,2, 1,2, true, true) ;
    *(p+6) = new_piece(3,2, 1,2, true, true) ;
    *(p+7) = new_piece(1,1, 2,1, true, true) ;
    *(p+8) = new_piece(0,4, 2,1, true, true) ;
    *(p+9) = new_piece(2,4, 2,1, true, true) ;

    break;
    
  case 3 :
    nb_pieces = 10 ;
    p = realloc(p, nb_pieces*sizeof(piece)) ;
    
    *p = new_piece(1,2, 2,2, true,true) ;
    *(p+1) = new_piece(1,1, 1,1, true, true) ;
    *(p+2) = new_piece(0,3, 1,1, true, true) ;
    *(p+3) = new_piece(2,4, 1,1, true, true) ;
    *(p+4) = new_piece(3,2, 1,1, true, true) ;
    *(p+5) = new_piece(0,1, 1,2, true, true) ;
    *(p+6) = new_piece(3,3, 1,2, true, true) ;
    *(p+7) = new_piece(1,0, 2,1, true, true) ;
    *(p+8) = new_piece(2,1, 2,1, true, true) ;
    *(p+9) = new_piece(0,4, 2,1, true, true) ;
    
    break;
    
  default:
    printf("Niveau incorrect");
    return NULL ;
  }

  game g = new_game (4,5, nb_pieces, p);
  free(p) ;

  return g;

}


game choixNiveaux(int jeu){
  // jeu étant le jeu sélectionné par l'utilisateur,
  // Si jeu vaut 1 alors on lance le sélectionneur de niveau du Rush-Hour
  // Sinon, si il vaut 0, on lance celui de l'Âne Rouge

  switch(jeu){
  case 1:
    return choixNiveauxRH();
    break;

  case 0:
    return choixNiveauxAR();
    break;
      
  default:
    printf("choix du jeu incorrect");
    return NULL ;
  }
}

//--------------------------------------------------------------------//
//--------------------------------------------------------------------//

piece* new_pieces_array(FILE* fichier, int nb_pieces) {

  piece* p = NULL;
  p = realloc(p, nb_pieces*sizeof(piece));
  int scanPiece[6] = {0};
  
  for (int i = 0; i < nb_pieces; i++) {

    fscanf(fichier, "%d %d %d %d %d %d",
	   scanPiece,
	   scanPiece+1,
	   scanPiece+2,
	   scanPiece+3,
	   scanPiece+4,
	   scanPiece+5);

    *(p+i) = new_piece(scanPiece[0], scanPiece[1], scanPiece[2], scanPiece[3], scanPiece[4], scanPiece[5]);
      
  }

  return p;
}

game new_game_from_file(char* typeGame, char* fichier) {

  FILE* file = fopen(fichier, "r");
  
  int scanGame[2] = {0};
  int nb_pieces = 0;
  game g = NULL;

  if (file != NULL) {

    fscanf(file, "%d %d", scanGame, scanGame+1);
    
    fscanf(file, "%d", &nb_pieces);

    g = new_game(scanGame[0], scanGame[1], nb_pieces, new_pieces_array(file, nb_pieces));

    fclose(file);
    
    return g;

  } else {
        
    printf("Impossible de lire le fichier");
    
  }

  fclose(file);

  return 0;
}
