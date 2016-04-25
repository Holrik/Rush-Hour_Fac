#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "gameover.h"


SDL_Rect position;

void creation_plateau(SDL_Surface* surf, cgame g){
  //création graphique du plateau                          
  for (int i = 0 ; i < game_height(g) ; i++){
    for (int j = 0 ; j < game_width(g) ; j++){
      position.x =i*100; 
      position.y =j*100;
      SDL_BlitSurface(SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0), NULL, surf, &position);
    }
  }
}

//remplissage du tableau graphique
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

//libération des surfaces
void free_surface(SDL_Surface **sPieces, cgame g){
  for (int i = 0 ; i < game_nb_pieces(g) ; i++) //free des surfaces
    SDL_FreeSurface(sPieces[i]);
}

//nettoie l'affichage pour éviter la super position
void nettoyage(SDL_Renderer* renderer){
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  SDL_RenderClear(renderer);	
}


   
int creation_interface(game g, int jeu_type){

  // création de la surface
  SDL_Surface *surf =  SDL_CreateRGBSurface(0, game_height(g)*100, game_width(g)*100, 32, 0, 0, 0, 0);

  position.w = 100;
  position.h = 100;
  
  //int i = 0;
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
  while (! game_over(g, jeu_type)){
    SDL_WaitEvent(&event);
    int xDown=0;
    int yDown=0;
    int i_cV =-1;
    switch(event.type){
    case SDL_MOUSEBUTTONDOWN : {
      // lien interessant pour la personne motivée http://loka.developpez.com/tutoriel/sdl/advanceEvent/
      //1) il faut savoir sur quelle voiture on est au moment du clic
      //event.button.x && event.button.y
      // On prend l'endroit où le clic a été appuyé
      // On vérifie que les x-y obtenus correspondent à une pièce du plateau sinon le numéro de la voiture prend une valeur erroné par défaut
      xDown = event.button.x;
      yDown = event.button.y;
      for (int i = 0 ; i <game_nb_pieces(g) ; i++){
	int xPiece= (game_height(g)*100) - (get_x(game_piece(g,i))*100);
	int yPiece =(game_width(g)*100 ) - (get_y(game_piece(g,i))*100);
	int pieceW= get_width(game_piece(g, i));
	int pieceH= get_height(game_piece(g, i));
	if( ( xDown > xPiece) && ( xDown < xPiece + pieceW )
	    && ( yDown > yPiece ) && ( yDown < yPiece + pieceH ) ){
	  i_cV  = i;
	}
          	
      }
          
      break;
    }
    case SDL_MOUSEBUTTONUP : {
      // Et l'endroit où le clic a été relaché
          
      //2) il récupéré la postion final du déplacement de la souris en fonction des cases pour connaitre le déplacement
      //grâce à ça 
      int xUp = event.button.x;
      int yUp = event.button.y;
	  
      //3) et pour finir déterminer la direction et la distance
      int i_cDir=-1;
      int i_cDis=0;
      int xPiece= (game_height(g)*100) - (get_x(game_piece(g,i_cV))*100);
      int yPiece =(game_width(g)*100 ) - (get_y(game_piece(g,i_cV))*100);
      int pieceW= get_width(game_piece(g, i_cV));
      int pieceH= get_height(game_piece(g, i_cV));
    	  
      // vérifie la direction et calcul la distance en fonction de la direction
      if((yPiece - yUp)/100<0 ){
	i_cDir= 0;
	i_cDis=(yPiece - yUp)/100;
      } else if((xPiece-xUp)/100<0){
	i_cDir= 1;
	i_cDis=(xPiece-xUp)/100;
      } else if((yPiece+pieceH - yUp)/100>0 ){
	i_cDir= 2;
	i_cDis=(yPiece+pieceH - yUp)/100;
      } else if((xPiece+pieceW-xUp)/100>0){
	i_cDir= 3;
	i_cDis=(xPiece+pieceW-xUp)/100;
      }
	  
      //4) puis l'appliquer
      if(i_cV!=-1){
	if (play_move(g, i_cV, i_cDir, i_cDis)){
	  // Si le mouvement est effectué, on affiche le nouveau plateau.
	  nettoyage(pRenderer);
	  remplissage(surf,sPieces,g);
	  pTexture = SDL_CreateTextureFromSurface(pRenderer,surf);
	  SDL_RenderCopy(pRenderer, pTexture, NULL,NULL);
	  SDL_RenderPresent(pRenderer);
	}
      }else
	// Sinon, on affiche un message d'erreur.
	// NB : La boucle se relance, puisque le Gave Over n'a forcément pas été atteint
	// puisque aucune pièce n'a été déplacée depuis la précédente boucle.
	printf("Ce mouvement ne peut pas être effectué. Veuillez réessayer.\n");  

      break;
    }
    }
    
  }
  free_surface(sPieces,g);
  SDL_Quit();
  
  printf("Vous avez fini en %d coups.\n", game_nb_moves(g));
  delete_game(g) ;
  
  return EXIT_SUCCESS;
}

//test
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
  
  creation_interface(g, 0);
  return EXIT_SUCCESS;

}