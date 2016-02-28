#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"
#include "game.h"

// manque la création et l'affichage!!
void main (){
game g = new_game_hr (); // aremplir avec ce qu'il faut
char * nums;
int numi;
char * direc;
int direci =-1;
char * dists;
int disti;
while (game_over_hr(g))
    {
        printf("Veuillez entrer le numero de la voiture:");
       fgets(nums, 2, stdin); //a tester
       numi= atoi(nums);
        printf("Veuillez entrer la direction du déplacement:");
       fgets(direc, 10, stdin); //a tester printf("Veuillez entrer le numero de la voiture:");

           
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
            printf("Veuillez entrer le nombre de déplacement:");
           fgets(dists, 1, stdin); 
            disti= atoi(deps);
            
            play_move(g, numi,direci,depi);
            
            //affichage!!
        }
    }
    
}

