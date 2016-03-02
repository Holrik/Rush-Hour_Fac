#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"
#include "game.h"

//génére l'affichage dans la console
void afficher(cgame g){
    // crée en mémoire un tableau rempli de -1 par défaut
    int tab [TAILLE_PLATEAU][TAILLE_PLATEAU];
    for(int i=0; i <TAILLE_PLATEAU; i++){
        for(int j=0; j <TAILLE_PLATEAU; j++){
            tab[i][j]= -1;
        } 
    }
   
   // met les voitures à leurs place dans le tableau
    for (int l = 0 ; l < game_nb_pieces(g) ; l++){
         int taille =0;
	 if(is_horizontal(game_piece(g, l))){
             taille = get_width(game_piece(g, l));
        }else{
            taille = get_height(game_piece(g, l));
        }
       for (int k=0; k<taille; k++ ){
           
           if((is_horizontal(game_piece(g, l)) == true){
                tab[get_x(game_piece(g, l)) +k][get_y(game_piece(g, l))]=l;
           }else{
                tab[get_x(game_piece(g, l))][get_y(game_piece(g, l)) +k]=l;
           }
       }
    }
    
    
    printf("  ");
    for(int i=0; i <TAILLE_PLATEAU; i++){
     printf("   %d" + i);
    }
    printf("\n");
    
     for(int i = TAILLE_PLATEAU-1; i >= 0; i++){
        printf("   ");
        for(int j=0; j <TAILLE_PLATEAU; j++){
            printf("****");
        }
        printf("*\n");
        printf("%d: |", i);
        for(int j=0; j <TAILLE_PLATEAU; j++){
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
     for(int i=0; i <TAILLE_PLATEAU; i++){
     printf("****");
    }
    printf("\n");
}

// manque la création et l'affichage!!
int main (){
game g = new_game_hr (); // à remplir avec ce qu'il faut
char * nums;
int numi;
char * direc;
int direci =-1;
char * dists;
int disti;
afficher();

//tant que ce n'est pas la fin on fait le corps du programme
while (!game_over_hr(g))
    {
        printf("Veuillez entrer le numero de la voiture:");
       fgets(nums, 2, stdin); //a tester
       numi= atoi(nums);
        printf("Veuillez entrer la direction du déplacement:");
       fgets(direc, 10, stdin); //a tester 

           
        if(direc == "UP"){
            direci=0;
        }else if(direc == "DOWN"){
            direci=2;
        }else if(direc == "LEFT"){
            direci=1;
        }else if(direc == "RIGHT"){
            direci=3;
        }
        
        if(direci > -1){
            printf("Veuillez entrer la distance du déplacement:");
            fgets(dists, 1, stdin); 
            disti= atoi(deps);
            
            play_move(g, numi,direci,depi);
            
            afficher(g);
        }
    }
   printf("Vous avez fini en %d coup(s)", game_nb_moves(g)); 
}

