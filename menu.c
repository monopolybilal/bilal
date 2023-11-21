
#include "plateau.h"

void modepass() {
    char cle[] = "Wilkens05";
    char cleprincipale[50];
    int tentatives_max = 3; // Nombre maximal de tentatives à chaque joueur
    int tentative_actuelle = 0;

    do {
        printf("Rentrez un mot de pass:\n");
        scanf("%s", cleprincipale);
        if (strcmp(cle, cleprincipale) != 0){
            printf("Mot de passe incorrect. Il vous reste %d tentatives.\n", tentatives_max - tentative_actuelle - 1);
            tentative_actuelle++;

            if (tentative_actuelle == tentatives_max) {
                printf("Nombre maximal de tentatives atteint\n");
                exit(0);
            }
        } else {
            printf("Mot de passe correct.\n");
            break; // Sortir de la boucle si le mot de passe est correct
        }
    } while (tentative_actuelle < tentatives_max);
}
void modepass1(){
    char cle[] = "Wilkens";
    char cleprincipale[50];
    printf("Rentrez un mot de pass :\n");
    scanf("%s", cleprincipale);
    if (strcmp(cle, cleprincipale) != 0) {
        printf("Mot de passe incorrect. Fermeture du programme.\n");
        exit(0);
    } else {
        printf("Mot de passe correct.\n");
    }

}

void loadingBar(){
    modepass1();
    // 0 - black background,
    // D - purple Foreground
    system("color 0D");

    // Initialize char for printing
    // loading bar
    char a = 177, b = 219, c = 201, d = 200,  e = 205, f = 188, g = 187;

    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t");
    gotoligcol(100, 500);
    printf("Chargement du jeu...\n\n");
    printf("\t\t\t\t\t");



    //Fond barre de progression
    gotoligcol(100, 500);
    for (int i = 0; i < 26; i++){
        printf("%c", a);
    }


    //Remettre le curseur au point de d�part
    //Situer la barre de chargement
    printf("\r");
    printf("\t\t\t\t\t");

    //Chargement barre de pogression
    gotoligcol(100, 500);
    for (int i = 0; i < 26; i++)
    {
        printf("%c", b);

        //Vitesse de chargement
        Sleep(150);
    }
    system("cls");
}

void reglessnoopy(){
    printf("Regles Snoopy : \n"
           "\n"
           "Snoopy a pour objectif de récupérer quatre oiseaux situés aux quatre coins du niveau, le tout dans un laps de temps défini de deux minutes par niveau. Cependant, récupérer ces oiseaux n'est pas une tâche aisée, car une balle rebondit en permanence dans le niveau, entravant les efforts de Snoopy dans sa quête.\n"
           "  \n"
           "Snoopy doit franchir d'autres obstacles tels que des téléporteurs utilisés par la balle, des cases piégées, voire même des blocs qu'il doit pousser ou briser.\n"
           "\n"
           "La balle se déplace exclusivement en diagonale, rebondissant uniquement sur les murs, c'est-à-dire les bords de la matrice. Sa vitesse reste constante. La balle traverse tous les obstacles du terrain sans changer de direction, mais elle met fin à la quête de Snoopy en le \"tuant\" dès qu'elle le touche.\n"
           "\n"
           "Snoopy ne peut pas se déplacer en diagonale. Il ne peut se déplacer que dans les 4 directions classiques\n"
           "(Haut, Bas, Gauche et Droite) et d'une seule case à la fois.\n"
           "\n"
           "Au départ, le joueur dispose de 3 vies. Chaque niveau doit être complété en moins de 120 secondes. En cas d'expiration du temps imparti, le joueur perd une vie et recommence le niveau. L'objectif consiste à récupérer les 4 oiseaux du niveau sans être touché par la balle et/ou les ennemis, s'ils sont présents.\n"
           "\n"
           "Pour gagner, il faut récupérer les 4 oiseaux du niveau. Un fois un niveau terminé, on charge\n"
           "automatiquement le niveau suivant en donnant son code d’accès et ainsi de suite.\n"
           "Quand le joueur perd toutes ses vies, on affiche un écran de GameOver et le jeu revient au menu\n"
           "principal.\n"
           "\n"
           "Pour gagner, il faut récuperer les 4 oiseaux du niveau. Une fois qu'un niveau est réussi, le niveau suivant se charge automatiquement à l'aide de son code d'accès, et ainsi de suite. En cas de perte de toutes ses vies, le jeu affiche un écran Game Over et retourne au menu principal.");

}

void Menu(t_plateau*terrain){
    modepass();
    int choix;
    do{
        Color(2,0);

        printf("===========MENU PRINCIPAL=========\n");

        Color(14,0);
        printf("1.LANCER UNE NOUVELLE PARTIE  \n");
        printf("2.CHARGER UNE ANCIENNE PARTIE  \n");
        printf("3.SAUVEGARDER UNE PARTIE  \n");
        printf("4.AFFICHER LES REGLES DU JEU  \n");
        printf("Pour revenir au menu principal pendant la partie en cours, Entrez 9 \n");
        Color(15, 0);
        printf("Saisissez votre choix(1-4):");
        scanf("%d",&choix);
    }while(choix < 1 || choix>4);
    switch(choix)
    {
        case 1:
            system("cls");
            loadingBar();
            Color(15,0);
            initialiserPlateau(terrain);
            boucleDeJeu(terrain);
            printf("\n");
            break;
        case 2:
            modepass();
            break;
        case 3:
            modepass();
            break;
        case 4:
            loadingBar();
            reglessnoopy();
            break;
    }


}

