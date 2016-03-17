#ifndef _MGAME_H_
#define _MGAME_H_
#include <stdbool.h>
#include "piece.h"
#include "game.h"

/**
 * @brief selectionne le game_over correspondant au game choisi.
 * @return true if the piece find he exit
 */
bool game_over(cgame g, int jeu);

#endif
