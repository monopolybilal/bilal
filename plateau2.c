#include "plateau.h"
#include "plateau.h"

void effacerPlateau(t_plateau *terrain) {
    for (int i = 0; i < Ligne; i++) {
        for (int j = 0; j < Colonne; j++) {
            terrain->caractere[i][j] = ' ';
            terrain->caractere_precedent[i][j] = ' '; // Réinitialisation du tableau de caractères précédents
        }
    }
}

void blocPiege(t_plateau* terrain) {
    for (int i = 0; i < 1; i++) {
        if (terrain->PositionSnoopy.x == terrain->blocPiege[i].x && terrain->PositionSnoopy.y == terrain->blocPiege[i].y) {
            terrain->vieSnoopy = 0;

            printf("Snoopy est mort");
            effacerZone(0, 0, 60, 60);
            Menu(terrain);
        }
    }
}

void iniPlateau2(t_plateau *terrain) {
  effacerZone(0,0,60,60);

    for (int i = 0; i < Ligne; i++) {
        for (int j = 0; j < Colonne; j++) {
            if (i == 0 || i == Ligne - 1) {
                terrain->caractere[i][j] = '-';
            } else if (j == 0 || j == Colonne - 1) {
                terrain->caractere[i][j] = '|';
            } else {
                terrain->caractere[i][j] = ' ';
            }
            terrain->caractere_precedent[i][j] = ' '; // Réinitialisation du tableau de caractères précédents
        }
    }

    // Réinitialisation des autres valeurs de la structure
    terrain->PositionSnoopy.x = Ligne / 2;
    terrain->PositionSnoopy.y = Colonne / 2;
    terrain->caractere[terrain->PositionSnoopy.x][terrain->PositionSnoopy.y] = 0x01;
    terrain->boule.x = Ligne / 3;
    terrain->boule.y = Colonne / 2;
    terrain->caractere[terrain->boule.x][terrain->boule.y] = 0x0B;



    // Réinitialisation des oiseaux dans les coins
    terrain->oiseau[0].x = 1;
    terrain->oiseau[0].y = 1;
    terrain->caractere[terrain->oiseau[0].x][terrain->oiseau[0].y] = 0x0E;
    terrain->oiseau[1].x = 1;
    terrain->oiseau[1].y = Colonne - 2;
    terrain->caractere[terrain->oiseau[1].x][terrain->oiseau[1].y] = 0x0E;
    terrain->oiseau[2].x = Ligne - 2;
    terrain->oiseau[2].y = 1;
    terrain->caractere[terrain->oiseau[2].x][terrain->oiseau[2].y] = 0x0E;
    terrain->oiseau[3].x = Ligne - 2;
    terrain->oiseau[3].y = Colonne - 2;
    terrain->caractere[terrain->oiseau[3].x][terrain->oiseau[3].y] = 0x0E;

    // Bloc à gauche
    terrain->blocCassable[0].x = terrain->PositionSnoopy.x;
    terrain->blocCassable[0].y = terrain->PositionSnoopy.y - 3;
    terrain->caractere[terrain->blocCassable[0].x][terrain->blocCassable[0].y] =0x06;

    // Bloc à droite
    terrain->blocCassable[1].x = terrain->PositionSnoopy.x;
    terrain->blocCassable[1].y = terrain->PositionSnoopy.y + 3;
    terrain->caractere[terrain->blocCassable[1].x][terrain->blocCassable[1].y] = 0x06;

    // Bloc en haut
    terrain->blocCassable[2].x = terrain->PositionSnoopy.x - 3;
    terrain->blocCassable[2].y = terrain->PositionSnoopy.y;
    terrain->caractere[terrain->blocCassable[2].x][terrain->blocCassable[2].y] = 0x06;

    // Bloc en bas
    terrain->blocCassable[3].x = terrain->PositionSnoopy.x + 3;
    terrain->blocCassable[3].y = terrain->PositionSnoopy.y;
    terrain->caractere[terrain->blocCassable[3].x][terrain->blocCassable[3].y] = 0x06;
    terrain->score = 0;

    //Bloc piégé
    terrain->blocPiege[0].x=3;
    terrain->blocPiege[0].y=3;
    terrain->caractere[terrain->blocPiege[0].x][terrain->blocPiege[0].y]=0x05;

    terrain->blocPiege[1].x=12;
    terrain->blocPiege[1].y=27;
    terrain->caractere[terrain->blocPiege[1].x][terrain->blocPiege[1].y]=0x05;
}
