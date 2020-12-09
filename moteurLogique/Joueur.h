#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include <string>

struct Joueur{
    void appliquerRota(int r, int r2);
    void appliquerDirection(bool direction); //si true a droite ,si false a gauche 
    bool verifCO();
    bool verifCP();
    void agirT();
    bool agir();
    void zSolo();
    void sSolo();
    void qSolo();
    void dSolo();
    std::string nom;
    int score= 0;
    bool peutJouer = false;
    
};
	
#endif