#define TAILLE_MAX 1000
#include "niveaux.h"


// Renvoie un tableau de pièces à partir du fichier entré en paramètre
piece* new_pieces_array(FILE* fichier, int nb_pieces) {

  piece* p = NULL;
  p = realloc(p, nb_pieces*sizeof(piece));

  // Variable contenant les paramètres de la pièce
  int scanPiece[6] = {0};

  // Pour le nombre de pièces entré en paramètre
  for (int i = 0; i < nb_pieces; i++) {

    // On récupère les 6 premières valeurs de la ligne
    fscanf(fichier, "%d %d %d %d %d %d",
	   scanPiece,
	   scanPiece+1,
	   scanPiece+2,
	   scanPiece+3,
	   scanPiece+4,
	   scanPiece+5);

    // On ajoute une nouvelle pièce à partir de ces valeur à notre liste
    *(p+i) = new_piece(scanPiece[0], scanPiece[1], scanPiece[2], scanPiece[3], scanPiece[4], scanPiece[5]);
      
  }

  return p;
}

// Renvoie un game crée à partir d'un fichier txt et du type de game voulu
game new_game_from_file(char* fichier) {

  // Création de la variable permettant la lecture du fichier
  FILE* file = fopen(fichier, "r");

  // Variable contenant les paramètres du game
  int scanGame[2] = {0};
  
  int nb_pieces = 0;
  game g = NULL;

  // On vérifie que le fichier existe
  if (file != NULL) {

    // On lit la première ligne avec les paramètres de la game
    fscanf(file, "%d %d", scanGame, scanGame+1);

    // On lit la deuxième qui contient le nombre de pièces
    fscanf(file, "%d", &nb_pieces);

    // Création du game avec tout ces paramètres
    g = new_game(scanGame[0], scanGame[1], nb_pieces, new_pieces_array(file, nb_pieces));

    // On ferme la lecture du fichier
    fclose(file);
    
    return g;

  } else {
        
    printf("Impossible de lire le fichier");
    
  }

  fclose(file);

  return NULL;
}
