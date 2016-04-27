#include "affichage.h"
#include "game.h"
#include <string.h>

//génére l'affichage dans la console
void afficher(cgame g, int jeu){
  int width= game_width(g);
  int height= game_height(g);
  
  // Crée en mémoire un tableau rempli de -1 par défaut
  int tab [height][width];
  for(int i=0; i < height ; i++){
    for(int j=0; j < width ; j++){
      tab[i][j]= -1;
    } 
  }
   
  // Met les voitures à leur place dans le tableau
  for (int l = 0 ; l < game_nb_pieces(g) ; l++){
    int pieceW= get_width(game_piece(g, l));
    int pieceH= get_height(game_piece(g, l));   
    for(int i=0; i< pieceW; i++){
      for(int j=0; j< pieceH; j++){
	tab[get_y(game_piece(g, l))+j][get_x(game_piece(g, l))+i]=l;
      }
    }
  } 
  for(int i = height -1; i >= 0; i--){
    printf("   ");
	
    for(int j=0; j < width ; j++){
      printf("****");
    }
	
    printf("*\n%d: |", i);
	
    for(int j=0; j < width ; j++){
      if(tab[i][j]==-1){
	printf("   |");
      }else if(tab[i][j]==0){
	printf("\e[0;31m %d \e[0m|", tab[i][j]);
      }else{
	printf(" %d |", tab[i][j]);
      }
    }
    int ligne_fin = get_y(game_piece(g, 0));
    if (i == ligne_fin && jeu == 1)
      printf(" ->");
    printf("\n");
  }
  printf("   *");
    
  for(int i=0; i < width ; i++){
    printf("****");
  }
  
  if (jeu == 0) {
    printf("\n       |SORTIE|\n       |______|");
  }
    
  printf("\n  ");
    
  for(int i = 0; i < width ; i++){
    printf("   %d", i);
  }
    
  printf("\n\n");

}
