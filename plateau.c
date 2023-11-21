#include "plateau.h"
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}


void gotoligcol(int lig, int col){

    COORD mycoord;
    mycoord.X = col;

    mycoord.Y = lig;

    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void effacage_txt (int ligne, int colonne, char txt[])
{
    gotoligcol(ligne, colonne);
    Color(0, 0);
    Color(15, 0);
}




void initialiserPlateau(t_plateau *terrain){

    for (int i = 0; i < Ligne; i++)
    {
        for (int j = 0; j < Colonne; j++)
        {
            if (i == 0 || i == Ligne - 1)
            {
                terrain->caractere[i][j] = '-';

            }
            else if (j == 0 || j == Colonne - 1)
            {
                terrain->caractere[i][j] = '|';
            }
            else
            {
                terrain->caractere[i][j] = ' ';
            }
        }
    }

    terrain->PositionSnoopy.x=Ligne/2;
    terrain->PositionSnoopy.y=Colonne/2;
    terrain->caractere[terrain->PositionSnoopy.x][terrain->PositionSnoopy.y]= 0x01;
    terrain->boule.x=Ligne/3;
    terrain->boule.y=Colonne/2;
    terrain->caractere[terrain->boule.x][terrain->boule.y] = 0x0B ;
    terrain->vieSnoopy=3;
    // Initialisation des oiseaux dans les coins
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
    terrain->score=0;
}

void effacerZone(int debutLigne, int debutColonne, int finLigne, int finColonne) {
    for (int i = debutLigne; i <= finLigne; i++) {
        gotoligcol(i, debutColonne); // Positionner le curseur au début de la ligne
        for (int j = debutColonne; j <= finColonne; j++) {
            printf(" "); // Imprimer des espaces pour effacer la zone
        }
    }
}
void effacerCaractere(int ligne, int colonne) {
    gotoligcol(ligne, colonne); // Positionner le curseur à la position spécifique
    printf(" "); // Imprimer un espace pour effacer le caractère à cette position
}



void afficherPlateau(t_plateau *terrain) {
    for (int i = 0; i < Ligne; i++) {
        for (int j = 0; j < Colonne; j++) {
            // Vérifier si le caractère a changé
            if (terrain->caractere[i][j] != terrain->caractere_precedent[i][j]) {
                gotoligcol(i, j); // Déplacer le curseur à la position
                printf("%c", terrain->caractere[i][j]); // Afficher le caractère
                terrain->caractere_precedent[i][j] = terrain->caractere[i][j]; // Mettre à jour la copie du caractère précédent
            }
        }
    }
//info_joueur(terrain,2,35);
}

void sauvegarderPlateau(t_plateau *terrain,  char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier != NULL) {
        for (int i = 0; i < Ligne; i++) {
            for (int j = 0; j < Colonne; j++) {
                fprintf(fichier, "%c", terrain->caractere[i][j]);
            }
            fprintf(fichier, "\n");
        }
        fclose(fichier);

        //afficherPlateauFromFile(nomFichier); // Afficher le contenu du fichier après chaque sauvegarde
    } else {
        printf("Impossible d'ouvrir le fichier %s pour l'enregistrement.\n", nomFichier);
    }
}

void info_joueur(t_plateau*terrain,int x,int y, int *timerCount)
{
    gotoligcol(x,y);
    Color(12,0);
     printf("Timer : %d \n", 120 - *timerCount); // Affiche le temps restant
    gotoligcol(x+1,y);
    printf("NombreVie : ");
     Color(15,0);
    printf("%d\n",terrain->vieSnoopy);
    Color(12,0);
    gotoligcol(x+2,y);
    printf("ScoreSnoopy : ");
     Color(15,0);
    printf("%d",terrain->score);

}


void deplacementBalle(t_plateau *terrain) {
    static int direction_x = 1; // Utilisation du mot-clé static pour conserver la direction entre les appels
    static int direction_y = 1;

    terrain->caractere[terrain->boule.x][terrain->boule.y] = ' ';

    int new_x = terrain->boule.x + direction_x;
    int new_y = terrain->boule.y + direction_y;

    // Vérifier les limites du plateau pour le rebondissement de la balle
    if (new_x >= Ligne - 1 || new_x <= 0) {
        direction_x = -direction_x;
    }

    if (new_y >= Colonne - 1 || new_y <= 0) {
        direction_y = -direction_y;
    }

    // Mettre à jour les nouvelles coordonnées après le rebondissement
    new_x = terrain->boule.x + direction_x;
    new_y = terrain->boule.y + direction_y;

    terrain->boule.x = new_x;
    terrain->boule.y = new_y;

    terrain->caractere[new_x][new_y] = '*'; // Mettre à jour la position de la balle sur le plateau

   if (terrain->boule.x == terrain->PositionSnoopy.x && terrain->boule.y == terrain->PositionSnoopy.y)
        {
            terrain->vieSnoopy -= 1;
        }

   if (terrain->PositionSnoopy.x == terrain->oiseau[0].x && terrain->PositionSnoopy.y == terrain->oiseau[0].y)
        {
            if (terrain->oiseau[0].x >= 0 && terrain->oiseau[0].y >= 0)
            {
                terrain->score += 1;
                terrain->oiseau[0].x = -1; // Marquer l'oiseau comme capturé en affectant des coordonnées hors limites
                terrain->oiseau[0].y = -1;
            }
        }
        if (terrain->PositionSnoopy.x == terrain->oiseau[1].x && terrain->PositionSnoopy.y == terrain->oiseau[1].y)
        {
            if (terrain->oiseau[1].x >= 0 && terrain->oiseau[1].y >= 0)
            {
                terrain->score += 1;
                terrain->oiseau[1].x = -1; // Marquer l'oiseau comme capturé en affectant des coordonnées hors limites
                terrain->oiseau[1].y = -1;
            }
        }
        if (terrain->PositionSnoopy.x == terrain->oiseau[2].x && terrain->PositionSnoopy.y == terrain->oiseau[2].y)
        {
            if (terrain->oiseau[2].x >= 0 && terrain->oiseau[2].y >= 0)
            {
                terrain->score += 1;
                terrain->oiseau[2].x = -1; // Marquer l'oiseau comme capturé en affectant des coordonnées hors limites
                terrain->oiseau[2].y = -1;
            }
        }
        if (terrain->PositionSnoopy.x == terrain->oiseau[3].x && terrain->PositionSnoopy.y == terrain->oiseau[3].y)
        {
            if (terrain->oiseau[3].x >= 0 && terrain->oiseau[3].y >= 0)
            {
                terrain->score += 1;
                terrain->oiseau[3].x = -1; // Marquer l'oiseau comme capturé en affectant des coordonnées hors limites
                terrain->oiseau[3].y = -1;
            }
        }

    sauvegarderPlateau(terrain, "plateau.txt");
    afficherPlateau(terrain);
}

void deplacementSnoopy(t_plateau *terrain) {
    char direction;

    if (_kbhit()) {
        direction = _getch();
        terrain->caractere[terrain->PositionSnoopy.x][terrain->PositionSnoopy.y] = ' ';

            if (direction == 'z' && terrain->PositionSnoopy.x > 1) {
                terrain->PositionSnoopy.x = terrain->PositionSnoopy.x - 1;
            } else if (direction == 's' && terrain->PositionSnoopy.x < Ligne - 2) {
                terrain->PositionSnoopy.x = terrain->PositionSnoopy.x + 1;
            } else if (direction == 'q' && terrain->PositionSnoopy.y > 1) {
                terrain->PositionSnoopy.y = terrain->PositionSnoopy.y - 1;
            } else if (direction == 'd' && terrain->PositionSnoopy.y < Colonne - 2) {
                terrain->PositionSnoopy.y = terrain->PositionSnoopy.y + 1;
            }

            terrain->caractere[terrain->PositionSnoopy.x][terrain->PositionSnoopy.y] = 0x01;
            sauvegarderPlateau(terrain, "plateau.txt");
            afficherPlateau(terrain);

    }
}

void boucleDeJeu(t_plateau *terrain) {
    int timerCount = 0;
    time_t startTime = time(NULL);
do{
       // initialiserPlateau(terrain);
        deplacementBalle(terrain);
        deplacementSnoopy(terrain);
        info_joueur(terrain, 2, 35, &timerCount);

        if (terrain->score == 4) {
            Color(10,0);
            gotoligcol(20,30);
            printf("Bravo, vous allez augmenter de niveau ");
            usleep(2000000);
            effacerZone(20,30,20,80);
            iniPlateau2(terrain);
            blocPiege(terrain);
            deplacementBalle(terrain);
            deplacementSnoopy(terrain);

            info_joueur(terrain, 2, 35, &timerCount);

        }

        Sleep(100);
        time_t currentTime = time(NULL);
        if (difftime(currentTime, startTime) >= 1.0) {
            timerCount++;
            startTime = currentTime;
        }

} while(terrain->vieSnoopy > 0 && timerCount < 120);

    gotoligcol(30,40);
    printf("Game over\n");
    usleep(2000000);
    effacerZone(0, 0, 60, 60);
    Menu(terrain);

}


