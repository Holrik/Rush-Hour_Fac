#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
   
int creation_interface(cgame g){

  // création de la surface
  SDL_Surface *surf =  SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);

  SDL_Rect position;

  int i = 0;
  /* Création de la fenêtre */
  SDL_Window* pWindow = NULL;
  pWindow = SDL_CreateWindow("Rush_Hour",SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            640,
                            480,
                            SDL_WINDOW_SHOWN);
  //création du tableau de suface contenant toutes les surfaces des pieces
  SDL_Surface **sPieces= {NULL};
  sPieces =(SDL_Surface**) malloc(game_nb_pieces(g) * sizeof(SDL_Surface*));
  if(sPieces==NULL){
    return EXIT_FAILURE;
  }
  //remplissage
  for (i = 0 ; i <game_nb_pieces(g) ; i++){
    sPieces[i]= SDL_CreateRGBSurface(0, 640, 480, 32, 50, 50,50, 0);
  }

  //affectation des surfaces à la surface mère
  for (i = 0 ; i < game_nb_pieces(g) ; i++)

  {
      
    position.x =game_height(g)- get_x(game_piece(g,i)); // Les lignes sont à gauche (abscisse de 0)

    position.y = game_width(g) -get_y(game_piece(g,i)); // La position verticale dépend du numéro de la ligne

    if(i==0){
	    SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,255 ,64,64));
    }else{
	    SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,64 ,64,64));
    }
    SDL_BlitSurface(sPieces[i], NULL, surf, &position);

  }

  //processus permettant d'obtenir une texture à partir d'une surface 
  SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED);
  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,surf);
  SDL_RenderCopy(pRenderer, pTexture, NULL,NULL);
  SDL_RenderPresent(pRenderer);

  for (i = 0 ; i < game_nb_pieces(g) ; i++) //free des surfaces
    SDL_FreeSurface(sPieces[i]);

  SDL_Quit();


  return EXIT_SUCCESS;
}


int main(void){
  piece* p = NULL ;
  int nb_pieces ;

  nb_pieces = 10 ;
  p = realloc(p, nb_pieces*sizeof(piece)) ;
    
  *p = new_piece(1,1, 2,2, true,true) ;
  *(p+1) = new_piece(0,0, 1,1, true, true) ;
  *(p+2) = new_piece(1,0, 1,1, true, true) ;
  *(p+3) = new_piece(2,0, 1,1, true, true) ;
  *(p+4) = new_piece(3,0, 1,1, true, true) ;
  *(p+5) = new_piece(0,1, 1,2, true, true) ;
  *(p+6) = new_piece(3,1, 1,2, true, true) ;
  *(p+7) = new_piece(0,3, 2,1, true, true) ;
  *(p+8) = new_piece(2,3, 2,1, true, true) ;
  *(p+9) = new_piece(1,4, 2,1, true, true) ;

  game g = new_game (4,5, nb_pieces, p);
  
  creation_interface(g);
  return 0;

}
