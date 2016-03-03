#include <stdlib.h>
//#include <time.h> // A quoi ça sert ???
#include <stdio.h>
#include <string.h> // A enlever quand le main sera modifié
#include <ctype.h>
#include "piece.h"
#include "game.h"

//génére l'affichage dans la console
void afficher(cgame g){
    // Crée en mémoire un tableau rempli de -1 par défaut
    int tab [TAILLE_PLATEAU][TAILLE_PLATEAU];
    for(int i=0; i <TAILLE_PLATEAU; i++){
        for(int j=0; j <TAILLE_PLATEAU; j++){
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
    
    
    printf("  ");
    for(int i = 0; i < TAILLE_PLATEAU; i++){
     printf("   %d" + i);
    }
    printf("\n");
    
     for(int i = TAILLE_PLATEAU-1; i >= 0; i--){
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

// Manque la création et l'affichage!!
int main (){
  piece* p = malloc(2*sizeof(piece)) ;
        *p = new_piece_rh(0,3,true,true) ;
	*(p+1) = new_piece_rh(2,2,false, false) ;
	*(p+2) = new_piece_rh(3,1,false, false) ;
	
  game g = new_game_hr (3, p); // à remplir avec ce qu'il faut | TODO
  
  char nums[4] = ""; // Numéro voiture à déplacer en STRING
  int numi; // Numéro voiture à déplacer en INT
  
  char direc[10] = ""; // UP/DOWN/LEFT/RIGHT
  int direci = -1; // Direction de la voiture à partir de direc
  
  char dists[4] = ""; // Distance déplacement en STRING
  int disti; // Distance déplacement en INT
  
  afficher(g);

// Tant que ce n'est pas la fin, on fait le corps du programme
while (!game_over_hr(g))
    {
        printf("Veuillez entrer le numero de la voiture: ");

	while (fgets(nums, 4, stdin) == NULL
	       || (!isdigit(nums[0]) || nums[1] != '\n') // Ne permet qu'un chiffre dans le nombre de la voiture (A améliorer ?)
	       || atoi(nums) < 0
	       || atoi(nums) >= game_nb_pieces(g)){
	  printf("Raté ! Veuillez entrer un numéro entre 0 et %d : ", game_nb_pieces(g)-1);
	}

	numi = atoi(nums);

	
        printf("Veuillez entrer la direction du déplacement: ");

	while(fgets(direc, 10, stdin) == NULL
	      || strcmp(direc, "UP\n\0")!= 0
	      || strcmp(direc, "DOWN")!= 0
	      || strcmp(direc, "LEFT")!= 0
	      || strcmp(direc, "RIGHT")!= 0){

	  printf("Direction incorrecte. Veuillez entrer UP/DOWN/LEFT/RIGHT.\n");
	}

	if(strcmp(direc, "UP")){
	    direci = 0;
	} else if(strcmp(direc, "LEFT")){
	    direci = 1;
	} else if(strcmp(direc, "DOWN")){
	    direci = 2;
	} else {
	    direci = 3;
	}

	printf("Veuillez entrer la distance du déplacement: ");

	// TODO - Vérifier entrées utilisateur
	while(fgets(dists, 4, stdin) == NULL
	       || (!isdigit(dists[0]) || dists[1] != '\n') // Ne permet qu'un chiffre dans le nombre de la distance (A améliorer ?)
	       || atoi(dists) < 0
	       || atoi(dists) >= game_nb_pieces(g)){

	  printf("Distance incorrecte. Veuillez entrer une distance de déplacement entre 1 et %d: ", TAILLE_PLATEAU);
	  
	}
	    
        disti= atoi(dists);
            
        play_move(g, numi, direci, disti);
            
        afficher(g);
        
    }
   printf("Vous avez fini en %d coups.\n", game_nb_moves(g)); 
}

