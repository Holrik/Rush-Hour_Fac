#include <stdlib.h>
//#include <time.h> // A quoi ça sert ???
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "piece.h"
#include "game.h"
#include "niveaux.h"
#include "affichage.h"




int choixVoiture(cgame g){

  char nums[4] = "";
  printf("Veuillez entrer le numero de la voiture: ");

  while (fgets(nums, 4, stdin) == NULL
	 || (!isdigit(nums[0]) || nums[1] != '\n') // Ne permet qu'un chiffre dans le nombre de la voiture - AA
	 || atoi(nums) < 0
	 || atoi(nums) >= game_nb_pieces(g))
  {
	  printf("Raté ! Veuillez entrer un numéro entre 0 et %d : ", game_nb_pieces(g)-1);
  }

  return atoi(nums);
  
}

//-----------------------------------------------------------------//

int choixDirection(cgame g){

  char direc[10] = ""; // UP/DOWN/LEFT/RIGHT
  
  printf("Veuillez entrer la direction du déplacement (UP/DOWN/LEFT/RIGHT): ");

  while(true){

    fgets(direc, 10, stdin);
    
    if(!strcmp(direc, "UP\n")){
      return 0;
    } else if(!strcmp(direc, "LEFT\n")){
      return 1;
    } else if(!strcmp(direc, "DOWN\n")){
      return 2;
    } else if(!strcmp(direc, "RIGHT\n")){
      return 3;
    }

    printf("Veuillez saisir une direction correcte (UP/DOWN/LEFT/RIGHT) : ");

  }

}

//-----------------------------------------------------------------//

int choixDistance(cgame g){

  char dists[4] = ""; // Distance déplacement en STRING

  printf("Veuillez entrer la distance du déplacement: ");

  // TODO - Vérifier entrées utilisateur
  while(fgets(dists, 4, stdin) == NULL
	|| (!isdigit(dists[0])
	|| dists[1] != '\n') // Ne permet qu'un chiffre dans le nombre de la distance (A améliorer ?)
	|| atoi(dists) < 0
	|| atoi(dists) >= TAILLE_PLATEAU)
  {
    printf("Distance incorrecte. Veuillez entrer une distance de déplacement entre 1 et %d: ", TAILLE_PLATEAU);
  }
  return atoi(dists); 
}

//-----------------------------------------------------------------//

int main (){

  game g = choixNiveaux();

  afficher(g);

// Tant que ce n'est pas la fin, on fait le corps du programme
while (!game_over_hr(g))
    {
      int i_cV = choixVoiture(g) ;
      int i_cDir = choixDirection(g) ;
      int i_cDis = choixDistance(g) ;
      
      play_move(g, i_cV, i_cDir, i_cDis);
            
      afficher(g);
        
      }
   printf("Vous avez fini en %d coups.\n", game_nb_moves(g));
   delete_game(g) ;
}
