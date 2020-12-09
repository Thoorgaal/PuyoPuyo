#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "../moteurLogique/terrain.h"
#include <vector>
#include "../moteurLogique/Joueur.h"

struct Fenetre{
    Fenetre();
    sf::RectangleShape dessinerPuyoP(float x, float y, int c);//auteur Jolan, confiance tres bonne
    //affiche le puyo demandé en position demandé avec une taille de wP et hP
    void afficherGT(int score);//affiche le terrain plus le fond ainsi que le score et les puyos en jeu
    //confiance tres bonne 
    Fenetre(char *m);//créé la fenetre et met un evenenement fermeture de fenetre auteur : Jolan,
    //fiabilité haute
    bool action(Joueur j1);// attends la réponse d'un joueur et fait l'action qui lui est rattaché
    sf::RenderWindow window;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); //je peux obtenir la taille de l'écran
    sf::Font font;
    int mode ;
    float wT = desktop.width/4, hT = 3*desktop.height/4, wP = desktop.width/(4*getDLA());
    float xT = 3*desktop.width/8, yT = 3*desktop.height/16, hP = hT/getDLO() ;
    char fileIN[256];
    const float G = 0.1;
    
};

#endif