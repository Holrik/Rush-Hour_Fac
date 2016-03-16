#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
#include "mygame.h"
#include "game.h"


static bool game_over_ar(cgame g){
  return get_x(game_piece(g, 0)) == 1 && get_y(game_piece(g, 0))==0;
}

bool game_over(cgame g, int jeu){
  // jeu étant la valeur entrée par le joueur pour choisir le type de jeu,
  // Si jeu vaut 1 alors on lance le sélectionneur de Game Over du Rush-Hour
  // Sinon, si il vaut 0, on lance celui de l'Âne Rouge

  switch(jeu){
  case 1:
    return game_over_hr(g);
    break;

  case 0:
    return game_over_ar(g);
    break;
      
  default:
    printf("choix du jeu incorrect");
    return NULL ;
  }
}
