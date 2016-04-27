#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "gameover.h"


SDL_Rect position;

void creation_plateau(SDL_Surface* surf, cgame g){
  //création graphique du plateau en mettant des surfaces pour représenter chaque cases                      
  for (int i = 0 ; i < game_width(g) ; i++){
    for (int j = 0 ; j < game_height(g) ; j++){
      position.x =i*100; 
      position.y =j*100;
      //placement plus création des surfaces
      SDL_BlitSurface(SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0), NULL, surf, &position);
    }
  }
}

//remplissage du tableau graphique 
void remplissage(SDL_Surface *surf, SDL_Surface **sPieces, cgame g){
  //création des surfaces correspondantes au pièces
  for (int i = 0 ; i <game_nb_pieces(g) ; i++){
    int pieceW= get_width(game_piece(g, i));
    int pieceH= get_height(game_piece(g, i));
    sPieces[i]= SDL_CreateRGBSurface(0, 100*pieceW, 100*pieceH, 32, 0, 0,0, 0);
  }

  //affectation des surfaces à la surface mère en leur donnant une position sur la surface "mère"
  for (int i = 0 ; i < game_nb_pieces(g) ; i++) {
    position.x =get_x(game_piece(g,i)) *100; // Les lignes sont à gauche (abscisse de 0)
    position.y =(game_height(g) - get_y(game_piece(g,i)) - get_height(game_piece(g, i))) *100; // La position verticale dépend du numéro de la ligne
    //position.y = get_y(game_piece(g, i)) *100;
    if(i%10 ==0){
      SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,200 ,64,64));
    }else if(i%10 ==1){
      SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,64, 200,64));
    }else if(i%10 ==2){
      SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,64,64, 200));
    }else if(i%10 ==3){
      SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,200 ,200,64));
    }else if(i%10 ==4){
      SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,200 ,64,200));
    }else if(i%10 ==5){
      SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,64 ,200,200));
    }else if(i%10 ==6){
      SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,240, 240,240));
    }else if(i%10 ==7){
      SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,230,150, 64));
    }else if(i%10 ==8){
      SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,10 ,100,10));
    }else if(i%10 ==9){
      SDL_FillRect(sPieces[i], NULL, SDL_MapRGB(surf->format,150 ,150,150));
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
  SDL_Surface* s = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0) ;
  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer,s);
  SDL_RenderCopy(renderer, pTexture, NULL,NULL);
  //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, NULL);
  SDL_RenderPresent(renderer);
}


   
int creation_interface(game g, int jeu_type){

  // création de la surface
  SDL_Surface *surf =  SDL_CreateRGBSurface(0, game_width(g)*100, game_height(g)*100, 32, 0, 0, 0, 0);

  position.w = 100;
  position.h = 100;
  
  //int i = 0;
  /* Création de la fenêtre */
  SDL_Window* pWindow = NULL;
  pWindow = SDL_CreateWindow("Rush_Hour",SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,
			     game_width(g)*100,
			     game_height(g)*100,
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
  int i_cV =-1;
  while (SDL_WaitEvent(&event) >=0 && !game_over(g, jeu_type)){
    remplissage(surf,sPieces,g);
    pTexture = SDL_CreateTextureFromSurface(pRenderer,surf);
    SDL_RenderCopy(pRenderer, pTexture, NULL,NULL);
    SDL_RenderPresent(pRenderer);
    switch(event.type){
    case SDL_QUIT:  {
      free_surface(sPieces,g);
      SDL_Quit();
      delete_game(g) ;
      return EXIT_FAILURE;
    }
    case SDL_MOUSEBUTTONDOWN : {
      // lien interessant pour la personne motivée http://loka.developpez.com/tutoriel/sdl/advanceEvent/
      //1) il faut savoir sur quelle voiture on est au moment du clic
      //event.button.x && event.button.y
      // On prend l'endroit où le clic a été appuyé
      // On vérifie que les x-y obtenus correspondent à une pièce du plateau sinon le numéro de la voiture prend une valeur erroné par défaut
      int xDown = event.button.x;
      int yDown = event.button.y;
      for (int i = 0 ; i <game_nb_pieces(g) ; i++){
	int pieceW= get_width(game_piece(g, i));
	int pieceH= get_height(game_piece(g, i));
	int xPiece= get_x(game_piece(g,i))*100;
	int yPiece=(game_height(g) - get_y(game_piece(g,i)) -pieceH) *100;
	if( ( xDown >= xPiece) && ( xDown <= xPiece + pieceW*100 )
	    && ( yDown >= yPiece ) && ( yDown <= yPiece + pieceH*100 ) ){
	  i_cV  = i;
	  break;
	}
          	
      }
          
      break;
    }
    case SDL_MOUSEBUTTONUP : {
      // Et l'endroit où le clic a été relaché
          
      //2) il récupéré la postion final du déplacement de la souris en fonction des cases pour connaitre le déplacement
      //grâce à ça 
      if(i_cV == -1) {
	break;
      }
      int xUp = event.button.x;
      int yUp = event.button.y;
	  
      //3) et pour finir déterminer la direction et la distance
      int i_cDir=-1;
      int i_cDis=0;
      int pieceW= get_width(game_piece(g, i_cV));
      int pieceH= get_height(game_piece(g, i_cV));
      int xPiece= get_x(game_piece(g,i_cV))*100;
      int yPiece =(game_height(g) - get_y(game_piece(g,i_cV)) -pieceH) *100;
    	  
      // vérifie la direction et calcul la distance en fonction de la direction
      //UP
      if((yPiece+100 -yUp)/100 >0 ){
	i_cDir= 0;
	i_cDis=(yPiece+100 -yUp)/100;
	//LEFT
      } else if((xPiece+100 -xUp)/100>0){
	i_cDir= 1;
	i_cDis=(xPiece+100 -xUp)/100;
	//DOWN
      } else if(( yUp -(yPiece+(pieceH-1)*100) )/100>0 ){
	i_cDir= 2;
	i_cDis=( yUp -(yPiece+(pieceH-1)*100) )/100;
	//RIGHT
      } else if(( xUp -(xPiece+(pieceW-1)*100) )/100>0){
	i_cDir= 3;
	i_cDis=( xUp -(xPiece+(pieceW-1)*100) )/100;
      }
	  
      //4) puis l'appliquer
      if(i_cDir!=-1){
	play_move(g, i_cV, i_cDir, i_cDis);
      }else
	// Sinon, on affiche un message d'erreur.
	// NB : La boucle se relance, puisque le Gave Over n'a forcément pas été atteint
	// puisque aucune pièce n'a été déplacée depuis la précédente boucle.
	printf("Ce mouvement ne peut pas être effectué. Veuillez réessayer.\n");
      i_cV =-1;
      nettoyage(pRenderer);

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
int main(int argc, char *argv[]){
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
  /*if (argc != 3) {
    printf("Mauvais nombre d'arguments : Il en faut deux !\n");
    return EXIT_FAILURE ;
  }
  
  char* typeJeu = argv[1];

  int jeu = 1;

  if (strcmp(typeJeu, "a") && strcmp(typeJeu, "r")) {
    printf("Le type de jeu entré est incorrect\n");
    return EXIT_FAILURE ;
  }

  if (!strcmp(typeJeu, "a")) {
    jeu = 0;
  }
  
  game g = new_game_from_file(argv[2]);*/
  
  creation_interface(g, 0);
  return EXIT_SUCCESS;

}
