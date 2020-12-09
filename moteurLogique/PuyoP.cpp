#include "PuyoP.hpp"
#include <vector>

using namespace std;



PuyoP::PuyoP(){
    for(int i = 0; i < dLo; i++){ 
        gridPuyo[i]  = vector<int>(dLa);
        for(int j = 0; j<gridPuyo[i].size(); j++){
            gridPuyo[i][j] = couleursD::VIDE;
        }
    }
}

bool PuyoP::doExist(int x, int y){
    if(gridPuyo[y][x] == couleursD::VIDE){
        return false;
    }
    return true;
}

