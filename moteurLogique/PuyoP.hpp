#ifndef PUYOP_HPP_INCLUDED
#define PUYOP_HPP_INCLUDED


#include <vector>

struct PuyoP{    
    PuyoP();
    void gravite();
    bool doExist(int x,int y);
    enum couleursD{VIDE,ROUGE,VERT,JAUNE,BLEU,MAGENTA};
    int c,dLa = 6, dLo = 13;
    std::vector<std::vector<int>> gridPuyo = std::vector<std::vector<int>>(dLo);
    /*Les premiers crochets indiqueront la position y, les deuxiemes la position y et contiendra la couleur (vide par défaut) */  
    bool isIni = false;
    int rota =0; //0 mode par défauts 1 .... il pourra etre modifie grace au terrain
};

#endif 