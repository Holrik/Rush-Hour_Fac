#include <SDL2/SDL.h>
#include <stdio.h>

   
int creation_interface(cgame g){
    
  // création de la surface
 SDL_Surface surf =  SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);

    SDL_Rect position;

    int i = 0;
    /* Création de la fenêtre */
     SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  640,
                                                                  480,
			       SDL_WINDOW_SHOWN);

    SDL_Surface* sPieces= {NULL};
    sPieces = malloc(game->nb_pieces*sizeof(SDL_Suface));
    if(sPieces==NULL){
      return EXIT_FAILURE;
    }
    for (i = 0 ; i < game->nb_pieces ; i++){
      sPieces[i]= SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
    }
    
    for (i = 0 ; i < game->nb_pieces ; i++)

    {
        position.x = game->pieces[i]->x; // Les lignes sont à gauche (abscisse de 0)

        position.y = game->pieces[i]->y; // La position verticale dépend du numéro de la ligne

        SDL_BlitSurface(sPieces[i], NULL, surf, &position);

    }


    for (i = 0 ; i <= game->nb_pieces ; i++) //free des surfaces
        SDL_FreeSurface(sPieces[i]);

    SDL_Quit();


    return EXIT_SUCCESS;
}

