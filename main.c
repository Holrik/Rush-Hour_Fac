#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"
#include "game.h"

void afficher(cgame g){
    int tab [TAILLE_PLATEAU][TAILLE_PLATEAU];
    for(int i=0; i <TAILLE_PLATEAU; i++){
        for(int j=0; j <TAILLE_PLATEAU; j++){
            tab[i][j]= -1;
        } 
    }
   
    for (int l=0; l<g->nb_pieces, l++){
         int taille =0;
        if((g->pieces+l)->small == true){
             taille = 2;
        }else{
            taille=3;
        }
       for (int k=0; k<taille; k++ ){
           
           if((g->pieces+l)->horizontal == true){
                tab[get_x(g->pieces+l)+k][get_y(g->pieces+l)]=l;
           }else{
                tab[get_x(g->pieces+l)][get_y(g->pieces+l)+k]=l;
           }
       }
    }
    
    
    for(int k=0; k <TAILLE_PLATEAU; k++){
     printf("--");
    }
    printf("\n");
     for(int i=0; i <TAILLE_PLATEAU; i++){
          printf("||");
        for(int j=0; j <TAILLE_PLATEAU; j++){
            if(tab[i][j]==-1){
                printf(" ");
            }else{
                printf(tab[i][j]);
            }
        } 
        printf("|| \n");
    }
     for(int k=0; k <TAILLE_PLATEAU; k++){
     printf("--");
    }
}

// manque la création et l'affichage!!
void main (){
game g = new_game_hr (); // aremplir avec ce qu'il faut
char * nums;
int numi;
char * direc;
int direci =-1;
char * dists;
int disti;
afficher();
while (game_over_hr(g))
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
            
            afficher();
        }
    }
   prinft("vous avez finis en:"+ g->nb_moves+ "coup(s)"); 
}

