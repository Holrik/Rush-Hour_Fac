#include "affichage.h"

//génére l'affichage dans la console
void afficher(cgame g){
    // Crée en mémoire un tableau rempli de -1 par défaut
    int tab [TAILLE_PLATEAU][TAILLE_PLATEAU];
    for(int i=0; i < TAILLE_PLATEAU ; i++){
        for(int j=0; j < TAILLE_PLATEAU ; j++){
            tab[i][j]= -1;
        } 
    }
   
   // Met les voitures à leurs place dans le tableau
    for (int l = 0 ; l < game_nb_pieces(g) ; l++){
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
    }
    
     for(int i = TAILLE_PLATEAU -1; i >= 0; i--){
        printf("   ");
	
        for(int j=0; j < TAILLE_PLATEAU ; j++){
            printf("****");
        }
	
        printf("*\n%d: |", i);
	
        for(int j=0; j < TAILLE_PLATEAU ; j++){
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
    
    for(int i=0; i < TAILLE_PLATEAU ; i++){
     printf("****");
    }
    
    printf("\n  ");
    
    for(int i = 0; i < TAILLE_PLATEAU ; i++){
      printf("   %d", i);
    }
    
    printf("\n\n");
}
