#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include <conio.h>
#include <stdbool.h>
#include <unistd.h>


#define Ligne 15
#define Colonne 30


typedef struct position
{
    int x;
    int y;
}t_position;


typedef struct plateau
{
    char caractere[Ligne][Colonne];
    char caractere_precedent[Ligne][Colonne];
    int vieSnoopy;
    int score;
    t_position PositionSnoopy;
    t_position boule;
    t_position oiseau[3];
    t_position blocCassable[5];
    t_position blocPoussable[5];
    t_position blocPiege[3];
    t_position blocInvincible[5];
    t_position blocDisApa[5];
    t_position blocApousser[5];
}t_plateau;



void effacerEcran();
void clearplateau();
void sauvegarderPlateau(t_plateau *terrain, char *nomFichier);
void initialiserPlateau(t_plateau*terrain);
void afficherPlateauFromFile(char *nomFichier);
void Deplacement(t_plateau *terrain);
void effacerConsole();
void DeplacementBoule(t_plateau *terrain, char direction);
void afficherPlateau();
void DeplacementAutoBoule(t_plateau *terrain);
void effacerZone(int debutLigne, int debutColonne, int finLigne, int finColonne);
void effacerCaractere(int ligne, int colonne);
void Menu();
void effacerPlateau(t_plateau *terrain);
void iniPlateau2(t_plateau *terrain);
void info_joueur(t_plateau*terrain,int x,int y, int *timerCount);
void Deplacement2(t_plateau *terrain);
void deplacerBalleSnoopy(terrain);
void gererCode(t_plateau *terrain);
void deplacementSnoopy(t_plateau *terrain);
void boucleDeJeu(t_plateau *terrain);
void boucleDeJeu(t_plateau *terrain);
void deplacementSnoopy(t_plateau *terrain);
void deplacementBalle(t_plateau *terrain);

#endif // PLATEAU_H_INCLUDED
