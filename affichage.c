#include "affichage.h"
#include "game.h"

//génére l'affichage dans la console
void afficher(cgame g){
  int width=game_width(g);
  int height= game_height(g);
    // Crée en mémoire un tableau rempli de -1 par défaut
    int tab [width][height];
    for(int i=0; i < width ; i++){
        for(int j=0; j < height ; j++){
            tab[i][j]= -1;
        } 
    }
   
   // Met les voitures à leurs place dans le tableau
    /*  for (int l = 0 ; l < game_nb_pieces(g) ; l++){
         int taille =0;
	 if(is_horizontal(game_piece(g, l))){
             taille = get_width(game_piece(g, l));
        }else{
            taille = get_height(game_piece(g, l));
        }
       for (int k=0; k<taille; k++ ){
           
	 if(is_horizontal(game_piece(g, l))){
	   // On met y puis x car pour chaque ligne tab[y] du tableau on lira
	   // sa case tab[y][x]
                tab[get_y(game_piece(g, l))][get_x(game_piece(g, l)) +k]=l;
         }else{
                tab[get_y(game_piece(g, l)) +k][get_x(game_piece(g, l))]=l;
         }
       }
       }*/


    
    for (int l = 0 ; l < game_nb_pieces(g) ; l++){
      int pieceW=  get_width(game_piece(g, l));
      int pieceH= get_height(game_piece(g, l));   
      for (int k =0; k< pieceW; k++){
	tab[get_y(game_piece(g, l))+k][get_x(game_piece(g, l))]=l;
      }
      for(int j= 0; j<pieceH; j++){
	tab[get_y(game_piece(g, l))][get_x(game_piece(g, l)) +j]=l;
      }
    } 
     for(int i = width -1; i >= 0; i--){
        printf("   ");
	
        for(int j=0; j < height ; j++){
            printf("****");
        }
	
        printf("*\n%d: |", i);
	
        for(int j=0; j < height ; j++){
            if(tab[i][j]==-1){
                printf("   |");
            }else{
                printf(" %d |", tab[i][j]);
            }
        }
	
        if (i == 3)
            printf(" ->");
        printf("\n");
    }
    printf("   *");
    
    for(int i=0; i < width ; i++){
     printf("****");
    }
    
    printf("\n  ");
    
    for(int i = 0; i < width ; i++){
      printf("   %d", i);
    }
    
    printf("\n\n");

}
