#ifndef _NIVEAUX_H_
#define _NIVEAUX_H_
#include "piece.h"
#include "game.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

game choixNiveaux(int jeu);
game choixNiveauxRH();
game choixNiveauxAR();
game new_game_from_file(char* fichier);

#endif
