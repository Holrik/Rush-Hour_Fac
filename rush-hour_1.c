#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "piece.h"
#include "game.h"
#include "gameover.h"
#include "niveaux.h"
#include "affichage.h"



int choixJeu(){

  char nums[4] = "";
  printf("Veuillez entrer le numéro du jeu choisi (0:ANE ROUGE, 1:RUSH_HOUR): ");

  while (fgets(nums, 4, stdin) == NULL
	 || (!isdigit(nums[0]) || nums[1] != '\n') // Ne permet qu'un chiffre  AA
	 || atoi(nums) < 0
	 || atoi(nums)>1)
    {
      printf("\nRaté ! Veuillez entrer un numéro entre 0 et 1: ");
    }

  return atoi(nums);
}

int choixVoiture(cgame g){


  char nums[4] = "";
  printf("Veuillez entrer le numero de la voiture: ");

  while (fgets(nums, 4, stdin) == NULL
	 || (!isdigit(nums[0]) || nums[1] != '\n') // Ne permet qu'un chiffre dans le nombre de la voiture - AA
	 || atoi(nums) < 0
	 || atoi(nums) >= game_nb_pieces(g))
    {
      printf("\nRaté ! Veuillez entrer un numéro entre 0 et %d : ", game_nb_pieces(g)-1);
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

    printf("\nVeuillez saisir une direction correcte (UP/DOWN/LEFT/RIGHT) : ");

  }

}

//-----------------------------------------------------------------//

int choixDistance(cgame g, dir d){

  char dists[4] = ""; // Distance déplacement en STRING

  printf("Veuillez entrer la distance du déplacement: ");

  while(fgets(dists, 4, stdin) == NULL
	|| (!isdigit(dists[0])
	    || dists[1] != '\n') // Ne permet qu'un chiffre dans le nombre de la distance (A améliorer ?)
	|| atoi(dists) < 0
	|| (atoi(dists) >= game_width(g) && atoi(dists) >=game_height(g) )
	)
    {
      printf("\nDistance incorrecte. Veuillez entrer une distance de déplacement entre ");
      if (d==LEFT || d==RIGHT)
	printf("1 et %d pour un déplacement en longueur: ", game_width(g) );
      else
	printf("1 et %d pour un déplacement en hauteur: ", game_height(g) );
    }
  return atoi(dists); 
}

//-----------------------------------------------------------------//

int main (){
  int i = choixJeu();
  game g = choixNiveaux(i);

  afficher(g, i);

  // Tant que ce n'est pas la fin, on fait le corps du programme
  while (! game_over(g, i))
    {
      int i_cV = choixVoiture(g) ;
      int i_cDir = choixDirection(g) ;
      int i_cDis = choixDistance(g, i_cDir) ;
      
      if (play_move(g, i_cV, i_cDir, i_cDis))
	// Si le mouvement est effectué, on affiche le nouveau plateau.
	afficher(g, i) ;
      else
	// Sinon, on affiche un message d'erreur.
	// NB : La boucle se relance, puisque le Gave Over n'a forcément pas été atteint
	// puisque aucune pièce n'a été déplacée depuis la précédente boucle.
        printf("Ce mouvement ne peut pas être effectué. Veuillez réessayer.\n");
	  
    }
  printf("Vous avez fini en %d coups.\n", game_nb_moves(g));
  delete_game(g) ;
}

