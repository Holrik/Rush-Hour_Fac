#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "piece.h"
#include "game.h"


void main (){
game g = new_game_hr (); // aremplir avec ce qu'il faut
char * buf;
while (game_over_hr(g))
    {
       fgets(buf, 10, stdin); //a tester

    }

}
