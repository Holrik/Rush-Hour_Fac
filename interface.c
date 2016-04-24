#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void creation_plateau(SDL_Surface* surf, cgame g){
	//création du plateau                          
  for (int i = 0 ; i < game_height(g) ; i++){
    for (int j = 0 ; j < game_width(g) ; j++){
      position.x =i; 
      position.y =j;
      SDL_BlitSurface(SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0), NULL, surf, &position);
    }
  }
}

void remplissage(SDL_Surface *surf, SDL_Surface **sPieces, cgame g){
   for (int i = 0 ; i <game_nb_pieces(g) ; i++){
    int pieceW= get_width(game_piece(g, i));
    int pieceH= get_height(game_piece(g, i));
    sPieces[i]= SDL_CreateRGBSurface(0, 100*pieceH, 100*pieceW, 32, 0, 0,0, 0);
  }

  //affectation des surfaces à la surface mère
  for (int i = 0 ; i < game_nb_pieces(g) ; i++) {
    position.x =(game_height(g)*100) - (get_x(game_piece(g,i))*100); // Les lignes sont à gauche (abscisse de 0)
    position.y =(game_width(g)*100 ) - (get_y(game_piece(g,i))*100); // La position verticale dépend du numéro de la ligne
    if(i==0){
	    SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,255 ,64,64));
    }else{
	    SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,64 ,64,64));
    }
    SDL_BlitSurface(sPieces[i], NULL, surf, &position);
  }	
}

void free_surface(SDL_Surface **sPieces, cgame g){
  for (int i = 0 ; i < game_nb_pieces(g) ; i++) //free des surfaces
    SDL_FreeSurface(sPieces[i]);
}

void nettoyage(SDL_Renderer* renderer){
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  SDL_RenderClear(renderer);	
}


   
int creation_interface(cgame g){

  // création de la surface
  SDL_Surface *surf =  SDL_CreateRGBSurface(0, (game_height(g)+1)*100, (game_width(g)+1)*100, 32, 0, 0, 0, 0);

  SDL_Rect position;

  int i = 0;
  /* Création de la fenêtre */
  SDL_Window* pWindow = NULL;
  pWindow = SDL_CreateWindow("Rush_Hour",SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            game_height(g)*100,
                            game_width(g)*100,
                            SDL_WINDOW_SHOWN);
  
  
  creation_plateau(surf, g);
  
  //création du tableau de suface contenant toutes les surfaces des pieces
  SDL_Surface **sPieces= {NULL};
  sPieces =(SDL_Surface**) malloc(game_nb_pieces(g) * sizeof(SDL_Surface*));
  if(sPieces==NULL){
    return EXIT_FAILURE;
  }
  
  remplissage(surf,sPieces,g);
  
  //processus permettant d'obtenir une texture à partir d'une surface 
  SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED);
  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,surf);
  SDL_RenderCopy(pRenderer, pTexture, NULL,NULL);
  SDL_RenderPresent(pRenderer);

  SDL_Event event;
  while (! game_over(g, jeu)){
    SDL_WaitEvent(&event);
      switch(event.type){
        case SDL_MOUSEBUTTONUP && SDL_MOUSEMOTION:
          // lien interessant pour la personne motivée http://loka.developpez.com/tutoriel/sdl/advanceEvent/
          //1) il faut savoir sur quelle voiture on est au moment du clic
          //event.button.x && event.button.y
          //2) il récupéré la postion final du déplacement de la souris en fonction des cases pour connaitre le déplacement
          //grâce à ça 
          // x = event.motion.x;
	  // y = event.motion.y;
	  //3) et pour finir déterminer la direction
	  
	  //4) puis l'appliquer
	    nettoyage(pRenderer);
	    remplissage(surf,sPieces,g);
	    pTexture = SDL_CreateTextureFromSurface(pRenderer,surf);
            SDL_RenderCopy(pRenderer, pTexture, NULL,NULL);
            SDL_RenderPresent(pRenderer);
            break;
      }
    
  }
  free_surface(sPieces,g);
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
